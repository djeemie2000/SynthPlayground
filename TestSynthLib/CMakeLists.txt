cmake_minimum_required (VERSION 2.6)
project (TestSynthLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

include_directories(./../SynthLib ./../SynthLib/Controllers ./../SynthLib/Granular ./../MidiLib ./../UnitTest)

add_executable(TestSynthLib
    main.cpp
    TestRampUp.cpp
    TestPeriodicConstGenerator.cpp
    TestStepSequencer2.cpp
    TestPerdiodicTicker.cpp
    TestNotes.cpp
    TestDelayLine.cpp
    TestDelayLine2.cpp
    TestFeedbackDelay.cpp
    TestAREnvelope.cpp
    TestConstNumSamplesGenerator.cpp
    TestPeriodicSampleGrabber.cpp
    TestFMOperatorStage.cpp
    TestADSREnvelope.cpp
    TestPosNegShaper.cpp
    TestLinSegOperator.cpp
    TestDetune.cpp
    TestWaveFolder2.cpp
    TestNoise.cpp
    TestGlitchOperator.cpp
    TestMultiStepSequencer.cpp
    TestTrigger.cpp
    TestDecayEnvelope.cpp
    TestClockPulse.cpp
    TestPitch.cpp
    TestFMFrequencyModulator.cpp
    TestRandomGate.cpp
    TestSlewLimiter.cpp
    TestOneVoltPerOctave.cpp
    TestOnePoleFilter.cpp
    TestBufferGrabber.cpp
    TestGrainBank.cpp
    TestPhaseShifter.cpp
    TestWaveTable2.cpp
    testkarplusstrong.cpp
    TestToggleGate.cpp
    TestReadWriteBuffer.cpp
    TestSimpleReadWriteBuffer.cpp
    TestWaveShaperA116.cpp
    TestCombinedOperator.cpp
)

target_link_libraries(TestSynthLib SynthLib UnitTest)
