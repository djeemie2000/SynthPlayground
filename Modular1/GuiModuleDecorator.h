#ifndef GUIMODULEDECORATOR_H
#define GUIMODULEDECORATOR_H

#include <memory>
#include <string>
#include "ModularModuleI.h"

class QWidget;
class QTabWidget;

class CGuiModuleDecorator : public IModularModule
{
public:
    CGuiModuleDecorator(std::shared_ptr<IModularModule> Module, QTabWidget* Parent, QWidget* Widget);
    ~CGuiModuleDecorator();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;
    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    std::shared_ptr<IModularModule> m_Module;
    QTabWidget* m_Parent;
    QWidget* m_Widget;
};

#endif // GUIMODULEDECORATOR_H
