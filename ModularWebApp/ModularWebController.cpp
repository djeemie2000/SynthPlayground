#include <fstream>
#include "ModularWebController.h"
#include "CommandStackController.h"
#include "ModularController.h"
#include "WebPageManager.h"
#include "WebPageHelpers.h"
#include "WebRequest.h"
#include "CommandStack.h"

CModularWebController::CModularWebController(const std::string& PatchDirectory)
    : m_ModularController(new CModularController(PatchDirectory))
    , m_WebPageManager(new CWebPageManager())
{
    UpdatePatchesPage(m_ModularController->GetPatchManager(), *m_WebPageManager);
    UpdateModuleCreationPage(m_ModularController->GetModuleManager(), *m_WebPageManager);

    CreatePages(*m_WebPageManager);
}

CModularWebController::~CModularWebController()
{
    RemoveAll();
    m_WebPageManager.reset();
    m_ModularController.reset();
}

string CModularWebController::HandleWebRequest(const SWebRequest &Request)
{
    if(Request.s_Uri == "/Patches")
    {
        std::string Command = GetQuery("Command", Request);
        std::string SelectedPatchName = GetQuery("SelectedPatch", Request);
        std::string NewPatchName = GetQuery("PatchName", Request);

        if(Command=="Load")
        {
            if(!SelectedPatchName.empty())
            {
                m_ModularController->LoadPatch(SelectedPatchName);
            }
        }
        else if(Command=="Save")
        {
            if(!SelectedPatchName.empty())
            {
                //Save current patch as SelectedPatchName
                m_ModularController->SavePatch(SelectedPatchName);
            }
        }
        else if(Command=="Clear")
        {
            RemoveAll();
        }
        else if(Command=="SaveAs")
        {
            if(!NewPatchName.empty())
            {
                //Save current patch as NewPatchName (if it is not empty)
                m_ModularController->SavePatch(NewPatchName);
                //
                UpdatePatchesPage(m_ModularController->GetPatchManager(), *m_WebPageManager);
            }
        }
    }
    else if(Request.s_Uri == "/ModuleCreation")
    {
        std::string Command = GetQuery("Command", Request);
        std::string ModuleType = GetQuery("SelectedModule", Request);
        if(Command=="Create" && !ModuleType.empty())
        {
            Create(ModuleType, "");//auto name creation
        }
    }
    else if(Request.s_Uri == "/Connections")
    {
        UpdateConnectionsPage(m_ModularController->GetModuleManager(), *m_WebPageManager);
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
            m_ModularController->Default();
        }
        else if(Command=="Default")
        {
            // TODO defaults on selected module only
        }
        else if(Command=="Remove")
        {
            if(!SelectedModule.empty())
            {
                m_ModularController->Remove(SelectedModule);
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
                    SCmdStackItem Item = m_ModularController->GetCommandStackController().GetCurrent(itQuery.first);
                    Item.ValueFromString(itQuery.second);
                    m_ModularController->GetCommandStackController().Handle(Item);
                }
            }
        }

        UpdateModuleWebPages();
    }

    return m_WebPageManager->GetPage(Request.s_Uri);
}

bool CModularWebController::Create(const string &Type, const string &Name)
{
    bool RetVal = m_ModularController->Create(Type, Name);
    UpdateModuleWebPages();
    return RetVal;
}

bool CModularWebController::Remove(const string &Name)
{
    bool RetVal = m_ModularController->Remove(Name);
    UpdateModuleWebPages();
    return RetVal;
}

bool CModularWebController::RemoveAll()
{
    bool RetVal = m_ModularController->RemoveAll();
    UpdateModuleWebPages();
    return RetVal;
}

void CModularWebController::Restore()
{
    m_ModularController->Restore();
    UpdateModuleWebPages();
}

void CModularWebController::UpdateModuleWebPages()
{
    UpdateModulePages(m_ModularController->GetModuleManager(), *m_WebPageManager, m_ModularController->GetCommandStackController());
}
