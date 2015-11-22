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

add_library(IntSynthLib
    IntCombinors.h
    IntConversions.h
    IntEnvelope.h
    IntInterpolator.h
    IntNoise.h
    IntOnePoleFilter.h
    IntOperators.h
    IntPhaseGenerator.h
    IntCombinedOperator.h
    IntSimpleOscillator.h 
    IntMultiSaw.h
    IntOperatorFactory.h
    IntSimpleOscillator.h
    IntCombinedOperator.h
    IntCombinorFactory.h
    IntDelayLine.h
    IntKarplusStrong.h
    IntDeltaSmooth.h
    IntFeedbackDelay.h
    IntSkewer2D.h
    IntScaledValue.h
    Dummy.cpp
)

