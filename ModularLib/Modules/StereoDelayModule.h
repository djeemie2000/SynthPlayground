#ifndef STEREODELAYMODULE_H
#define STEREODELAYMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CStereoDelayFilter;
class CJackIOManager;
class CCommandStackController;

class CStereoDelayModule  : public IModularModule
{
public:
    CStereoDelayModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CStereoDelayModule();

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
    std::shared_ptr<CStereoDelayFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // STEREODELAYMODULE_H
