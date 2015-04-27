#ifndef LFOBANKMODULE_H
#define LFOBANKMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CLFOBankFilter;
class CJackIOManager;
class CCommandStackController;

class CLFOBankModule : public IModularModule
{
public:
    CLFOBankModule(const std::string& Name, int Size, CCommandStackController& CommandStackController);
    ~CLFOBankModule();

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
    int m_Size;
    std::shared_ptr<CLFOBankFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // LFOBANKMODULE_H
