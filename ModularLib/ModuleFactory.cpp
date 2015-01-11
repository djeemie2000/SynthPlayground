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

    return Module;
}

std::vector<string> CModuleFactory::GetSupportedTypes(const std::string &Category) const
{
    if(Category=="Envelope")
    {
        return {
            "ADSREnvelopeBank(4)",
            "ADSREnvelopeBank(8)",
            "EnvelopeFollower"
        };
    }

    if(Category=="CV")
    {
        return {
            "ControllerBank(4)",
            "ControllerBank(8)",
            "LFOBank(4)",
            "LFOBank(8)",
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
            "FM"
        };
    }

    if(Category=="Oscillate")
    {
        return {
            "Operator",
            "Phasor",
            "SimpleOscillator",
            "LinSegOperator",
            "Noise"
        };
    }

    if(Category=="Modify")
    {
        return {
            "Amp",
            "LPF",
            "PhaseSkewer",
            "Combinor",
            "WaveFolder",
            "PosNegShaper",
            "MultiStageWaveFolder",
            "SampleAndHold",
            "AsymmetricAmp",
            "FM",
            "Limiter",
            "UnipolarLimiter",
            "BipolarLimiter"
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
            "StereoMixer(4)"
        };
    }

    if(Category=="Effects")
    {
        return {
            "StereoDelay",
            "Distortion1",
            "Glitch",
            "EnvelopeFollower",
            "DelayLine"
        };
    }

    if(Category=="Midi")
    {
        return {
            "MidiNote",
            "MidiStepSequencer",
            "MidiControllerBank(4)",
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
