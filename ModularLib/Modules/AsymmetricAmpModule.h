#ifndef AsymmetricAmpMODULE_H
#define AsymmetricAmpMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CAsymmetricAmpFilter;
class CJackIOManager;
class CCommandStackController;

class CAsymmetricAmpModule : public IModularModule
{
public:
    CAsymmetricAmpModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CAsymmetricAmpModule();

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
    std::shared_ptr<CAsymmetricAmpFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // AsymmetricAmpMODULE_H
