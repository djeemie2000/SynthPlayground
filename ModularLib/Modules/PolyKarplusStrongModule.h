#ifndef PolyKarplusStrongMODULE_H
#define PolyKarplusStrongMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CPolyKarplusStrongFilter;
class CJackIOManager;
class CCommandStackController;

class CPolyKarplusStrongModule : public IModularModule
{
public:
    CPolyKarplusStrongModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CPolyKarplusStrongModule();

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
    std::shared_ptr<CPolyKarplusStrongFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // PolyKarplusStrongMODULE_H
