#include "ModuleFactory.h"
#include "CommandStackController.h"

#include "AmpModule.h"
#include "ConstModule.h"
#include "OperatorModule.h"
#include "PhasorModule.h"

CModuleFactory::CModuleFactory(std::shared_ptr<CCommandStackController> CommandStackController)
 : m_CommandStackController(CommandStackController)
{
}

std::shared_ptr<IModularModule> CModuleFactory::Create(const std::string &Type, const std::string &Name)
{
    //TODO
    std::shared_ptr<IModularModule> Module;

    if(Type=="Amp")
    {
        Module.reset(new CAmpModule(Name));
    }
    else if(Type == "Const")
    {
        Module.reset(new CConstModule(Name, *m_CommandStackController));//TODO sp ipv ref
    }
    else if(Type == "Operator")
    {
        Module.reset(new COperatorModule(Name, *m_CommandStackController));//TODO sp ipv ref
    }
    else if(Type == "Phasor")
    {
        Module.reset(new CPhasorModule(Name));
    }

    return Module;
}
