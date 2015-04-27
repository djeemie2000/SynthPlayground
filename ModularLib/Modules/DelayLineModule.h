#ifndef DelayLineMODULE_H
#define DelayLineMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CDelayLineFilter;
class CJackIOManager;
class CCommandStackController;

class CDelayLineModule  : public IModularModule
{
public:
    CDelayLineModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CDelayLineModule();

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
    std::shared_ptr<CDelayLineFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // DelayLineMODULE_H
