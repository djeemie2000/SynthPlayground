#include "PatchReader.h"
#include "tinyxml2.h"
#include "CommandStackItem.h"
#include "CommandStack.h"
#include "ModuleManager.h"
#include "JackConnectionManager.h"

CPatchReader::CPatchReader()
{
}

namespace
{

std::string TiXmlAttributeToString(const tinyxml2::XMLElement* Element, const std::string& AttributeName)
{
    if(Element && Element->Attribute(AttributeName.c_str()))
    {
        return Element->Attribute(AttributeName.c_str());
    }
    return "";
}

}

bool CPatchReader::ReadParameters(const std::string &Path,
                                  CCommandStack &CommandStack,
                                  CModuleManager &ModuleManager,
                                  CJackConnectionManager &ConnectionManager)
{
    tinyxml2::XMLDocument Doc;
    Doc.LoadFile(Path.c_str());
    if(!Doc.Error())
    {
        // modules
        if(tinyxml2::XMLElement* ModulesEl = Doc.RootElement()->FirstChildElement("Modules"))
        {
            CModuleManager::ModuleState ImportedModuleState;
            for(tinyxml2::XMLElement* ModuleEl = ModulesEl->FirstChildElement("Module");
                ModuleEl!=nullptr;
                ModuleEl = ModuleEl->NextSiblingElement("Module"))
            {
                std::string Name = TiXmlAttributeToString(ModuleEl, "Name");
                std::string Type = TiXmlAttributeToString(ModuleEl, "Type");
                ImportedModuleState[Name] = Type;
            }
            ModuleManager.ApplyModuleState(ImportedModuleState);
        }
        //connections
        if(tinyxml2::XMLElement* ConnectionsEl = Doc.RootElement()->FirstChildElement("Connections"))
        {
            for(tinyxml2::XMLElement* ConnectionEl = ConnectionsEl->FirstChildElement("Connection");
                ConnectionEl!=nullptr;
                ConnectionEl = ConnectionEl->NextSiblingElement("Connection"))
            {
                std::string OutputPortName = TiXmlAttributeToString(ConnectionEl, "OutputPort");
                std::string InputPortName = TiXmlAttributeToString(ConnectionEl, "InputPort");
                ConnectionManager.Connect(OutputPortName, InputPortName);
            }
        }
        //parameters
        if(tinyxml2::XMLElement* Parameters = Doc.RootElement()->FirstChildElement("Parameters"))
        {
            for(tinyxml2::XMLElement* Parameter = Parameters->FirstChildElement("Parameter");
                Parameter!=nullptr;
                Parameter = Parameter->NextSiblingElement("Parameter"))
            {
                std::string Name = TiXmlAttributeToString(Parameter, "Name");
                std::string Type = TiXmlAttributeToString(Parameter, "Type");
                std::string Value = TiXmlAttributeToString(Parameter, "Value");
                CommandStack.AddItem({Name, Type, Value});
            }
        }
        // else: missing parameters
    }

    return false;
}
