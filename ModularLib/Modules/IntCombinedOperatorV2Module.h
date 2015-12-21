#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CIntCombinedOperatorV2Filter;
class CJackIOManager;
class CCommandStackController;

class CIntCombinedOperatorV2Module : public IModularModule
{
public:
    CIntCombinedOperatorV2Module(const std::string& Name, CCommandStackController& CommandStackController);
    ~CIntCombinedOperatorV2Module();

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
    std::shared_ptr<CIntCombinedOperatorV2Filter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
