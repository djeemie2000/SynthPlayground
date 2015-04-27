#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CExtendedModulatorFilter;
class CJackIOManager;

class CExtendedModulatorModule : public IModularModule
{
public:
    CExtendedModulatorModule(const std::string& Name, int Size);
    ~CExtendedModulatorModule();

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
    int m_Size;
    std::shared_ptr<CExtendedModulatorFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
