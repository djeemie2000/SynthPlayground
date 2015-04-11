cmake_minimum_required (VERSION 2.6)
project (JackLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../SynthLib ./../MidiLib)
#todo if win32 include path to jack!

add_library(JackLib
    JackIOManager.cpp
    JackMidiSource.cpp
    JackConnectionManager.cpp
    JackMidiRenderer.cpp
    JackMidiHandler.cpp    
    JackIOManager.h
    JackMidiSource.h
    JackConnectionManager.h
    JackMidiRenderer.h
    JackMidiHandler.h
    JackWin32Port.h
    IConnectionChangedListener.h)
