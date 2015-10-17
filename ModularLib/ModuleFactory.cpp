#include "ModuleFactory.h"
#include "CommandStackController.h"

#include "AmpModule.h"
#include "ControllerBankModule.h"
#include "OperatorModule.h"
#include "PhasorModule.h"
#include "MidiNoteModule.h"
#include "LpfModule.h"
#include "LFOBankModule.h"
#include "SimpleOscillatorModule.h"
#include "StereoDelayModule.h"
#include "ADSREnvelopeBankModule.h"
#include "MixerModule.h"
#include "PhaseSkewerModule.h"
#include "CombinorModule.h"
#include "CrossMixerModule.h"
#include "ModulatorModule.h"
#include "WaveFolderModule.h"
#include "PosNegShaperModule.h"
#include "LinSegOperatorModule.h"
#include "DetunerModule.h"
#include "MultiStageWaveFolderModule.h"
#include "PeriodicSyncModule.h"
#include "Distortion1Module.h"
#include "NoiseModule.h"
#include "SampleAndHoldModule.h"
#include "GlitchModule.h"
#include "MidiStepSequencerModule.h"
#include "PeriodicTriggerModule.h"
#include "StepSequencerModule.h"
#include "MidiControllerBankModule.h"
#include "EnvelopeFollowerModule.h"
#include "DelayLineModule.h"
#include "StereoMixerModule.h"
#include "AsymmetricAmpModule.h"
#include "MultiStepSequencerModule.h"
#include "ClockModule.h"
#include "FMModule.h"
#include "RandomGateModule.h"
#include "ExtendedModulatorModule.h"
#include "LimiterModule.h"
#include "BipolarLimiterModule.h"
#include "UnipolarLimiterModule.h"
#include "SlewLimiterModule.h"
#include "OneVoltPerOctaveModule.h"
#include "HpfModule.h"
#include "GranularModule.h"
#include "PhaseShifterModule.h"
#include "WaveTableModule.h"
#include "KarplusStrongModule.h"
#include "DecayEnvelopeModule.h"
#include "ToggleGateModule.h"
#include "ScalerModule.h"
#include "ControllerChangeModule.h"
#include "RingSequencerModule.h"
#include "MidiOctaveGateModule.h"
#include "BasicSamplerModule.h"
#include "BinaryOscillatorModule.h"
#include "WaveShaperA116Module.h"
#include "CombinedOperatorModule.h"
#include "IntSimpleOscillatorModule.h"
#include "IntCombinedOperatorModule.h"
#include "IntKarplusStrongModule.h"
#include "IntFeedbackDelayModule.h"

CModuleFactory::CModuleFactory(std::shared_ptr<CCommandStackController> CommandStackController)
 : m_CommandStackController(CommandStackController)
{
}

