#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CDelayVerbFilter;
class CJackIOManager;

class CDelayVerbModule : public IModularModule
{
public:
    CDelayVerbModule(const std::string& Name);
    ~CDelayVerbModule();

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
    std::shared_ptr<CDelayVerbFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
