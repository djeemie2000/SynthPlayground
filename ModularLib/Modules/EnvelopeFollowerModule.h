#ifndef EnvelopeFollowerMODULE_H
#define EnvelopeFollowerMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CEnvelopeFollowerFilter;
class CJackIOManager;
class CCommandStackController;

class CEnvelopeFollowerModule : public IModularModule
{
public:
    CEnvelopeFollowerModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CEnvelopeFollowerModule();

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
    std::shared_ptr<CEnvelopeFollowerFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // EnvelopeFollowerMODULE_H
