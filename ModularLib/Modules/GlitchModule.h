#ifndef GlitchMODULE_H
#define GlitchMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CGlitchFilter;
class CJackIOManager;
class CCommandStackController;

class CGlitchModule : public IModularModule
{
public:
    CGlitchModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CGlitchModule();

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
    std::shared_ptr<CGlitchFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // GlitchMODULE_H
