#ifndef MidiLoggerMODULE_H
#define MidiLoggerMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CMidiLoggerFilter;
class CJackIOManager;

class CMidiLoggerModule : public IModularModule
{
public:
    CMidiLoggerModule(const std::string& Name);
    ~CMidiLoggerModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;

    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();

    std::string m_Name;
    std::shared_ptr<CMidiLoggerFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // MidiLoggerMODULE_H
