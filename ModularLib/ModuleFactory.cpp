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
    else if(Type == "PeriodicTrigger")
    {
        Module.reset(new CPeriodicTriggerModule(Name, *m_CommandStackController));
    }

    return Module;
}

std::vector<string> CModuleFactory::GetSupportedTypes() const
{
    return {
        "Amp",
        "ControllerBank(4)",
        "ControllerBank(8)",
        "Operator",
        "Phasor",
        "MidiNote",
        "LPF",
        "LFOBank(4)",
        "LFOBank(8)",
        "SimpleOscillator",
        "StereoDelay",
        "ADSREnvelopeBank(4)",
        "ADSREnvelopeBank(8)",
        "Mixer(4)",
        "Mixer(8)",
        "PhaseSkewer",
        "Combinor",
        "CrossMixer",
        "Modulator",
        "WaveFolder",
        "PosNegShaper",
        "LinSegOperator",
        "Detuner(3)",
        "MultiStageWaveFolder",
        "PeriodicSync",
        "Distortion1",
        "Noise",
        "SampleAndHold",
        "Glitch",
        "MidiStepSequencer",
        "PeriodicTrigger"
    };
}
