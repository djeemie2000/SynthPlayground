#ifndef MidiStepSequencerMODULE_H
#define MidiStepSequencerMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CMidiStepSequencerFilter;
class CJackIOManager;
class CCommandStackController;

class CMidiStepSequencerModule : public IModularModule
{
public:
    CMidiStepSequencerModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CMidiStepSequencerModule();

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
    CCommandStackController& m_CommandStackController;
    std::shared_ptr<CMidiStepSequencerFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // MidiStepSequencerMODULE_H
