#ifndef CONSTMODULE_H
#define CONSTMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CConstFilter;
class CJackIOManager;
class CCommandStackController;

class CConstModule : public IModularModule
{
public:
    CConstModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CConstModule();

    std::string GetName() const override;

private:
    bool Open();
    bool Close();

    CCommandStackController& m_CommandStackController;
    std::string m_Name;
    std::shared_ptr<CConstFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // CONSTMODULE_H
