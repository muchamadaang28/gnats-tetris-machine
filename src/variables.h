#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#define APP_NAME "Gnat's Tetris Machine"

#define BUFFER_MAX 512

/* Custom C Types */
typedef enum {false=0, true} bool; /* Boolean. Mmmm. */



/* Video Variables */
extern int width, height, bpp, vid_flags;

/* Base Program Variables */
extern bool rendering_ortho;  
extern bool running; 
extern SDL_Event event;
extern int screen_current;
enum {SCREEN_GAMEPLAY}; /* add more screens here */

/* Input variables */
extern bool move_left;
extern bool move_right;
extern bool flip_brick;
extern bool move_down;

/* game variables */
extern int score;
extern int level;
extern bool game_over;
extern GLfloat theta;

/* visual effects */
#define GLOW_MIN 0.16
extern float score_glow;

/* some colors for later on.. */
#define GREY_1 0.16
#define GREY_2 0.13
#define GREY_3 0.1

/************************************************************
/* Gameboard and brick stuff
/************************************************************/

extern bool new_brick;
extern int brick_x;
extern int brick_y;
extern float brick_move_timer;
extern int brick_move_difficulty;

extern int brick_type_current;
extern int brick_type_next;
extern int brick_type_rotation;
extern int brick_color_current;
extern int brick_color_next;

    
#define GAMEBOARD_W 10
#define GAMEBOARD_H 20

#define BACKGROUND_W 34
#define BACKGROUND_H 23

#define GAMEPIECE_W 4
#define GAMEPIECE_H 4
#define GAMEPIECE_ROTATIONS 4

#define MAX_BRICK_TYPES 7
#define MAX_BRICK_COLORS 3

extern int gameboard[GAMEBOARD_H][GAMEBOARD_W]; /* 10 across, 20 down */
extern int background[BACKGROUND_H][BACKGROUND_W];
extern int brick_T[GAMEPIECE_ROTATIONS][GAMEPIECE_H][GAMEPIECE_W];
extern int brick_I[GAMEPIECE_ROTATIONS][GAMEPIECE_H][GAMEPIECE_W];
extern int brick_J[GAMEPIECE_ROTATIONS][GAMEPIECE_H][GAMEPIECE_W];
extern int brick_L[GAMEPIECE_ROTATIONS][GAMEPIECE_H][GAMEPIECE_W];
extern int brick_O[GAMEPIECE_ROTATIONS][GAMEPIECE_H][GAMEPIECE_W];
extern int brick_Z[GAMEPIECE_ROTATIONS][GAMEPIECE_H][GAMEPIECE_W];
extern int brick_S[GAMEPIECE_ROTATIONS][GAMEPIECE_H][GAMEPIECE_W];



#ifndef PI
#define PI 3.14159265
#endif
#ifndef abs
#define abs(a)   ((a) < 0 ? -(a) : (a))
#endif

#endif
