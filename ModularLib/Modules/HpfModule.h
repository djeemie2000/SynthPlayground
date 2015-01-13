#ifndef HpfMODULE_H
#define HpfMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CHpfFilter;
class CJackIOManager;
class CCommandStackController;

class CHpfModule : public IModularModule
{
public:
    CHpfModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CHpfModule();

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
    std::shared_ptr<CHpfFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // HpfMODULE_H
