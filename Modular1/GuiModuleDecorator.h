#ifndef GUIMODULEDECORATOR_H
#define GUIMODULEDECORATOR_H

#include <memory>
#include <string>
#include "ModularModuleI.h"

class QMainWindow;
class QDockWidget;

class CGuiModuleDecorator : public IModularModule
{
public:
    CGuiModuleDecorator(std::shared_ptr<IModularModule> Module, QMainWindow* MainWindow, QDockWidget* DockWidget);
    ~CGuiModuleDecorator();

    std::string GetName() const override;

private:
    std::shared_ptr<IModularModule> m_Module;
    QMainWindow* m_MainWindow;
    QDockWidget* m_DockWidget;
};

#endif // GUIMODULEDECORATOR_H
