#ifndef KarplusStrongMODULE_H
#define KarplusStrongMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CKarplusStrongFilter;
class CJackIOManager;
class CCommandStackController;

class CKarplusStrongModule : public IModularModule
{
public:
    CKarplusStrongModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CKarplusStrongModule();

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
    std::shared_ptr<CKarplusStrongFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // KarplusStrongMODULE_H
