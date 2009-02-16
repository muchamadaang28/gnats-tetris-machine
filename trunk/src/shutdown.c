#include "master.h"

/*****************************************************************************

    Function: shutdown

    Description: Shutdown SDL and other api's. Free any allocated heap
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void shutdown()
{
    /* free texture structs */
    int i;
    for(i = 0; i < TEXTURE_COUNT; i++)
        free(textures[i]);
        
    /* glDeleteTextures( 1, &texture ); */ /* Not really needed in this case. OGL deletes its own stuff */  

    /* free sample data */
    for(i = 0; i < SAMPLE_COUNT; i++)
        FSOUND_Sample_Free(samples[i]);

    /* shutdown apis */
    FSOUND_Close();
    SDL_Quit();
}
