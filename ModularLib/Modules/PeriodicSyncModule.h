#ifndef PeriodicSyncMODULE_H
#define PeriodicSyncMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class IAudioFilter;
class CJackIOManager;

class CPeriodicSyncModule : public IModularModule
{
public:
    CPeriodicSyncModule(const std::string& Name);
    ~CPeriodicSyncModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;
    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();

    std::string m_Name;
    std::shared_ptr<IAudioFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // PeriodicSyncMODULE_H
