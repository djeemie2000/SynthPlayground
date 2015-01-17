#ifndef GranularMODULE_H
#define GranularMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CGranularFilter;
class CJackIOManager;
class CCommandStackController;

class CGranularModule : public IModularModule
{
public:
    CGranularModule(const std::string& Name, CCommandStackController& CommandStackController);
    ~CGranularModule();

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
    std::shared_ptr<CGranularFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // GranularMODULE_H
