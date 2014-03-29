
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Synth2
TEMPLATE = app

CONFIG   += c++11 (Qt5)

SOURCES += main.cpp\
        mainwindow.cpp \
    Controller.cpp \
    QAudioIoDevice.cpp \
    QView.cpp

HEADERS  += mainwindow.h \
    Controller.h \
    WriteWavFile.h \
    ReadWavFile.h \
    QAudioIoDevice.h \
    GranularSamplePlayer.h \
    PhaseStep.h \
    View.h \
    QView.h \
    SampleGrabber.h \
    PseudoSin.h \
    FullPseudoSin.h \
    NoOp.h \
    RampUp.h \
    RampDown.h \
    Square.h \
    InvSquare.h \
    PhaseGenerator.h \
    FeedbackOperator.h \
    FlipOperator.h \
    MirrorOperator.h \
    HardKneeShaper.h \
    CenteredShaper.h \
    PhaseDecreaseCondition.h

FORMS    += mainwindow.ui