std::shared_ptr<IModularModule> CModuleFactory::Create(const std::string &Type, const std::string &Name)
{
    std::shared_ptr<IModularModule> Module;

    if(Type=="Amp")
    {
        Module.reset(new CAmpModule(Name));
    }
    else if(Type == "ControllerBank(4)")
    {
        Module.reset(new CControllerBankModule(Name, 4, *m_CommandStackController));//TODO wp ipv ref
    }
    else if(Type == "ControllerBank(8)")
    {
        Module.reset(new CControllerBankModule(Name, 8, *m_CommandStackController));//TODO wp ipv ref
    }
    else if(Type == "Operator")
    {
        Module.reset(new COperatorModule(Name, *m_CommandStackController));//TODO wp ipv ref
    }
    else if(Type == "Phasor")
    {
        Module.reset(new CPhasorModule(Name));
    }
    else if(Type == "MidiNote")
    {
        Module.reset(new CMidiNoteModule(Name));
    }
    else if(Type == "LPF")
    {
        Module.reset(new CLpfModule(Name, *m_CommandStackController));
    }
    else if(Type == "HPF")
    {
        Module.reset(new CHpfModule(Name, *m_CommandStackController));
    }
    else if(Type == "LFOBank(4)")
    {
        Module.reset(new CLFOBankModule(Name, 4, *m_CommandStackController));
    }
    else if(Type == "LFOBank(8)")
    {
        Module.reset(new CLFOBankModule(Name, 8, *m_CommandStackController));
    }
    else if(Type == "SimpleOscillator")
    {
        Module.reset(new CSimpleOscillatorModule(Name, *m_CommandStackController));
    }
    else if(Type == "StereoDelay")
    {
        Module.reset(new CStereoDelayModule(Name, *m_CommandStackController));
    }
    else if(Type == "ADSREnvelopeBank(4)")
    {
        Module.reset(new CADSREnvelopeBankModule(Name, 4, *m_CommandStackController));
    }
    else if(Type == "ADSREnvelopeBank(8)")
    {
        Module.reset(new CADSREnvelopeBankModule(Name, 8, *m_CommandStackController));
    }
    else if(Type == "Mixer(4)")
    {
        Module.reset(new CMixerModule(Name, 4, *m_CommandStackController));
    }
    else if(Type == "Mixer(8)")
    {
        Module.reset(new CMixerModule(Name, 8, *m_CommandStackController));
    }
    else if(Type == "PhaseSkewer")
    {
        Module.reset(new CPhaseSkewerModule(Name));
    }
    else if(Type == "Combinor")
    {
        Module.reset(new CCombinorModule(Name, *m_CommandStackController));
    }
    else if(Type == "CrossMixer")
    {
        Module.reset(new CCrossMixerModule(Name));
    }
    else if(Type == "Modulator")
    {
        Module.reset(new CModulatorModule(Name, 2, *m_CommandStackController));
    }
    else if(Type == "WaveFolder")
    {
        Module.reset(new CWaveFolderModule(Name));
    }
    else if(Type == "PosNegShaper")
    {
        Module.reset(new CPosNegShaperModule(Name, *m_CommandStackController));
    }
    else if(Type == "LinSegOperator")
    {
        Module.reset(new CLinSegOperatorModule(Name));
    }
    else if(Type == "Detuner(3)")
    {
        Module.reset(new CDetunerModule(Name, 3, *m_CommandStackController));
    }
    else if(Type == "MultiStageWaveFolder")
    {
        Module.reset(new CMultiStageWaveFolderModule(Name, *m_CommandStackController));
    }
    else if(Type == "PeriodicSync")
    {
        Module.reset(new CPeriodicSyncModule(Name));
    }
    else if(Type == "Distortion1")
    {
        Module.reset(new CDistortion1Module(Name, *m_CommandStackController));
    }
    else if(Type == "Noise")
    {
        Module.reset(new CNoiseModule(Name));
    }
    else if(Type == "SampleAndHold")
    {
        Module.reset(new CSampleAndHoldModule(Name));
    }
    else if(Type == "Glitch")
    {
        Module.reset(new CGlitchModule(Name, *m_CommandStackController));
    }
    else if(Type == "MidiStepSequencer")
    {
        Module.reset(new CMidiStepSequencerModule(Name, *m_CommandStackController));
    }
    else if(Type == "StepSequencer")
    {
        Module.reset(new CStepSequencerModule(Name, *m_CommandStackController));
    }
    else if(Type == "PeriodicTrigger")
    {
        Module.reset(new CPeriodicTriggerModule(Name, *m_CommandStackController));
    }
    else if(Type == "MidiControllerBank(4)")
    {
        Module.reset(new CMidiControllerBankModule(Name, 4, *m_CommandStackController));
    }
    else if(Type == "EnvelopeFollower")
    {
        Module.reset(new CEnvelopeFollowerModule(Name, *m_CommandStackController));
    }
    else if(Type == "DelayLine")
    {
        Module.reset(new CDelayLineModule(Name, *m_CommandStackController));
    }
    else if(Type == "StereoMixer(4)")
    {
        Module.reset(new CStereoMixerModule(Name, 4, *m_CommandStackController));
    }
    else if(Type == "AsymmetricAmp")
    {
        Module.reset(new CAsymmetricAmpModule(Name, *m_CommandStackController));
    }
    else if(Type == "MultiStepSequencer")
    {
        Module.reset(new CMultiStepSequencerModule(Name, *m_CommandStackController));
    }
    else if(Type == "Clock")
    {
        Module.reset(new CClockModule(Name, *m_CommandStackController));
    }
    else if(Type == "FM")
    {
        Module.reset(new CFMModule(Name, *m_CommandStackController));
    }
    else if(Type == "RandomGate")
    {
        Module.reset(new CRandomGateModule(Name, *m_CommandStackController));
    }
    else if(Type == "ModulatorExt")
    {
        Module.reset(new CExtendedModulatorModule(Name, 3));
    }
    else if(Type == "Limiter")
    {
        Module.reset(new CLimiterModule(Name));
    }
    else if(Type == "UnipolarLimiter")
    {
        Module.reset(new CUnipolarLimiterModule(Name));
    }
    else if(Type == "BipolarLimiter")
    {
        Module.reset(new CBipolarLimiterModule(Name));
    }
    else if(Type == "SlewLimiter")
    {
        Module.reset(new CSlewLimiterModule(Name));
    }
    else if(Type == "1V/Oct")
    {
        Module.reset(new COneVoltPerOctaveModule(Name));
    }
    else if(Type == "Granular")
    {
        Module.reset(new CGranularModule(Name, *m_CommandStackController));
    }
    else if(Type == "PhaseShifter")
    {
        Module.reset(new CPhaseShifterModule(Name));
    }
    else if(Type == "WaveTable")
    {
        Module.reset(new CWaveTableModule(Name, *m_CommandStackController));
    }
    else if(Type == "KarplusStrong")
    {
        Module.reset(new CKarplusStrongModule(Name, *m_CommandStackController));
    }
    else if(Type == "DecayEnvelope")
    {
        Module.reset(new CDecayEnvelopeModule(Name));
    }
    else if(Type == "ToggleGate")
    {
        Module.reset(new CToggleGateModule(Name));
    }
    else if(Type == "Scaler")
    {
        Module.reset(new CScalerModule(Name));
    }
    else if(Type == "ControllerChange")
    {
        Module.reset(new CControllerChangeModule(Name));
    }
    else if(Type == "RingSequencer")
    {
        Module.reset(new CRingSequencerModule(Name));
    }
    else if(Type == "MidiOctaveGate")
    {
        Module.reset(new CMidiOctaveGateModule(Name, *m_CommandStackController));
    }
    else if(Type == "BasicSampler")
    {
        Module.reset(new CBasicSamplerModule(Name, *m_CommandStackController));
    }
    else if(Type == "BinaryOscillator")
    {
        Module.reset(new CBinaryOscillatorModule(Name));
    }
    else if(Type == "WaveShaperA116")
    {
        Module.reset(new CWaveShaperA116Module(Name));
    }
    else if(Type == "CombinedOperator")
    {
        Module.reset(new CCombinedOperatorModule(Name, *m_CommandStackController));
    }
    else if(Type == "IntSimpleOscillator")
    {
        Module.reset(new CIntSimpleOscillatorModule(Name, *m_CommandStackController));
    }
    else if(Type == "IntCombinedOperator")
    {
        Module.reset(new CIntCombinedOperatorModule(Name, *m_CommandStackController));
    }
    else if(Type == "IntKarplusStrong")
    {
        Module.reset(new CIntKarplusStrongModule(Name, *m_CommandStackController));
    }
    else if(Type == "IntFeedbackDelay")
    {
        Module.reset(new CIntFeedbackDelayModule(Name, *m_CommandStackController));
    }

    return Module;
}

