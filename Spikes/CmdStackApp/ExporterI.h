#ifndef EXPORTERI_H
#define EXPORTERI_H

#include <string>

class IExporter
{
public:
    virtual ~IExporter(){}

    virtual bool Export(const std::string& Path) =0;
};

#endif // EXPORTERI_H
