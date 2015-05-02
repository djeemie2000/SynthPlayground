cmake_minimum_required (VERSION 2.6)
project (MidiLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

add_library(MidiLib
    LogMidiInputHandler.cpp
    NoteQueueMidiInputHandler.cpp
    NoteCountMidiHandler.cpp
    MidiNotePitch.cpp
    MultiMidiHandler.cpp
    RawMidiParser.cpp
    MidiHandlerI.h
    LogMidiInputHandler.h
    NoteQueueMidiInputHandler.h
    NoteCountMidiHandler.h
    MidiSourceI.h
    MidiRendererI.h
    MidiNotePitch.h
    MultiMidiHandler.h
    RawMidiParser.h
)
