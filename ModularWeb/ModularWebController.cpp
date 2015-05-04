#include <fstream>
#include "ModularWebController.h"
#include "CommandStackController.h"
#include "ModuleManager.h"
#include "ModuleFactory.h"
#include "JackConnectionManager.h"
#include "tinyxml2.h"
#include "WebPageManager.h"
#include "WebPageHelpers.h"
#include "PatchManager.h"
#include "WebRequest.h"

CModularWebController::CModularWebController(const std::string& PatchDirectory)
    : m_PatchManager(new CPatchManager(PatchDirectory))
    , m_ConnectionManager()
    , m_CommandStackController()
    , m_ModuleManager()
    , m_CapturedConnections()
    , m_CapturedParameters()
    , m_WebPageManager(new CWebPageManager())
{
    m_ConnectionManager.reset(new CJackConnectionManager());
    m_ConnectionManager->OpenClient("ConnectionMgr");

    m_CommandStackController.reset(new CCommandStackController());
    std::shared_ptr<IModuleFactory> Factory(new CModuleFactory(m_CommandStackController));
    m_ModuleManager.reset(new CModuleManager(Factory));

    UpdateCommandsPage(*m_WebPageManager);
    UpdatePatchesPage(*m_PatchManager, *m_WebPageManager);
    UpdateModuleTypesPage(*m_ModuleManager, *m_WebPageManager);
    UpdateTestPage(*m_WebPageManager);

    CreatePages(*m_WebPageManager);
}

CModularWebController::~CModularWebController()
{
    RemoveAll();
    m_ModuleManager.reset();
    m_CommandStackController.reset();
    m_ConnectionManager.reset();
}

string CModularWebController::HandleWebRequest(const SWebRequest &Request)
{
    if(Request.s_Uri == "/Patches")
    {
        std::string Command = GetQuery("Command", Request);
        std::string SelectedPatchName = GetQuery("SelectedPatch", Request);
        std::string NewPatchName = GetQuery("PatchName", Request);
        if(!SelectedPatchName.empty())
        {
            if(Command=="Load")
            {
                LoadPatch(SelectedPatchName);
            }
            else if(Command=="Save")
            {
                //Save current patch as SelectedPatchName
                SavePatch(SelectedPatchName);
            }
            else if(Command=="Clear")
            {
                RemoveAll();
            }
            else if(Command=="SaveAs")
            {
                //Save current patch as NewPatchName (if it is not empty)
                if(!NewPatchName.empty())
                {
                    SavePatch(NewPatchName);
                    //
                    UpdatePatchesPage(*m_PatchManager, *m_WebPageManager);
                }
            }
        }
    }
    else if(Request.s_Uri == "/SupportedModules")
    {
        std::string ModuleType = GetQuery("Create", Request);
        if(!ModuleType.empty())
        {
            Create(ModuleType, "");
        }
    }
    else if(Request.s_Uri == "/Modules")
    {
        std::string Command = GetQuery("Command", Request);
        std::string SelectedModule = GetQuery("SelectedModule", Request);
        if(Command=="RemoveAll")
        {
            RemoveAll();
        }
        else if(Command=="DefaultAll")
        {
            Default();
        }
        else if(Command=="Default")
        {
            // TODO defaults on selected module only
        }
        else if(Command=="Remove")
        {
            if(!SelectedModule.empty())
            {
                m_ModuleManager->Remove(SelectedModule);
            }
        }
        else if(Command=="Edit")
        {
            // Queries are of the form
            //  ParameterName = string value

            // in order to correctly apply the parameter, first retrieve the current
            // then update current (which knows the correct type) from string value
            // then apply it

            for(auto itQuery : Request.s_Query)
            {
                if(itQuery.first!="Command" && itQuery.first!="SelectedModule")
                {
                    SCmdStackItem Item = m_CommandStackController->GetCurrent(itQuery.first);
                    Item.ValueFromString(itQuery.second);
                    m_CommandStackController->Handle(Item);
                }
            }
        }

        UpdateModuleWebPages();
    }

    return m_WebPageManager->GetPage(Request.s_Uri);
}

