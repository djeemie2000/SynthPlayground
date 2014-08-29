#ifndef MODULEPARAMETERVISITORI_H
#define MODULEPARAMETERVISITORI_H

#include <string>
#include <vector>

class IModuleParameterVisitor
{
public:
    virtual ~IModuleParameterVisitor(){}

    virtual void Start() =0;
    virtual void FloatParameter(const std::string& ParameterName, const std::string& Name, float Default, float Min, float Max, float Step, int NumDecimals) =0;
//    virtual void IntegerParameter(const std::string& ParameterName, const std::string& Name, int Default, int Min, int Max, int Step) =0;
    virtual void SelectionParameter(const std::string& ParameterName, const std::string& Name, int Default, const std::vector<std::string>& Selections) =0;
//    virtual void BooleanParameter(const std::string& ParameterName, const std::string& Name, bool Default) =0;
//    virtual void TriggeredParameter(const std::string& ParameterName, const std::string& Name) =0;
//    virtual void FilePathParameter(const std::string& ParameterName, const std::string& Name, const std::string& Extensions) =0;
    virtual void Finish() =0;
};

#endif // MODULEPARAMETERVISITORI_H
