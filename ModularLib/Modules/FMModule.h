#ifndef FMMODULE_H
#define FMMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CFMFilter;
class CJackIOManager;
class CCommandStackController;

class CFMModule : public IModularModule
{
public:
    CFMModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CFMModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;

    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();

    CCommandStackController& m_CommandStackController;
    std::string m_Name;
    std::shared_ptr<CFMFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // FMMODULE_H
