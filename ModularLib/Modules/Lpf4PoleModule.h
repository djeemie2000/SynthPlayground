#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CLpf4PoleFilter;
class CJackIOManager;
class CCommandStackController;

class CLpf4PoleModule : public IModularModule
{
public:
    CLpf4PoleModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CLpf4PoleModule();

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
    std::shared_ptr<CLpf4PoleFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
