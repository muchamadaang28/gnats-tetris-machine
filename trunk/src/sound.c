#include "master.h"
/*****************************************************************************

    Function: setupSound

    Description: Sets up the various FMOD settings
    Parameters: n/a
    Return: n/a
    
*****************************************************************************/
void setupSound()
{
    if (FSOUND_GetVersion() < FMOD_VERSION)
    {
        printf("Error : You are using the wrong DLL version!  You should be using FMOD %.02f\n", FMOD_VERSION);
        return 0;
    }
    
    if (!FSOUND_Init(44100, 64, 0))
    {
        printf("%s\n", FMOD_ErrorString(FSOUND_GetError()));
        return 0;
    }
}
/*****************************************************************************

    Function: playSound

    Description: Calls the sound api to play the selected sound data
    Parameters: pointer to fmod api sample
    Return: n/a

*****************************************************************************/
void playSound(FSOUND_SAMPLE* sound)
{
    FSOUND_PlaySound(FSOUND_FREE, sound); 
} 
/*****************************************************************************

    Function: muteSounds

    Description: Mutes all playing audio files
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void muteAllSound()
{
    FSOUND_StopSound(FSOUND_ALL);
} 
