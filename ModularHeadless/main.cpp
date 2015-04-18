#include <iostream>
#include <string>
#include "Pitch.h"
#include "ModularHeadlessController.h"

namespace
{

void DoInstantiations()
{
    CPitch Pitch;
}

void Usage()
{

}

}

int main(int argc, const char* argv[])
{
    if(2<=argc)
    {
        std::string Path(argv[1]);
        CModularWebController Controller;
        Controller.Load(Path);

        std::cout << "Opened patch " << Path << std::endl;
        std::cout << "Press 'q' to exit" << std::endl;
        // wait for key 'q'
        char Key = ' ';
        std::cin >> Key;

        return 0;
    }

    Usage();
	return -1;
}

