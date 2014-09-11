#ifndef DetunerMODULE_H
#define DetunerMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CDetunerFilter;
class CJackIOManager;
class CCommandStackController;

class CDetunerModule : public IModularModule
{
public:
    CDetunerModule(const std::string& Name, int Size, CCommandStackController& CommandStackController);
    ~CDetunerModule();

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
    int m_Size;
    std::shared_ptr<CDetunerFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // DetunerMODULE_H
