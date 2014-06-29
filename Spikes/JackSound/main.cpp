
/** @file simple_client.c
   *
   * @brief This is very simple client that demonstrates the basic
   * features of JACK as they would be used by many applications.
   */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string>

#include<jack/jack.h>

jack_client_t *client;
jack_port_t *output_port;
jack_nframes_t sample_rate;

/*
 * The process callback for this JACK application.
  * It is called by JACK at the appropriate times.
 */
int process (jack_nframes_t nframes, void */*arg*/)
{
    //printf("processing %d frames into output \r\n", nframes);

    jack_default_audio_sample_t *out = (jack_default_audio_sample_t *) jack_port_get_buffer (output_port, nframes);
    //    jack_default_audio_sample_t *in = (jack_default_audio_sample_t *) jack_port_get_buffer (input_port, nframes);

    // generate saw wave output
    jack_default_audio_sample_t PhaseIncrease = 10.0f/nframes;//440.0f/44100;
    jack_default_audio_sample_t Phase = -1.0f;
    jack_default_audio_sample_t* outEnd = out + nframes;
    while(out<outEnd)
    {
        *out = Phase;
        Phase += PhaseIncrease;
        if(1.0f<Phase)
        {
            Phase -= 2.0f;
        }
        ++out;
    }

    return 0; // return non zero upon error
}

/*
  * This is the shutdown callback for this JACK application.
  * It is called by JACK if the server ever shuts down or
  * decides to disconnect the client.
  */
void jack_shutdown (void *)
{
    printf("Jack shutdown\r\n");
//    jack_client_close (client); cannot be done safey inside this function call!
    exit (1);
}

int main (int argc, const char *argv[])
{
    if (argc< 1)
    {
        fprintf (stderr, "usage: jack_simple_client<name>\n");
        return 1;
    }

    /* try to become a client of the JACK server */
    std::string Name("MyClient");
    if ((client = jack_client_open(Name.c_str(), JackNullOption, 0)) == 0)
    {
        fprintf (stderr, "jack server not running?\n");
        return 1;
    }

    /* tell the JACK server to call `process()' whenever there is work to be done. */
    jack_set_process_callback(client, process, 0);

    /* tell the JACK server to call `jack_shutdown()' if it ever shuts down, either entirely, or if it just decides to stop calling us.*/
    jack_on_shutdown(client, jack_shutdown, 0);

    /* retrieve and display the current sample rate. */
    sample_rate = jack_get_sample_rate(client);
    printf("engine sample rate: %d \n", sample_rate);

    /* create one output port. Use default audio type, which is mono float 32 bits */
    output_port = jack_port_register(client, "output", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput|JackPortIsTerminal, 0);

    /* tell the JACK server that we are ready to roll */
    if (jack_activate(client))
    {
        fprintf (stderr, "cannot activate client");
        return 1;
    }

    /* Since this is just a toy, run for a few seconds, then finish */
    sleep (35);

    jack_deactivate(client);
    jack_client_close (client);
    exit (0);
}

