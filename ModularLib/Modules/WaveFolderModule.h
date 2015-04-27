#ifndef WaveFolderMODULE_H
#define WaveFolderMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class IAudioFilter;
class CJackIOManager;

class CWaveFolderModule : public IModularModule
{
public:
    CWaveFolderModule(const std::string& Name);
    ~CWaveFolderModule();

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

#endif // WaveFolderMODULE_H
