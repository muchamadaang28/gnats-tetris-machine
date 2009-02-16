#include "master.h"

float time_delta;
long long last_ms;

/*****************************************************************************

    Function: setupTimers

    Description: Sets up sdl timer
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void setupTimers()
{    
    /* Set Up Timers For Game Use */
    time_delta = 0.0f;
    last_ms = SDL_GetTicks();
}
/*****************************************************************************

    Function: updateTimers

    Description: Updates the timer
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void updateTimers()
{
    sleep(0); /* Give back spare cpu cycles */
    
    /* Find this frames time delta */
    time_delta = 0;
    if(SDL_GetTicks() > last_ms)
    {
        time_delta = SDL_GetTicks() - last_ms;
        last_ms = SDL_GetTicks();
    }
}

