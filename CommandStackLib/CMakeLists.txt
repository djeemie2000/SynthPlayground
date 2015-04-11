cmake_minimum_required (VERSION 2.6)
project (CommandStackLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

add_library(CommandStackLib
    CommandStack.cpp
    CommandStackController.cpp
    LogCommandStackHandler.cpp
    ExportCommandStackHandler.cpp
    CommandStackImporter.cpp
    ExecuteCommandStackHandler.cpp
    MultiCommandStackHandler.cpp
    CommandStackDistributor.cpp
    CommandStack.h
    CommandStackController.h
    CommandStackHandlerI.h
    ImporterI.h
    LogCommandStackHandler.h
    ExporterI.h
    ExportCommandStackHandler.h
    CommandStackImporter.h
    ExecuteCommandStackHandler.h
    MultiCommandStackHandler.h
    RegisterNamedCommandStackHandlerI.h
    CommandStackDistributor.h)

