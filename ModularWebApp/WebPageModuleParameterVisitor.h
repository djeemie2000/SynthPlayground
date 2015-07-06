#pragma once

#include <string>
#include <sstream>
#include "ModuleParameterVisitorI.h"

class CCommandStackController;

class CWebPageModuleParameterVisitor : public IModuleParameterVisitor
{
public:
    CWebPageModuleParameterVisitor(CCommandStackController &CommandStackController);

    void Start() override;
    void StartLine() override;
    void FloatParameter(const std::string& ParameterName, const std::string& Name, float Default, float Min, float Max, float Step, int NumDecimals) override;
    void IntegerParameter(const std::string& ParameterName, const std::string& Name, int Default, int Min, int Max, int Step) override;
    void SelectionParameter(const std::string& ParameterName, const std::string& Name, int Default, const std::vector<std::string>& Selections) override;
    void BooleanParameter(const std::string& ParameterName, const std::string& Name, bool Default) override;
    void FilePathParameter(const std::string& ParameterName, const std::string& Name, const std::string& Extensions) override;
    void BooleanStatus(const std::string& ParameterName, const std::string& Name, bool Default) override;
    void FinishLine() override;
    void Finish() override;

    std::string GetContent() const;

private:
    CCommandStackController& m_CommandStackController;
    std::ostringstream m_Content;
};
