#ifndef QCOMMANDSENDER_H
#define QCOMMANDSENDER_H

#include <string>
#include <QObject>

class CCommandStackController;

class QCommandSender : public QObject
{
    Q_OBJECT
public:
    explicit QCommandSender(const std::string& Name, CCommandStackController& Handler, QObject *parent = 0);

signals:

public slots:
    void OnBoolChanged(bool Value);
    void OnIntChanged(int Value);
    void OnDoubleChanged(double Value);
    void OnChanged();

private:
    std::string m_Name;
    CCommandStackController& m_Handler;
};

#endif // QCOMMANDSENDER_H
