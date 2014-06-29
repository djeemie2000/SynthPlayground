#include <iostream>
#include <string>
#include <alsa/asoundlib.h>

using namespace std;

void EnumerateDevices()
{

    register int  err;
    int           cardNum;

    // Start with first card
    cardNum = -1;

    for (;;)
    {
        snd_ctl_t *cardHandle;

        // Get next sound card's card number. When "cardNum" == -1, then ALSA
        // fetches the first card
        if ((err = snd_card_next(&cardNum)) < 0)
        {
            printf("Can't get the next card number: %s\n", snd_strerror(err));
            break;
        }

        // No more cards? ALSA sets "cardNum" to -1 if so
        if (cardNum < 0) break;

        // Open this card's control interface. We specify only the card number -- not
        // any device nor sub-device too
        {
            char   str[64];

            sprintf(str, "hw:%i", cardNum);
            if ((err = snd_ctl_open(&cardHandle, str, 0)) < 0)
            {
                printf("Can't open card %i: %s\n", cardNum, snd_strerror(err));
                continue;
            }
        }

        {
            int      devNum;

            // Start with the first wave device on this card
            devNum = -1;

            for (;;)
            {
                snd_pcm_info_t  *pcmInfo;
                register int        subDevCount, i;

                // Get the number of the next wave device on this card
                if ((err = snd_ctl_pcm_next_device(cardHandle, &devNum)) < 0)
                {
                    printf("Can't get next wave device number: %s\n", snd_strerror(err));
                    break;
                }

                // No more wave devices on this card? ALSA sets "devNum" to -1 if so.
                // NOTE: It's possible that this sound card may have no wave devices on it
                // at all, for example if it's only a MIDI card
                if (devNum < 0) break;

                // To get some info about the subdevices of this wave device (on the card), we need a
                // snd_pcm_info_t, so let's allocate one on the stack
                snd_pcm_info_alloca(&pcmInfo);
                memset(pcmInfo, 0, snd_pcm_info_sizeof());

                // Tell ALSA which device (number) we want info about
                snd_pcm_info_set_device(pcmInfo, devNum);

                // Get info on the wave outs of this device
                snd_pcm_info_set_stream(pcmInfo, SND_PCM_STREAM_PLAYBACK);

                i = -1;
                subDevCount = 1;

                // More subdevices?
                while (++i < subDevCount)
                {
                    // Tell ALSA to fill in our snd_pcm_info_t with info on this subdevice
                    snd_pcm_info_set_subdevice(pcmInfo, i);
                    if ((err = snd_ctl_pcm_info(cardHandle, pcmInfo)) < 0)
                    {
                        printf("Can't get info for wave output subdevice hw:%i,%i,%i: %s\n", cardNum, devNum, i, snd_strerror(err));
                        continue;
                    }

                    // Print out how many subdevices (once only)
                    if (!i)
                    {
                        subDevCount = snd_pcm_info_get_subdevices_count(pcmInfo);
                        printf("\nFound %i wave output subdevices on card %i\n", subDevCount, cardNum);
                    }

                    // NOTE: If there's only one subdevice, then the subdevice number is immaterial,
                    // and can be omitted when you specify the hardware name
                    printf((subDevCount > 1 ? "    hw:%i,%i,%i\n" : "    hw:%i,%i\n"), cardNum, devNum, i);
                }
            }
        }

        // Close the card's control interface after we're done with it
        snd_ctl_close(cardHandle);
    }

    snd_config_update_free_global();


}

void PlaySomeDataMinimal()
{
    const std::string device = "jack";//"jack"; /* playback device */
    snd_output_t *output = NULL;
    //unsigned char buffer[16*1024]; /* some random data */
    const int BufferSize = 16*1024;
    float buffer[BufferSize];

    // fill buffer 48k/Sec samples => period = 100 is 480Hz
    // U8 data rampup data
    for(int idx = 0; idx<BufferSize; ++idx)
    {
        buffer[idx] = -1.0f+  (idx%512)/256.0f;
        buffer[idx] *= 0.35;
        //buffer[idx] = (3*idx/2)%256;//rampup period 256
    }
//    for (i = 0; i < sizeof(buffer); i++)
//        buffer[i] = random() & 0xff;


    int err;
    unsigned int i;
    snd_pcm_t *handle;
    snd_pcm_sframes_t frames;

    // open playback device -> handle
    int Mode = 0;
    // if non blocking :
    // Mode |= SND_PCM_NONBLOCK;
    // if async mode: similar
    if ((err = snd_pcm_open(&handle, device.c_str(), SND_PCM_STREAM_PLAYBACK, Mode)) < 0)
    {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    // configure output device (using handle)
    // jack needs 2 channels, floating
    int NumChannels = 1;
    if ((err = snd_pcm_set_params(handle,
                                  SND_PCM_FORMAT_FLOAT_LE,//SND_PCM_FORMAT_U8,
                                  SND_PCM_ACCESS_RW_INTERLEAVED,
                                  NumChannels,
                                  44100,
                                  1,
                                  500000)) < 0) // 0.5sec
    {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    // print some device properties
    std::cout << "device name= " << snd_pcm_name(handle) << std::endl;
    snd_pcm_uframes_t buffer_size = 0;
    snd_pcm_uframes_t period_size = 0;
    snd_pcm_get_params(handle, &buffer_size, &period_size);
    std::cout << "device buffer size= " << buffer_size << std::endl;
    std::cout << "device period size= " << period_size << std::endl;


    int bs = 0;


    // write some data to the output device
    const int Repeats = 64;
    for (i = 0; i < Repeats; i++)
    {
        int NumFrames = 8192;//BufferSize/NumChannels;
        frames = snd_pcm_writei(handle, buffer, NumFrames);
        if (frames < 0)
        {
            frames = snd_pcm_recover(handle, frames, 0);
        }
        if (frames < 0)
        {
            printf("snd_pcm_writei failed: %s\n", snd_strerror(err));
            break;
        }
        if (frames > 0 && frames < NumFrames)
        {
            printf("Short write (expected %li, wrote %li)\n", (long)sizeof(buffer), frames);
        }

        printf("written %li frames \n", frames);

    }
    snd_pcm_close(handle);
}


int main()
{
    cout << "Hello World!" << endl;

    //EnumerateDevices();

    PlaySomeDataMinimal();

    return 0;
}

