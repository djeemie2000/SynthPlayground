cmake_minimum_required (VERSION 2.6)
project (CommandStackLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

add_library(CommandStackLib
    CommandStackItem.cpp
    CommandStackItem.h
    CommandStackController.cpp
    CommandStackController.h
    CommandStackHandlerI.h
    LogCommandStackHandler.cpp
    LogCommandStackHandler.h
    ExportCommandStackHandler.cpp
    ExportCommandStackHandler.h
    CommandStackImporter.cpp
    CommandStackImporter.h
    ExecuteCommandStackHandler.cpp
    ExecuteCommandStackHandler.h
    MultiCommandStackHandler.cpp
    MultiCommandStackHandler.h
    RegisterNamedCommandStackHandlerI.h
    CommandStackDistributor.cpp
    CommandStackDistributor.h
    CommandStack.cpp
    CommandStack.h
    StackCommandStackHandler.cpp
    StackCommandStackHandler.h
)

