#ifndef AMPMODULE_H
#define AMPMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class IAudioFilter;
class CJackIOManager;

class CAmpModule : public IModularModule
{
public:
    CAmpModule(const std::string& Name);
    ~CAmpModule();

    std::string GetName() const override;

private:
    bool Open();
    bool Close();

    std::string m_Name;
    std::shared_ptr<IAudioFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // AMPMODULE_H
