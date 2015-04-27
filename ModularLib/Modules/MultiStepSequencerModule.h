#ifndef MultiStepSequencerMODULE_H
#define MultiStepSequencerMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CMultiStepSequencerFilter;
class CJackIOManager;
class CCommandStackController;

class CMultiStepSequencerModule : public IModularModule
{
public:
    CMultiStepSequencerModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CMultiStepSequencerModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;
    Names GetMidiOutputNames() const override {  return {};  }
    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();
    void SetCurrentStepIndex(int Index);

    std::string m_Name;
    CCommandStackController& m_CommandStackController;
    std::shared_ptr<CMultiStepSequencerFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
    int m_CurrentStep;
};

#endif // MultiStepSequencerMODULE_H
