#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CMidiControllerBankFilter;
class CJackIOManager;
class CCommandStackController;

class CMidiControllerBankModule : public IModularModule
{
public:
    CMidiControllerBankModule(const std::string& Name, int Size, CCommandStackController& CommandStackController);
    ~CMidiControllerBankModule();

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
    std::shared_ptr<CMidiControllerBankFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
