#ifndef WaveShaperA116MODULE_H
#define WaveShaperA116MODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class IAudioFilter;
class CJackIOManager;

class CWaveShaperA116Module : public IModularModule
{
public:
    CWaveShaperA116Module(const std::string& Name);
    ~CWaveShaperA116Module();

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
    std::shared_ptr<IAudioFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // WaveShaperA116MODULE_H
