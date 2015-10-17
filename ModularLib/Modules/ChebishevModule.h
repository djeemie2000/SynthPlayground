#ifndef ChebishevMODULE_H
#define ChebishevMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class IAudioFilter;
class CJackIOManager;

class CChebishevModule : public IModularModule
{
public:
    CChebishevModule(const std::string& Name);
    ~CChebishevModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;
    Names GetMidiOutputNames() const override {  return {};  }
    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();

    std::string m_Name;
    std::shared_ptr<IAudioFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // ChebishevMODULE_H
