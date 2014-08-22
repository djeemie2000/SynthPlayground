#ifndef OPERATORMODULE_H
#define OPERATORMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class COperatorFilter;
class CJackIOManager;
class CCommandStackController;

class COperatorModule : public IModularModule
{
public:
    COperatorModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~COperatorModule();

    std::string GetName() const override;

private:
    bool Open();
    bool Close();

    CCommandStackController& m_CommandStackController;
    std::string m_Name;
    std::shared_ptr<COperatorFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // OPERATORMODULE_H
