#ifndef PHASORMODULE_H
#define PHASORMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class IAudioFilter;
class CJackIOManager;

class CPhasorModule : public IModularModule
{
public:
    CPhasorModule(const std::string& Name);
    ~CPhasorModule();

    std::string GetName() const override;

private:
    bool Open();
    bool Close();

    std::string m_Name;
    std::shared_ptr<IAudioFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // PHASORMODULE_H
