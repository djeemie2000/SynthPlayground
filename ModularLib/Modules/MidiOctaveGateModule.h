#pragma once

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CMidiOctaveGateFilter;
class CJackIOManager;
class CCommandStackController;

class CMidiOctaveGateModule : public IModularModule
{
public:
    CMidiOctaveGateModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CMidiOctaveGateModule();

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
    std::shared_ptr<CMidiOctaveGateFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};
