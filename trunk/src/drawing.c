#include "master.h"

/*****************************************************************************

    Function: blitScreen

    Description: Puts everything from the buffer to the screen, then 
                 clears it.
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void blitScreen()
{
    glFlush(); /* Make sure everything is through the pipes */
    SDL_GL_SwapBuffers(); /* Put it on the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* Clear buffer for new data */
}
/*****************************************************************************

    Function: enableOrtho2D

    Description: Pushes older projection and modelview matrixes onto the stack
                 creates new projection matrix as ortho mode. (for 2d stuff)
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void enableOrtho2D() 
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
    
	glOrtho(0, width, height, 0, -10, 10);

    glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 2, 0, 2, 0, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	/* .. you want to resume in modelview mode, so do it last */

	/* make sure the rest of the program knows by setting the state */
    rendering_ortho = true;
}
/*****************************************************************************

    Function: disableOrtho2D

    Description: Pops ortho mode from the matrix stack, returning
            the projection and modelview matrixes to their former selves.
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void disableOrtho2D() 
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	/* .. you want to resume in modelview mode, so do it last */
	
	
	/* make sure the rest of the program knows by setting the state */
    rendering_ortho = false;
}
/*****************************************************************************

    Function: cleanObject

    Description: Cleans the opengl settings for next object
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void cleanObject() 
{
    glLoadIdentity();
    glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f );	/* reverts back to white color so you get no screw-ups */	
    glBindTexture ( GL_TEXTURE_2D, NULL ); /* untexture to NULL so u can set color with no crap */
    glTranslatef( 0.0f, 0.0f, 0.0f);
    
    /* apply camera rotations if ortho mode is off */
    if(!rendering_ortho)
    {
        gluLookAt(
    		0.0f, -14.5f, -14.0f,
    		0.0f, -10.4f, 3.0f,
    		0.0f, 1.0f, 0.0f);
    }
}
/*****************************************************************************

    Function: draw2DTextureEx
        
    Description: 
    Parameters: x coordinate, y coordinate, z coordinate, alpha, 
                pointer to TEXTURE structure to draw
    Return: n/a

*****************************************************************************/
void draw2DTextureEx(float _x, float _y, float _z, float _alpha,  TEXTURE* _tex) 
{
    /* only use when currently rendering in ortho projection matrix */
    if(rendering_ortho)
    {
        /* Temporarily disable lighting */
        glDisable(GL_LIGHTING);
        
        cleanObject();
        glTranslatef(_x, _y, _z);
        glScalef(_tex->width, _tex->height, 1.0f); /* Blow up quad to texture size */
        glBindTexture(GL_TEXTURE_2D, _tex->id);
        /* Do proper blending with alpha channel */
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        
        glColor4f ( 1.0f, 1.0f, 1.0f, _alpha );
        
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
            /* top left */
            glTexCoord2f(0, 0);
            glVertex2f(0, 0);
            
            /* bottom left */
            glTexCoord2f(0, 1);
            glVertex2f(0, 1);
    
            /* bottom right */
            glTexCoord2f(1, 1);
            glVertex2f(1, 1);
            
            /* top right */
            glTexCoord2f(1, 0);
            glVertex2f(1, 0);
        glEnd();  
        glDisable(GL_TEXTURE_2D);
        
        glEnable(GL_LIGHTING);
    }
}
/*****************************************************************************

    Function: draw2DTexture
        
    Description: 
    Parameters: x coordinate, y coordinate, pointer to TEXTURE
                structure to draw
    Return: n/a

*****************************************************************************/
void draw2DTexture(float _x, float _y, TEXTURE* _tex) 
{
    draw2DTextureEx(_x, _y, -10.0f, 1.0f, _tex);
}
/*****************************************************************************

    Function: draw2DNumberFromRightEx
        
    Description: Draws a bitmap number with our specific number texture
                 from right to left
    Parameters: x coordinate, y coordinate, z coordinate, alpha, 
                pointer to TEXTURE structure to draw, size of 
                char x wise, size of, char y wise, number to draw
    Return: n/a

*****************************************************************************/
void draw2DNumberFromRightEx(float _x, float _y, float _z, float _alpha, TEXTURE* _tex, int _char_width, int _char_height, int _number) 
{

    char buffer[BUFFER_MAX];
    sprintf(buffer, "%d", _number);
    
    /* only use when currently rendering in ortho projection matrix */
    if(rendering_ortho)
    {
        /* Temporarily disable lighting */
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);

        int current_char_x;
        /* Find the right offset for drawing from the right */
        int right_offset = _char_width * strlen(buffer);
        
        /* Find out which number to print, then 
           send the coords to the drawing code */
        int i;
        for(i = 0; i < strlen(buffer); i+=1)
        {  
            switch(buffer[i])
            {
                case '0':
                    current_char_x = 9 * _char_width;
                break;
                case '1':
                    current_char_x = 0 * _char_width;
                break;
                case '2':
                    current_char_x = 1 * _char_width;
                break;
                case '3':
                    current_char_x = 2 * _char_width;
                break;
                case '4':
                    current_char_x = 3 * _char_width;
                break;
                case '5':
                    current_char_x = 4 * _char_width;
                break;
                case '6':
                    current_char_x = 5 * _char_width;
                break;
                case '7':
                    current_char_x = 6 * _char_width;
                break;
                case '8':
                    current_char_x = 7 * _char_width;
                break;
                case '9':
                    current_char_x = 8 * _char_width;
                break;
            }

            cleanObject();
            glTranslatef(_x+(i*_char_width)-right_offset, _y, _z);
            glScalef(_char_width, _char_height, 1.0f); /* Blow up quad to texture size */
            glBindTexture(GL_TEXTURE_2D, _tex->id);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
            
            glColor4f ( 1.0f, 1.0f, 1.0f, _alpha );
            
            glBegin(GL_QUADS);
                /* top left */
                glTexCoord2f((float)current_char_x/_tex->width, 0);
                glVertex2f(0, 0);
                
                /* bottom left */
                glTexCoord2f((float)current_char_x/_tex->width, 1);
                glVertex2f(0, 1);
                
                /* bottom right */
                glTexCoord2f((float)(current_char_x+_char_width)/_tex->width, 1);
                glVertex2f(1, 1);
                
                /* top right */
                glTexCoord2f((float)(current_char_x+_char_width)/_tex->width, 0);
                glVertex2f(1, 0);
            glEnd();  
        }
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
    }
}
/*****************************************************************************

    Function: draw2DNumberFromRight
        
    Description: Draws a bitmap number with our specific number texture
                 from right to left
    Parameters: x coordinate, y coordinate, pointer to TEXTURE
                structure to draw, size of char x wise, size of
                char y wise, number to draw
    Return: n/a

*****************************************************************************/
void draw2DNumberFromRight(float _x, float _y, TEXTURE* _tex, int _char_width, int _char_height, int _number) 
{
    draw2DNumberFromRightEx(_x, _y, -10.0f, 1.0f, _tex, _char_width, _char_height, _number);
}
/*****************************************************************************

    Function: drawBlockStationary
        
    Description: Draws the stationary tetris block geometry
    Parameters: x coordinate, y coordinate, red, green, blue
    Return: n/a

*****************************************************************************/
void drawBlockStationary(float _x, float _y, float _r, float _g, float _b)
{
    /* draw outside */
    cleanObject();
    glTranslatef(_x,_y,10);
    glScalef(1, 1, 0.8);
    glColor4f ( 0.0f, 0.0f, 0.0f, 1.0f );
    glutSolidCube(1.0);
    /* fill in the creamy centre */
    cleanObject();
    glTranslatef(_x,_y,10);
    glScalef(1, 1, 1.4);
    glColor4f( _r, _g, _b, 1.0f );
    glutSolidCube(.90);                                         
}
/*****************************************************************************

    Function: drawBlockMoving
        
    Description: Draws the moving tetris block geometry
    Parameters: x coordinate, y coordinate, red, green, blue
    Return: n/a

*****************************************************************************/
void drawBlockMoving(float _x, float _y, float _r, float _g, float _b)
{ 
    /* draw outside */
    cleanObject();
    glTranslatef(_x,_y,10);
    glScalef(1, 1, 0.8);
    glColor4f ( 0.15f, 0.15f, 0.15f, 1.0f );
    glutSolidCube(1.0);
    /* fill in the creamy centre */
    cleanObject();
    glTranslatef(_x,_y,10);
    glScalef(1, 1, 1.0);
    glColor4f( _r, _g, _b, 1.0f );
    glutSolidCube(.90);                                
}
/*****************************************************************************

    Function: drawBlockBackground
        
    Description: Draws the background tetris block geometry
    Parameters: x coordinate, y coordinate, red, green, blue
    Return: n/a

*****************************************************************************/
void drawBlockBackground(float _x, float _y, float _r, float _g, float _b)
{ 
    cleanObject();
    glTranslatef(_x,_y,10);
    glScalef(1, 1, 1);
    glColor4f ( _r, _g, _b, 1.0f );
    glutSolidCube(0.95);                               
}               
/*****************************************************************************

    Function: doDrawing

    Description: calls the current screens drawing function
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void doDrawing()
{
    switch(screen_current)
    {
        case SCREEN_GAMEPLAY:
            screenGameplayDrawing();
        break;
    }
}
