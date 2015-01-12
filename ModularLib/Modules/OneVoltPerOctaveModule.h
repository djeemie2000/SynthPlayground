#ifndef OneVoltPerOctaveMODULE_H
#define OneVoltPerOctaveMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class IAudioFilter;
class CJackIOManager;

class COneVoltPerOctaveModule : public IModularModule
{
public:
    COneVoltPerOctaveModule(const std::string& Name);
    ~COneVoltPerOctaveModule();

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

#endif // OneVoltPerOctaveMODULE_H
