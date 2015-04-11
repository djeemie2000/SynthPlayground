#include <fstream>
#include "ModularHeadlessController.h"
#include "CommandStackController.h"
#include "ModuleManager.h"
#include "ModuleFactory.h"
#include "JackConnectionManager.h"
#include "tinyxml2.h"

CModularHeadlessController::CModularHeadlessController()
 : m_ConnectionManager()
 , m_CommandStackController()
 , m_ModuleManager()
 , m_CapturedConnections()
 , m_CapturedParameters()
{
    m_ConnectionManager.reset(new CJackConnectionManager());
    m_ConnectionManager->OpenClient("ConnectionMgr");

    m_CommandStackController.reset(new CCommandStackController());
    std::shared_ptr<IModuleFactory> Factory(new CModuleFactory(m_CommandStackController));
    m_ModuleManager.reset(new CModuleManager(Factory));
}

CModularHeadlessController::~CModularHeadlessController()
{
    RemoveAll();
    m_ModuleManager.reset();
    m_CommandStackController.reset();
    m_ConnectionManager.reset();
}

//bool CModularHeadlessController::Create(const string &Type, const string &Name)
//{
//    return m_ModuleManager->Create(Type, Name);
//}

//bool CModularHeadlessController::Remove(const string &Name)
//{
//    return m_ModuleManager->Remove(Name);
//}

bool CModularHeadlessController::RemoveAll()
{
    return m_ModuleManager->RemoveAll();
}

bool CModularHeadlessController::Default()
{
    return m_CommandStackController->Default();
}

//std::vector<string> CModularHeadlessController::GetNames() const
//{
//    return m_ModuleManager->GetNames();
//}

//std::vector<string> CModularHeadlessController::GetSupportedTypes(const std::string& Category) const
//{
//    return m_ModuleManager->GetSupportedTypes(Category);
//}

//std::vector<string> CModularHeadlessController::GetSupportedCategories() const
//{
//    return m_ModuleManager->GetSupportedCategories();
//}

//void CModularHeadlessController::Capture()
//{
//    // capture modules (names, types)
//    m_ModuleManager->Capture();
//    // capture connections
//    m_CapturedConnections = ConnectionsToString(*m_ConnectionManager);
//    // capture parameters
//    m_CommandStackController->ExportToString(m_CapturedParameters);
//}

//void CModularHeadlessController::Restore()
//{
//    // restore captured modules
//    m_ModuleManager->Restore();
//    // restore captured connections
//    StringToConnections(*m_ConnectionManager, m_CapturedConnections);
//    // restore captured parameters
//    m_CommandStackController->ImportFromString(m_CapturedParameters);
//}

bool CModularHeadlessController::Save(const string &Path)
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

bool CModularHeadlessController::Load(const string &Path)
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

        return true;
    }
    return false;
}
