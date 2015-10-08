#ifndef IntKarplusStrongMODULE_H
#define IntKarplusStrongMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CIntKarplusStrongFilter;
class CJackIOManager;
class CCommandStackController;

class CIntKarplusStrongModule : public IModularModule
{
public:
    CIntKarplusStrongModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CIntKarplusStrongModule();

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
    std::shared_ptr<CIntKarplusStrongFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // IntKarplusStrongMODULE_H
