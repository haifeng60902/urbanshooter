#include <sound/SoundEngine.h>


#include <fmod_errors.h>
#include <stdio.h>

#include <iostream>
#include <conio.h>

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
       return;
    }
}



SoundEngine::SoundEngine()
{
	system = NULL;

}

SoundEngine::~SoundEngine()
{
	system->release();
	system->close();
//	delete system; //crash the application...
}


void SoundEngine::frame()
{
	//only thing that is ensured to stay  here!
	system->update();

}

bool SoundEngine::isValid()
{
	return true;
}

void SoundEngine::initialize()
{
	
	FMOD_RESULT      result;
    unsigned int     version;
    int              numdrivers;
    FMOD_SPEAKERMODE speakermode;
    FMOD_CAPS        caps;
    char             name[256];

    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);
#if 1     
    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return;
    }
    
    result = system->getNumDrivers(&numdrivers);
    ERRCHECK(result);

    if (numdrivers == 0)
    {
        result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
        ERRCHECK(result);
    }
    else
    {
        result = system->getDriverCaps(0, &caps, 0, 0, &speakermode);
        ERRCHECK(result);

        result = system->setSpeakerMode(speakermode);       /* Set the user selected speaker mode. */
        ERRCHECK(result);

        if (caps & FMOD_CAPS_HARDWARE_EMULATED)             /* The user has the 'Acceleration' slider set to off!  This is really bad for latency!. */
        {                                                   /* You might want to warn the user about this. */
            result = system->setDSPBufferSize(1024, 10);
            ERRCHECK(result);
        }

        result = system->getDriverInfo(0, name, 256, 0);
        ERRCHECK(result);

        if (strstr(name, "SigmaTel"))   /* Sigmatel sound devices crackle for some reason if the format is PCM 16bit.  PCM floating point output seems to solve it. */
        {
            result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR);
            ERRCHECK(result);
        }
    }
#endif
    result = system->init(100, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);

#if 1 
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)         /* Ok, the speaker mode selected isn't supported by this soundcard.  Switch it back to stereo... */
    {
        result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
        ERRCHECK(result);
            
        result = system->init(100, FMOD_INIT_NORMAL, 0);/* ... and re-init. */
        ERRCHECK(result);
    }



	result = system->setStreamBufferSize(64*1024, FMOD_TIMEUNIT_RAWBYTES);
    ERRCHECK(result);
#endif

}

void SoundEngine::playFire()
{

	FMOD::Sound* sound = NULL;
    FMOD_RESULT result = system->createSound("./datas/sounds/Shot.mp3",FMOD_SOFTWARE, NULL, &sound);
    ERRCHECK(result);

	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, NULL);

}
