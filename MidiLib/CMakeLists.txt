cmake_minimum_required (VERSION 2.6)
project (MidiLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../CommandStackLib)

add_library(MidiLib
    LogMidiInputHandler.cpp
    NoteQueueMidiInputHandler.cpp
    NoteCountMidiHandler.cpp
    CommandStackMidiInputHandler.cpp
    MidiInputController.cpp
    MidiNotePitch.cpp
    MultiMidiHandler.cpp
    RawMidiParser.cpp
    MidiHandlerI.h
    LogMidiInputHandler.h
    NoteQueueMidiInputHandler.h
    NoteCountMidiHandler.h
    CommandStackMidiInputHandler.h
    MidiInputController.h
    MidiControllerHandlerI.h
    MidiSourceI.h
    MidiRendererI.h
    MidiNotePitch.h
    MultiMidiHandler.h
    RawMidiParser.h)

