#include "MidiInputHandlerI.h"
#include "LogMidiInputHandler.h"
#include "MidiInput.h"

using namespace std;

int main()
{
    CLogMidiInputHandler Handler;
    CMidiInput MidiInput(Handler);
    if(MidiInput.OpenMidiInput("TestAlsa", "MidiIn"))
    {
        int Cntr = 40;
        while(0<Cntr)
        {
            MidiInput.Run();
            --Cntr;
        }
    }
    MidiInput.CloseMidiInput();
    return 0;
}
