#ifndef MODULEGUIPARAMETERVISITOR_H
#define MODULEGUIPARAMETERVISITOR_H

#include "ModuleParameterVisitorI.h"

class QGroupBox;
class QWidget;
class CCommandStackController;

class CModuleGuiParameterVisitor : public IModuleParameterVisitor
{
public:
    CModuleGuiParameterVisitor(QGroupBox* GroupBox, QWidget* Parent, CCommandStackController& CommandStackController);

    void Start() override;
    void FloatParameter(const std::string& ParameterName, const std::string& Name, float Default, float Min, float Max, float Step, int NumDecimals) override;
    void IntegerParameter(const std::string& ParameterName, const std::string& Name, int Default, int Min, int Max, int Step) override;
    void SelectionParameter(const std::string& ParameterName, const std::string& Name, int Default, const std::vector<std::string>& Selections) override;
//    void BooleanParameter(const std::string& ParameterName, const std::string& Name, bool Default) override;
//    void TriggeredParameter(const std::string& ParameterName, const std::string& Name) override;
//    void FilePathParameter(const std::string& ParameterName, const std::string& Name, const std::string& Extensions) override;
    virtual void Finish() override;

private:
    CCommandStackController& m_CommandStackController;
    QGroupBox* m_GroupBox;
    QWidget* m_Parent;
};

#endif // MODULEGUIPARAMETERVISITOR_H
