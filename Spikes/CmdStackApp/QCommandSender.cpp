#include "QCommandSender.h"
#include "CommandStack.h"

QCommandSender::QCommandSender(const std::string &Name, ICommandStackHandler& Handler, QObject *parent)
    : QObject(parent)
    , m_Name(Name)
    , m_Handler(Handler)
{
}

void QCommandSender::OnBoolChanged(bool Value)
{
    m_Handler.Handle({m_Name, Value, 0, 0.0f});
}

void QCommandSender::OnIntChanged(int Value)
{
    m_Handler.Handle({m_Name, false, Value, 0.0f});
}

void QCommandSender::OnDoubleChanged(double Value)
{
    m_Handler.Handle({m_Name, false, 0, static_cast<float>(Value)});
}

void QCommandSender::OnChanged()
{
    m_Handler.Handle({m_Name, false, 0, 0.0f});
}
