#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CIntCombFilterFilter;
class CJackIOManager;
class CCommandStackController;

class CIntCombFilterModule : public IModularModule
{
public:
    CIntCombFilterModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CIntCombFilterModule();

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
    std::shared_ptr<CIntCombFilterFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
