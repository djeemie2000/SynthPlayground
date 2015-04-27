#ifndef MODULARMODULEI_H
#define MODULARMODULEI_H

#include <string>
#include <vector>

class IModuleParameterVisitor;

class IModularModule
{
public:
    typedef std::vector<std::string> Names;

    virtual ~IModularModule(){}

    virtual std::string GetName() const =0;

    virtual Names GetInputNames() const =0;
    virtual Names GetOutputNames() const =0;
    virtual Names GetMidiInputNames() const =0;
    virtual Names GetMidiOutputNames() const =0;

    virtual void Accept(IModuleParameterVisitor& ParameterVisitor) const =0;
};

#endif // MODULARMODULEI_H
