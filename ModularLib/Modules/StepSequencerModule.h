#ifndef StepSequencerMODULE_H
#define StepSequencerMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CStepSequencerFilter;
class CJackIOManager;
class CCommandStackController;

class CStepSequencerModule : public IModularModule
{
public:
    CStepSequencerModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CStepSequencerModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;
    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();
    void SetCurrentStepIndex(int Index);

    std::string m_Name;
    CCommandStackController& m_CommandStackController;
    std::shared_ptr<CStepSequencerFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
    int m_CurrentStep;
};

#endif // StepSequencerMODULE_H
