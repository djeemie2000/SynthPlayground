#ifndef PeriodicTriggerMODULE_H
#define PeriodicTriggerMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CPeriodicTriggerFilter;
class CJackIOManager;
class CCommandStackController;

class CPeriodicTriggerModule : public IModularModule
{
public:
    CPeriodicTriggerModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CPeriodicTriggerModule();

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
    std::shared_ptr<CPeriodicTriggerFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // PeriodicTriggerMODULE_H
