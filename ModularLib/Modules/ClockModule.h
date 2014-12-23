#ifndef ClockMODULE_H
#define ClockMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CClockFilter;
class CJackIOManager;
class CCommandStackController;

class CClockModule : public IModularModule
{
public:
    CClockModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CClockModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;
    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();

    std::string m_Name;
    CCommandStackController& m_CommandStackController;
    std::shared_ptr<CClockFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // ClockMODULE_H
