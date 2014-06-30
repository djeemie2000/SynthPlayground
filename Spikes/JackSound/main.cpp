
/** @file simple_client.c
   *
   * @brief This is very simple client that demonstrates the basic
   * features of JACK as they would be used by many applications.
   */

#include <unistd.h>//std::sleep
#include <iostream>
#include <string>
#include <jack/jack.h>
#include "AudioSource2I.h"
#include "JackAudioOutput.h"

class CTestAudioSource : public IAudioSource2
{
public:
    CTestAudioSource()
    {}

    int OnRead(void *Dst, int NumFrames)
    {
        jack_default_audio_sample_t *Out = (jack_default_audio_sample_t *)Dst;

        // generate saw wave output
        jack_default_audio_sample_t PhaseIncrease = 10.0f/NumFrames;
        jack_default_audio_sample_t Phase = -1.0f;
        jack_default_audio_sample_t* OutEnd = Out + NumFrames;
        while(Out<OutEnd)
        {
            *Out = Phase;
            Phase += PhaseIncrease;
            if(1.0f<Phase)
            {
                Phase -= 2.0f;
            }
            ++Out;
        }

        return 0; // return zero upon success
    }
};

int main (int /*argc*/, const char **/*argv[]*/)
{
    CTestAudioSource AudioSource;
    CJackAudioOutput AudioOutput(AudioSource);

    if(AudioOutput.Open("TestJackSound", "Out1"))
    {
        std::cout << "Sampling frequency is " << AudioOutput.SamplingFrequency() << std::endl;

        // Since this is just a toy, run for a few seconds, then finish
        sleep (35);

        AudioOutput.Close();
    }

    return 0;
}

