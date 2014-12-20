#ifndef COUNTMODULEPARAMETERVISITOR_H
#define COUNTMODULEPARAMETERVISITOR_H

#include "ModuleParameterVisitorI.h"

class CCountModuleParameterVisitor : public IModuleParameterVisitor
{
public:
    CCountModuleParameterVisitor();

    void Start() override;
    void StartLine() override;
    void FloatParameter(const std::string& ParameterName, const std::string& Name, float Default, float Min, float Max, float Step, int NumDecimals) override;
    void IntegerParameter(const std::string& ParameterName, const std::string& Name, int Default, int Min, int Max, int Step) override;
    void SelectionParameter(const std::string& ParameterName, const std::string& Name, int Default, const std::vector<std::string>& Selections) override;
    void BooleanParameter(const std::string& ParameterName, const std::string& Name, bool Default) override;
    void BooleanStatus(const std::string& ParameterName, const std::string& Name, bool Default) override;
    void FinishLine() override;
    void Finish() override;

    int GetParameterCount() const;

private:
    int m_ParameterCount;
};

#endif // COUNTMODULEPARAMETERVISITOR_H
