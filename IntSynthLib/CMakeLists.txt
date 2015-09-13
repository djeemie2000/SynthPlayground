cmake_minimum_required (VERSION 2.6)
project (IntSynthLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(
        .
)
#todo if win32 include path to jack!

add_library(SynthLib
    IntCombinors.h
    IntConversions.h
    IntEnvelope.h
    IntInterpolator.h
    IntNoise.h
    IntOnePoleFilter.h
    IntOperators.h
    IntPhaseGenerator.h
)

