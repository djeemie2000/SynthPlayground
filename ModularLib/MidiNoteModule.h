#ifndef MIDINOTEMODULE_H
#define MIDINOTEMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CMidiNoteFilter;
class CJackIOManager;
class CCommandStackController;

class CMidiNoteModule : public IModularModule
{
public:
    CMidiNoteModule(const std::string& Name);
    ~CMidiNoteModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;

    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();

    std::string m_Name;
    std::shared_ptr<CMidiNoteFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // MIDINOTEMODULE_H
