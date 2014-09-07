#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CPosNegShaperFilter;
class CJackIOManager;
class CCommandStackController;

class CPosNegShaperModule : public IModularModule
{
public:
    CPosNegShaperModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CPosNegShaperModule();

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
    std::shared_ptr<CPosNegShaperFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
