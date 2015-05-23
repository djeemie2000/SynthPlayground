#include "PatchWriter.h"
#include "tinyxml2.h"
#include "CommandStack.h"
#include "JackConnectionManager.h"
#include "ModuleManager.h"

CPatchWriter::CPatchWriter()
{
}

bool CPatchWriter::WritePatch(const std::string &Path,
                                   const CCommandStack &CommandStack,
                                   const CModuleManager &ModuleManager,
                                   const CJackConnectionManager& ConnectionManager)
{
    tinyxml2::XMLDocument Doc;
    Doc.InsertEndChild(Doc.NewElement("xml"));
    if(tinyxml2::XMLElement* RootEl = Doc.RootElement())
    {
        // modules
        if(tinyxml2::XMLElement* ModulesEl = Doc.NewElement("Modules"))
        {
            for(const auto& Module : ModuleManager.GetModuleState())
            {
                tinyxml2::XMLElement* ModuleEl = Doc.NewElement("Module");
                ModuleEl->SetAttribute("Name", Module.first.c_str());
                ModuleEl->SetAttribute("Type", Module.second.c_str());
                ModulesEl->InsertEndChild(ModuleEl);
            }
            RootEl->InsertEndChild(ModulesEl);
        }
        // connections
        if(tinyxml2::XMLElement* ConnectionsEl = Doc.NewElement("Connections"))
        {
            for(const auto& Connection : ConnectionManager.GetConnections())
            {
                tinyxml2::XMLElement* ConnectionEl = Doc.NewElement("Connection");
                ConnectionEl->SetAttribute("OutputPort", Connection.s_OutputPortName.c_str());
                ConnectionEl->SetAttribute("InputPort", Connection.s_InputPortName.c_str());
                ConnectionsEl->InsertEndChild(ConnectionEl);
            }
            RootEl->InsertEndChild(ConnectionsEl);
        }
        // parameters
        if(tinyxml2::XMLElement* ParametersEl = Doc.NewElement("Parameters"))
        {
            for(const auto& Item : CommandStack.GetStack())
            {
                tinyxml2::XMLElement* ParameterEl = Doc.NewElement("Parameter");
                ParameterEl->SetAttribute("Name", Item.Name().c_str());
                ParameterEl->SetAttribute("Type", Item.Type().c_str());
                ParameterEl->SetAttribute("Value", Item.Value().c_str());
                ParametersEl->InsertEndChild(ParameterEl);
            }
            RootEl->InsertEndChild(ParametersEl);
        }
    }

    return Doc.SaveFile(Path.c_str());
}
