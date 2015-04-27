#ifndef MultiStageWaveFolderMODULE_H
#define MultiStageWaveFolderMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CMultiStageWaveFolderFilter;
class CJackIOManager;
class CCommandStackController;

class CMultiStageWaveFolderModule : public IModularModule
{
public:
    CMultiStageWaveFolderModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CMultiStageWaveFolderModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;
    Names GetMidiOutputNames() const override {  return {};  }
    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();

    CCommandStackController& m_CommandStackController;
    std::string m_Name;
    std::shared_ptr<CMultiStageWaveFolderFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // MultiStageWaveFolderMODULE_H
