#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CWaveTableFilter;
class CJackIOManager;
class CCommandStackController;

class CWaveTableModule : public IModularModule
{
public:
    CWaveTableModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CWaveTableModule();

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
    std::shared_ptr<CWaveTableFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
