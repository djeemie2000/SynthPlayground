#ifndef UnipolarLimiterMODULE_H
#define UnipolarLimiterMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class IAudioFilter;
class CJackIOManager;

class CUnipolarLimiterModule : public IModularModule
{
public:
    CUnipolarLimiterModule(const std::string& Name);
    ~CUnipolarLimiterModule();

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

#endif // UnipolarLimiterMODULE_H
