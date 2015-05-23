cmake_minimum_required (VERSION 2.6)
project (ModularWeb)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../JackLib ./../MidiLib ./../CommandStackLib ./../SynthLib ./../SynthLib/Granular ./../ModularLib ./../ModularLib/Modules ./../ModularLib/Filters ./../Utilities ./../TinyXml2 ./../Mongoose)
#todo win32 support

add_executable(ModularWeb
    main.cpp
    ModularWebController.cpp
    ModularWebController.h
    WebPageManager.cpp
    WebPageManager.h
    WebPageHelpers.cpp
    WebPageHelpers.h
    WebPageModuleParameterVisitor.cpp
    WebPageModuleParameterVisitor.h
    WebRequest.cpp
    WebRequest.h
    PatchManager.cpp
    PatchManager.h
)

target_link_libraries(ModularWeb ModularLib SynthLib JackLib MidiLib CommandStackLib Utilities TinyXml2 Mongoose jack)
