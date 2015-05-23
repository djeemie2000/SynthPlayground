#ifndef BasicSamplerMODULE_H
#define BasicSamplerMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CBasicSamplerFilter;
class CJackIOManager;
class CCommandStackController;

class CBasicSamplerModule : public IModularModule
{
public:
    CBasicSamplerModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CBasicSamplerModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;
    Names GetMidiOutputNames() const override {  return {};  }
    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();

    CCommandStackController& m_CommandStackController;
    std::string m_Name;
    std::shared_ptr<CBasicSamplerFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // BasicSamplerMODULE_H