std::vector<string> CModuleFactory::GetSupportedTypes(const std::string &Category) const
{
    if(Category=="Envelope")
    {
        return {
            "ADSREnvelopeBank(4)",
            "ADSREnvelopeBank(8)",
            "EnvelopeFollower",
            "DecayEnvelope"
        };
    }

    if(Category=="CV")
    {
        return {
            "ControllerBank(4)",
            "ControllerBank(8)",
            "LFOBank(4)",
            "LFOBank(8)",
            "1V/Oct",
            "Scaler",
            "ControllerChange",
            "RingSequencer"
        };
    }

    if(Category=="Modulate")
    {
        return {
            "Amp",
            "LFOBank(4)",
            "LFOBank(8)",
            "Combinor",
            "CrossMixer",
            "Modulator",
            "ModulatorExt",
            "Detuner(3)",
            "FM",
            "SlewLimiter",
            "RingSequencer"
        };
    }

    if(Category=="Oscillate")
    {
        return {
            "Operator",
            "Phasor",
            "SimpleOscillator",
            "LinSegOperator",
            "Noise",
            "WaveTable",
            "KarplusStrong",
            "BasicSampler",
            "BinaryOscillator",
            "CombinedOperator",
            "IntSimpleOscillator",
            "IntCombinedOperator",
            "IntKarplusStrong"
        };
    }

    if(Category=="Modify")
    {
        return {
            "Amp",
            "LPF",
            "HPF",
            "PhaseSkewer",
            "PhaseShifter",
            "Combinor",
            "WaveFolder",
            "PosNegShaper",
            "MultiStageWaveFolder",
            "SampleAndHold",
            "AsymmetricAmp",
            "FM",
            "Limiter",
            "UnipolarLimiter",
            "BipolarLimiter",
            "SlewLimiter",
            "WaveShaperA116"
        };
    }

    if(Category=="Control")
    {
        return {
            "Amp",
            "Mixer(4)",
            "Mixer(8)",
            "PeriodicSync",
            "StepSequencer",
            "PeriodicTrigger",
            "MultiStepSequencer",
            "Clock",
            "RandomGate",
            "StereoMixer(4)",
            "ToggleGate",
            "RingSequencer"
        };
    }

    if(Category=="Effects")
    {
        return {
            "StereoDelay",
            "Distortion1",
            "Glitch",
            "EnvelopeFollower",
            "DelayLine",
            "Granular",
            "IntFeedbackDelay"
        };
    }

    if(Category=="Midi")
    {
        return {
            "MidiNote",
            "MidiStepSequencer",
            "MidiControllerBank(4)",
            "MidiOctaveGate"
        };
    }

    if(Category=="Other")
    {
        return {

        };
    }

    return {};
}

std::vector<string> CModuleFactory::GetSupportedCategories() const
{
    return {
        "Envelope",
        "CV",
        "Modulate",
        "Oscillate",
        "Modify",
        "Control",
        "Effects",
        "Midi",
        "Other"
    };
}
