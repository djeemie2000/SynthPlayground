#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CModulatorFilter;
class CJackIOManager;
class CCommandStackController;

class CModulatorModule : public IModularModule
{
public:
    CModulatorModule(const std::string& Name, int Size, CCommandStackController& CommandStackController);
    ~CModulatorModule();

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
    int m_Size;
    std::shared_ptr<CModulatorFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
