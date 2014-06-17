#ifndef IMPORTERI_H
#define IMPORTERI_H

class IImporter
{
public:
    virtual ~IImporter(){}

    virtual bool Import(const std::string& Path) =0;

    virtual bool Default() =0;
};

#endif // IMPORTERI_H
