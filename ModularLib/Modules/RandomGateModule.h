#ifndef RandomGateMODULE_H
#define RandomGateMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CRandomGateFilter;
class CJackIOManager;
class CCommandStackController;

class CRandomGateModule : public IModularModule
{
public:
    CRandomGateModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CRandomGateModule();

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
    std::shared_ptr<CRandomGateFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // RandomGateMODULE_H
