#include "QCommandSender.h"
#include "CommandStack.h"
#include "CommandStackController.h"

QCommandSender::QCommandSender(const std::string &Name, CCommandStackController& Handler, QObject *parent)
    : QObject(parent)
    , m_Name(Name)
    , m_Handler(Handler)
{
}

void QCommandSender::OnBoolChanged(bool Value)
{
    m_Handler.Handle(SCmdStackItem(m_Name).BoolValue(Value));
}

void QCommandSender::OnIntChanged(int Value)
{
    m_Handler.Handle(SCmdStackItem(m_Name).IntValue(Value));
}

void QCommandSender::OnDoubleChanged(double Value)
{
    m_Handler.Handle(SCmdStackItem(m_Name).FloatValue(static_cast<float>(Value)));
}

void QCommandSender::OnChanged()
{
    m_Handler.Handle(SCmdStackItem(m_Name));
}
