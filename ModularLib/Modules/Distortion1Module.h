#ifndef Distortion1MODULE_H
#define Distortion1MODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CDistortion1Filter;
class CJackIOManager;
class CCommandStackController;

class CDistortion1Module : public IModularModule
{
public:
    CDistortion1Module(const std::string& Name, CCommandStackController& CommandStackController);
    ~CDistortion1Module();

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
    std::shared_ptr<CDistortion1Filter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
};

#endif // Distortion1MODULE_H
