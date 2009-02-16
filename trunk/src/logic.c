#include "master.h"

/*****************************************************************************

    Function: doLogic

    Description: calls the current screens logic function
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void doLogic()
{
    switch(screen_current)
    {
        case SCREEN_GAMEPLAY:
            screenGameplayLogic();
        break;
    }
} 
