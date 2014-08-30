#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CSimpleOscillatorFilter;
class CJackIOManager;
class CCommandStackController;

class CSimpleOscillatorModule : public IModularModule
{
public:
    CSimpleOscillatorModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CSimpleOscillatorModule();

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
    std::shared_ptr<CSimpleOscillatorFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
