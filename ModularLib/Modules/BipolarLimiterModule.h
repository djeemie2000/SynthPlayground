#ifndef BipolarLimiterMODULE_H
#define BipolarLimiterMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class IAudioFilter;
class CJackIOManager;

class CBipolarLimiterModule : public IModularModule
{
public:
    CBipolarLimiterModule(const std::string& Name);
    ~CBipolarLimiterModule();

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

#endif // BipolarLimiterMODULE_H