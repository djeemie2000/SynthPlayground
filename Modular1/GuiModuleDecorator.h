#ifndef GUIMODULEDECORATOR_H
#define GUIMODULEDECORATOR_H

#include <memory>
#include <string>
#include "ModularModuleI.h"

class QMainWindow;
class QDockWidget;

class CModuleGuiDecorator : public IModularModule
{
public:
    CModuleGuiDecorator(std::shared_ptr<IModularModule> Module, QMainWindow* MainWindow, QDockWidget* DockWidget);
    ~CModuleGuiDecorator();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;
    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    std::shared_ptr<IModularModule> m_Module;
    QMainWindow* m_MainWindow;
    QDockWidget* m_DockWidget;
};

#endif // GUIMODULEDECORATOR_H
