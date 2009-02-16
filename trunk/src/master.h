#ifndef _MASTER_H_
#define _MASTER_H_

#include <SDL/SDL.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/freeglut.h>
#include <SDL/SDL_image.h>
#include <fmod.h>
#include <fmod_errors.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>

#define DEBUG

/* undefine sdl main so console output works */
#ifdef DEBUG
    #ifdef main
    #undef main
    #endif
#endif

#include "variables.h"
#include "init.h"
#include "dataload.h"
#include "shutdown.h"
#include "input.h"
#include "sound.h"
#include "logic.h"
#include "drawing.h"
#include "timer.h"
/* Screens */
#include "screen_gameplay.h"

#endif

