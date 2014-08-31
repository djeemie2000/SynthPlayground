#include "ModuleFactory.h"
#include "CommandStackController.h"

#include "AmpModule.h"
#include "ControllerBankModule.h"
#include "OperatorModule.h"
#include "PhasorModule.h"
#include "MidiNoteModule.h"
#include "LpfModule.h"
#include "LFOBankModule.h"
#include "SimpleOscillatorModule.h"

CModuleFactory::CModuleFactory(std::shared_ptr<CCommandStackController> CommandStackController)
 : m_CommandStackController(CommandStackController)
{
}

std::shared_ptr<IModularModule> CModuleFactory::Create(const std::string &Type, const std::string &Name)
{
    std::shared_ptr<IModularModule> Module;

    if(Type=="Amp")
    {
        Module.reset(new CAmpModule(Name));
    }
    else if(Type == "ControllerBank<8>")
    {
        Module.reset(new CControllerBankModule(Name, 8, *m_CommandStackController));//TODO sp ipv ref
    }
    else if(Type == "Operator")
    {
        Module.reset(new COperatorModule(Name, *m_CommandStackController));//TODO sp ipv ref
    }
    else if(Type == "Phasor")
    {
        Module.reset(new CPhasorModule(Name));
    }
    else if(Type == "MidiNote")
    {
        Module.reset(new CMidiNoteModule(Name));
    }
    else if(Type == "LPF")
    {
        Module.reset(new CLpfModule(Name, *m_CommandStackController));
    }
    else if(Type == "LFOBank<8>")
    {
        Module.reset(new CLFOBankModule(Name, 8, *m_CommandStackController));
    }
    else if(Type == "SimpleOscillator")
    {
        Module.reset(new CSimpleOscillatorModule(Name, *m_CommandStackController));
    }

    return Module;
}

std::vector<string> CModuleFactory::GetSupportedTypes() const
{
    return { "Amp", "ControllerBank<8>", "Operator", "Phasor", "MidiNote", "LPF", "LFOBank<8>", "SimpleOscillator" };
}
