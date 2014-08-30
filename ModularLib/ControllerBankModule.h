#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CControllerBankFilter;
class CJackIOManager;
class CCommandStackController;

class CControllerBankModule : public IModularModule
{
public:
    CControllerBankModule(const std::string& Name, int Size, CCommandStackController& CommandStackController);
    ~CControllerBankModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;

    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();

    CCommandStackController& m_CommandStackController;
    std::string m_Name;
    int m_Size;
    std::shared_ptr<CControllerBankFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
