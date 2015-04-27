#ifndef LPFMODULE_H
#define LPFMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CLpfFilter;
class CJackIOManager;
class CCommandStackController;

class CLpfModule : public IModularModule
{
public:
    CLpfModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CLpfModule();

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
    std::shared_ptr<CLpfFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // LPFMODULE_H
