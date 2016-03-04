#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CExtendedCombFilterFilter;
class CJackIOManager;
class CCommandStackController;

class CExtendedCombFilterModule : public IModularModule
{
public:
    CExtendedCombFilterModule(const std::string& Name);
    ~CExtendedCombFilterModule();

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
    std::shared_ptr<CExtendedCombFilterFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
