#include "master.h"

/*****************************************************************************

    Function: setupMatrixes

    Description: Sets the projection and modelview matrix to the program
                 default.
    Parameters: width and height of viewport
    Return: n/a

*****************************************************************************/
void setupMatrixes(GLsizei _w, GLsizei _h)
{
    /* Prevent divide by zero */
    if(_h <= 0) _h = 1;
    if(_w <= 0) _w = 1;
    
    glViewport(0, 0, _w, _h); /* Set viewport to window dimensions */
    
    /* Reset projection matrix stack */
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(60.0f, 1.0f, 1.0f, 100.0f);

    /* Reset texture view matrix stack */
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    
    /* Reset model view matrix stack */
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    /* ... and keep it on for rendering */  
}
/*****************************************************************************

    Function: setupRenderingContext

    Description: Sets up the various opengl settings
    Parameters: n/a
    Return: n/a
    
*****************************************************************************/
void setupRenderingContext()
{
    glClearColor(0.4f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW); /* counter clockwise polys face out */
 
	glAlphaFunc(GL_GREATER, 0.01); /* Skip pixels which alpha channel is lower than 0.01 */
    glEnable(GL_TEXTURE_2D);  /* Enable 2D texturing */
    glEnable(GL_BLEND);  /* Enable Blending */
    glEnable(GL_ALPHA_TEST);  /* Enable Alpha */
    glEnable(GL_CULL_FACE);  /* Make sure face culling is enabled (speed demon ;) */
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);  /* Turn On The Blender */
	
	glPointSize(2); /* size of points */
    
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_NONE);
    
    glShadeModel(GL_SMOOTH); /* Smooth shading */

    /* Enable Lighting */
    glEnable(GL_LIGHTING);

    /* Set up light0 */
    GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specularLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat position[] = {  0.0, 40.0, -20.0, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    /* Create the newly set up lightsource */
    glEnable(GL_LIGHT0);


    /* GLOBAL light settings */
    GLfloat global_ambient[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    
    /* Material color tracking */
    glEnable(GL_COLOR_MATERIAL);
    /* Make it so ambient and diffuse material properties will use glcolor
       Soo...  glColor3f(0.0f, 0.0f, 1.0f); would make blue reflective properties
       Exactly like calling:
       float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
       glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
       before the geometry */
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
 
}
/*****************************************************************************

    Function: newGame

    Description: Sets up the board for a new game
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void newGame()
{
    /* Clear board */
    int i, j;
    for(i = GAMEBOARD_H-1; i >= 0; i--) 
        for(j = GAMEBOARD_W-1; j >= 0; j--)
            gameboard[i][j] = 0;
    
    /* Randomize next brick */
    brick_type_next = (rand() % MAX_BRICK_TYPES);
    brick_type_current = 0;         
    new_brick = true;  
    
    score = 0;
    level = 1;
    game_over = false;
}
/*****************************************************************************

    Function: initialize

    Description: Setup SDL and other api's
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void initialize()
{
    /* initialize SDL */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(width, height, 0, vid_flags);
    SDL_WM_SetCaption(APP_NAME, APP_NAME);

    /* setup opengl */
    setupRenderingContext();
    setupMatrixes(width, height);
    
    /* setup fmod */
    setupSound();
    
    /* set the game timer up */
    setupTimers();
    /* seed random numbers */
    srand (time(NULL));
    
    /* start new game */
    newGame();
}
