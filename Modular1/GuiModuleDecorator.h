#ifndef GUIMODULEDECORATOR_H
#define GUIMODULEDECORATOR_H

#include <memory>
#include <string>
#include "ModularModuleI.h"

class QWidget;
class QTabWidget;

class CModuleGuiDecorator : public IModularModule
{
public:
    CModuleGuiDecorator(std::shared_ptr<IModularModule> Module, QTabWidget* Parent, QWidget* Widget);
    ~CModuleGuiDecorator();

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