bool CModularWebController::Create(const string &Type, const string &Name)
{
    bool RetVal = m_ModuleManager->Create(Type, Name);
    UpdateModuleWebPages();
    return RetVal;
}

bool CModularWebController::Remove(const string &Name)
{
    bool RetVal = m_ModuleManager->Remove(Name);
    UpdateModuleWebPages();
    return RetVal;
}

bool CModularWebController::RemoveAll()
{
    bool RetVal = m_ModuleManager->RemoveAll();
    UpdateModuleWebPages();
    return RetVal;
}

bool CModularWebController::Default()
{
    return m_CommandStackController->Default();
}

void CModularWebController::Capture()
{
    // capture modules (names, types)
    m_ModuleManager->Capture();
    // capture connections
    m_CapturedConnections = ConnectionsToString(*m_ConnectionManager);
    // capture parameters
    m_CommandStackController->ExportToString(m_CapturedParameters);
}

void CModularWebController::Restore()
{
    // restore captured modules
    m_ModuleManager->Restore();
    // restore captured connections
    StringToConnections(*m_ConnectionManager, m_CapturedConnections);
    // restore captured parameters
    m_CommandStackController->ImportFromString(m_CapturedParameters);

    //
    UpdateModuleWebPages();
}

void CModularWebController::UpdateModuleWebPages()
{
    UpdateModulePages(*m_ModuleManager, *m_WebPageManager, *m_CommandStackController);
}

bool CModularWebController::LoadPatch(const string &PatchName)
{
    bool Succeeded = false;
    std::string Path = m_PatchManager->GetPath(PatchName);
    if(!Path.empty())
    {
        Succeeded = Load(Path);
    }
    return Succeeded;

}

bool CModularWebController::SavePatch(const string &PatchName)
{
    bool Succeeded = false;
    std::string Path = m_PatchManager->GetPath(PatchName);
    if(!Path.empty())
    {
        Succeeded = Save(Path);
    }
    return Succeeded;
}

bool CModularWebController::Save(const string &Path)
{
    std::ofstream OutFile;
    OutFile.open(Path.c_str());
    if(OutFile.is_open())
    {
        std::string Modules;
        m_ModuleManager->Export(Modules);
        std::string Connections = ConnectionsToString(*m_ConnectionManager);
        std::string Parameters;
        m_CommandStackController->ExportToString(Parameters);

        OutFile << "<xml>" << std::endl
                << "<Modules>" << std::endl << Modules << std::endl << "</Modules>" << std::endl
                << "<Connections>" << std::endl << Connections << std::endl << "</Connections>" << std::endl
                << "<Parameters>" << std::endl << Parameters << std::endl << "</Parameters>" << std::endl
                << "</xml>";

        return true;
    }
    return false;
}

namespace
{

std::string TiXmlElementToString(const tinyxml2::XMLElement* Element)
{
    if(Element && Element->GetText())
    {
        return Element->GetText();
    }
    return "";
}

}

bool CModularWebController::Load(const string &Path)
{
    tinyxml2::XMLDocument Doc;
    if(tinyxml2::XML_NO_ERROR == Doc.LoadFile(Path.c_str()))
    {
        std::string Modules = TiXmlElementToString( Doc.RootElement()->FirstChildElement("Modules") );
        std::string Connections = TiXmlElementToString( Doc.RootElement()->FirstChildElement("Connections") );
        std::string Parameters = TiXmlElementToString( Doc.RootElement()->FirstChildElement("Parameters") );
        m_ModuleManager->Import(Modules);
        StringToConnections(*m_ConnectionManager, Connections);
        m_CommandStackController->ImportFromString(Parameters);

        UpdateModuleWebPages();

        return true;
    }
    return false;
}
