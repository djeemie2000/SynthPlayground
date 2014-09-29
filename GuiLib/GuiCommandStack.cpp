#include "GuiCommandStack.h"
#include <QWidget>
#include <QToolButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include "QCommandSender.h"
#include "QCommandStackHandler.h"
#include "CommandStackController.h"
#include "CommandStackHandlerI.h"

void ConnectToolButton(QToolButton* Button, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller)
{
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Controller, Parent);
    Parent->connect(Button, SIGNAL(clicked(bool)), Sender, SLOT(OnBoolChanged(bool)));
    // controller -> gui
    // need to get feedback from controller ???
}

void ConnectCheckableToolButton(QToolButton* Button, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller)
{
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Controller, Parent);
    Parent->connect(Button, SIGNAL(clicked(bool)), Sender, SLOT(OnBoolChanged(bool)));
    // controller -> gui
    QCommandStackHandler* Reciever = new QCommandStackHandler();//no ownership by parent!
    Parent->connect(Reciever, SIGNAL(SignalBoolValueChanged(bool)), Button, SLOT(setChecked(bool)));
    Controller.Register(ParameterName, SPCommandStackHandler(Reciever));
}

void ConnectSpinbox(QSpinBox* SpinBox, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller)
{
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Controller, Parent);
    Parent->connect(SpinBox, SIGNAL(valueChanged(int)), Sender, SLOT(OnIntChanged(int)));
    // controller -> gui
    QCommandStackHandler* Reciever = new QCommandStackHandler();//no ownership by parent!
    Parent->connect(Reciever, SIGNAL(SignalIntValueChanged(int)), SpinBox, SLOT(setValue(int)));
    Controller.Register(ParameterName, SPCommandStackHandler(Reciever));
}

void ConnectDoubleSpinbox(QDoubleSpinBox* SpinBox, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller)
{
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Controller, Parent);
    Parent->connect(SpinBox, SIGNAL(valueChanged(double)), Sender, SLOT(OnDoubleChanged(double)));
    // controller -> gui
    QCommandStackHandler* Reciever = new QCommandStackHandler();//no ownership by parent!
    Parent->connect(Reciever, SIGNAL(SignalDoubleValueChanged(double)), SpinBox, SLOT(setValue(double)));
    Controller.Register(ParameterName, SPCommandStackHandler(Reciever));
}

void ConnectCombobox(QComboBox* ComboBox, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller)
{
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Controller, Parent);
    Parent->connect(ComboBox, SIGNAL(currentIndexChanged(int)), Sender, SLOT(OnIntChanged(int)));
    // controller -> gui
    QCommandStackHandler* Reciever = new QCommandStackHandler();//no ownership by parent!
    Parent->connect(Reciever, SIGNAL(SignalIntValueChanged(int)), ComboBox, SLOT(setCurrentIndex(int)));
    Controller.Register(ParameterName, SPCommandStackHandler(Reciever));
}

void ConnectPushButton(QPushButton* Button, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller)
{
    // not checkable push button!
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Controller, Parent);
    Parent->connect(Button, SIGNAL(clicked(bool)), Sender, SLOT(OnBoolChanged(bool)));
    // need to get feedback from controller ???
}

