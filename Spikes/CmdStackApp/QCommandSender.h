#ifndef QCOMMANDSENDER_H
#define QCOMMANDSENDER_H

#include <string>
#include <QObject>

class ICommandStackHandler;

class QCommandSender : public QObject
{
    Q_OBJECT
public:
    explicit QCommandSender(const std::string& Name, ICommandStackHandler& Handler, QObject *parent = 0);

signals:

public slots:
    void OnBoolChanged(bool Value);
    void OnIntChanged(int Value);
    void OnDoubleChanged(double Value);
    void OnChanged();

private:
    std::string m_Name;
    ICommandStackHandler& m_Handler;
};

#endif // QCOMMANDSENDER_H
