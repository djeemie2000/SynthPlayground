TARGET = IntSynthLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)
QMAKE_CXXFLAGS += -std=c++11

HEADERS += IntCombinors.h \
    IntConversions.h \
    IntEnvelope.h \
    IntInterpolator.h \
    IntNoise.h \
    IntOnePoleFilter.h \
    IntOperators.h \
    IntPhaseGenerator.h \
    IntMultiSaw.h \
    IntoperatorFactory.h \
    IntSimpleOscillator.h \
    IntCombinedOperator.h \
    IntCombinorFactory.h \
    IntDelayLine.h \
    IntKarplusStrong.h \
    IntDeltaSmooth.h \
    IntFeedbackDelay.h \
    IntSkewer2D.h \
    IntScaledValue.h \
    IntUtilities.h \
    IntMultiStageEnvelope.h \
    IntBinaryPattern.h \
    IntCombinedOperatorV2.h \
    IntWaveFolder.h \
    UintSkewedPhasor.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/IntSynthLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/IntSynthLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
