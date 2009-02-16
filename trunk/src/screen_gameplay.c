#include "master.h"

float secondary_timer = 0;

/*****************************************************************************

    Function: updateStarRank

    Description: updates the players "star ranking"
    Parameters: n/a
    Return: n/a

*****************************************************************************/
#define STAR_RANK_FLASH 110
float star_rank_timer = STAR_RANK_FLASH;
void updateStarRank()
{
    int old_level = level;

    /* if player reaches a certain score, update his star level */
    if(level == 11 && score > level*5000)
        level = 12;
    if(level == 10 && score > level*4500)
        level = 11;
    if(level == 9 && score > level*4000)
        level = 10;
    if(level == 8 && score > level*3500)
        level = 9;
    if(level == 7 && score > level*3000)
        level = 8;
    if(level == 6 && score > level*2500)
        level = 7;
    if(level == 5 && score > level*2000)
        level = 6;
    if(level == 4 && score > level*1500)
        level = 5;
    if(level == 3 && score > level*1000)
        level = 4;
    if(level == 2 && score > level*500)
        level = 3;
    if(level == 1 && score > 300)
        level = 2;

          
    /* level has changed, do animation */
    if(old_level < level)
        star_rank_timer = STAR_RANK_FLASH;
    
    /* decrement for animation */  
    if(star_rank_timer > 0)
        star_rank_timer -= time_delta * 0.05;
}
/*****************************************************************************

    Function: drawStarRank

    Description: draws the players "star ranking"
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void drawStarRank()
{
    int x = 24;
    int y = 52;
    int space = 50; /* space in between stars for drawing */
    
    /* Draw stars */
    int i;
    for(i = 0; i < 12; i++)
    { 
        if(level >= (i+1))
        {
            /* flicker stars when player has levelled up! */
            if(star_rank_timer <= 0 || (star_rank_timer > 20 && star_rank_timer < 40) || (star_rank_timer > 60 && star_rank_timer < 80) || (star_rank_timer > 100 && star_rank_timer < 120))
                draw2DTexture(x+(space*i), y, textures[TEX_STARLIT]);
            else
                draw2DTexture(x+(space*i), y, textures[TEX_STARBLANK]);
        }
        else
            draw2DTexture(x+(space*i), y, textures[TEX_STARBLANK]);
    }
}
/*****************************************************************************

    Function: updateSkillLevel

    Description: Updates difficulty according to current star level
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void updateSkillLevel()
{
    /* if player reaches a certain level, increase the difficulty */
    if(level == 12)
        brick_move_difficulty = 15;
    if(level == 11)
        brick_move_difficulty = 20;
    if(level == 10)
        brick_move_difficulty = 25;
    if(level == 9)
        brick_move_difficulty = 30;
    if(level == 8)
        brick_move_difficulty = 35;
    if(level == 7)
        brick_move_difficulty = 40;
    if(level == 6)
        brick_move_difficulty = 45;
    if(level == 5)
        brick_move_difficulty = 50;
    if(level == 4)
        brick_move_difficulty = 55;
    if(level == 3)
        brick_move_difficulty = 60;
    if(level == 2)
        brick_move_difficulty = 65;

}
/*****************************************************************************

    Function: updateGameOver

    Description: Effects for when player loses
    Parameters: n/a
    Return: n/a

*****************************************************************************/
float game_over_timer = 0; /* For gameover effects */
void updateGameOver()
{
    int _time = (int)game_over_timer;
    int j;
    
    if(_time >= GAMEBOARD_H)
        _time = GAMEBOARD_H - 1;
    
    int i;
    for(i = 0; i <= _time; i++) /* Make board grey colors */
    {
        /* Go through row */
        for(j = 0; j < GAMEBOARD_W; j++)
        {
            /* grey the row */
            if(gameboard[i][j] == 1 || gameboard[i][j] == 4)
                gameboard[i][j] = 7;
            if(gameboard[i][j] == 2 || gameboard[i][j] == 5)
                gameboard[i][j] = 8;
            if(gameboard[i][j] == 3 || gameboard[i][j] == 6)
                gameboard[i][j] = 9;
        }
    }

    game_over_timer += time_delta * 0.05; /* increment effect timer */
}
/*****************************************************************************

    Function: drawGameOver

    Description: Effects for when player loses
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void drawGameOver()
{
    float game_over_alpha = (((float)game_over_timer)/100);
    
    if(game_over_alpha > 1.0f) 
        game_over_alpha = 1.0f;
    
    /* draw the big 'game over' image :) */
    draw2DTextureEx(0, 190, 1, game_over_alpha, textures[TEX_GAMEOVER]);
}
/*****************************************************************************

    Function: scanBrick

    Description: Scans the x/y of the passed bricks array
    Parameters: Brick type, current rotation of brick, 
                y array position to scan, x array position to scan
    Return: The int held in x/y array position (either 1 or 0)

*****************************************************************************/
int scanBrick(int _type, int _rotation, int _y, int _x)
{
    switch(_type)
    {
        /* T brick */
        case 0:
            return brick_T[_rotation][_y][_x];
        break;
        case 1:
            return brick_I[_rotation][_y][_x];
        break;
        case 2:
            return brick_J[_rotation][_y][_x];
        break;
        case 3:
            return brick_L[_rotation][_y][_x];
        break;
        case 4:
            return brick_O[_rotation][_y][_x];
        break;
        case 5:
            return brick_Z[_rotation][_y][_x];
        break;
        case 6:
            return brick_S[_rotation][_y][_x];
        break;
    }
    
    return 0;
}
/*****************************************************************************

    Function: screenGameplayLogic

    Description: gameplay logic here
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void screenGameplayLogic()
{
    /* make sure input isnt affected by the timer */
    doInput();
    
    updateTimers();
    
    /* if the player hasnt lost, do stuff */
    if(!game_over)
    {
        /************************************************************
        /* If left key is tapped, see if moving piece left is ok
        /************************************************************/
        if(move_left && !new_brick)
        {
            bool move_ok = true;
            
            /* iterate through game board */
            int i, j;
            for(i = 0; i < GAMEBOARD_H; i++)
                for(j = 0; j < GAMEBOARD_W; j++)
                    if(gameboard[i][j] == 4 || gameboard[i][j] == 5 || gameboard[i][j] == 6)
                    {
                        /* if out of bounds */
                        if(j-1 < 0)
                            move_ok = false;
                        else 
                        {
                            /* if a brick is there */
                            if(gameboard[i][j-1] == 1 || gameboard[i][j-1] == 2 || gameboard[i][j-1] == 3)
                                move_ok = false;
                        }
                    }
            
            if(move_ok) /* if detection is OK then move the brick */
            {
                playSound(samples[SAM_BRICKMOVE]);
                
                /* iterate through game board */
                int i, j;
                for(i = 0; i < GAMEBOARD_H; i++)
                    for(j = 0; j < GAMEBOARD_W; j++)
                        if(gameboard[i][j] == 4 || gameboard[i][j] == 5 || gameboard[i][j] == 6)
                        {
                            int temp = gameboard[i][j];    
                            gameboard[i][j] = 0;
                            gameboard[i][j-1] = temp;
                        }
                        
                /* decrement the bricks x coordinate */
                brick_x -= 1;
            }
            
        }
        
        /************************************************************
        /* If right key is tapped, see if moving piece right is ok
        /************************************************************/
        if(move_right && !new_brick)
        {
            bool move_ok = true;
            
            /* iterate through game board */
            int i, j;
            for(i = GAMEBOARD_H-1; i >= 0; i--)
                for(j = GAMEBOARD_W-1; j >= 0; j--)
                    if(gameboard[i][j] == 4 || gameboard[i][j] == 5 || gameboard[i][j] == 6)
                    {
                        /* if out of bounds */
                        if(j+1 > GAMEBOARD_W-1)
                            move_ok = false;
                        else 
                        {
                            /* if a brick is there */
                            if(gameboard[i][j+1] == 1 || gameboard[i][j+1] == 2 || gameboard[i][j+1] == 3)
                                move_ok = false;
                        }
                    }
            
            if(move_ok) /* if detection is OK then move the brick */
            {
                playSound(samples[SAM_BRICKMOVE]);
                
                /* iterate through game board */
                int i, j;
                for(i = GAMEBOARD_H-1; i >= 0; i--)
                    for(j = GAMEBOARD_W-1; j >= 0; j--)
                        if(gameboard[i][j] == 4 || gameboard[i][j] == 5 || gameboard[i][j] == 6)
                        {
                            int temp = gameboard[i][j];
                            gameboard[i][j] = 0;
                            gameboard[i][j+1] = temp;
                        }
                        
                /* increment the bricks x coordinate */
                brick_x += 1;
            }
            
        }
     
        
        /*********************************************************************
        /* If up (flip brick) key is tapped, see if moving piece right is ok
        /*********************************************************************/
        if(flip_brick && !new_brick)
        {
            bool move_ok = true;
            /* find wanted brick type rotation to change to */
            int rotation_wanted = brick_type_rotation + 1;
            if(rotation_wanted > 3)
                rotation_wanted = 0;
    
            int i, j;
            /* iterate through wanted brick rotation */ 
            /* see if it fits on the gameboard at the brick_x, brick_y location */
            for(i = 0; i < 4; i++)
                for(j = 0; j < 4; j++)
                    if(scanBrick(brick_type_current, rotation_wanted, i, j) == 1)
                    {
                        int check_brick_y = i + brick_y;
                        int check_brick_x = j + brick_x;
                        
                        /* check if out of bounds */
                        if(check_brick_y > GAMEBOARD_H-1 || check_brick_y < 0 || check_brick_x > GAMEBOARD_W-1 || check_brick_x < 0)
                        {
                            move_ok = false;
                        }
                        else
                        {
                            /* check if it collides with something in the gameboard */
                            if(gameboard[check_brick_y][check_brick_x] == 1 || gameboard[check_brick_y][check_brick_x] == 2 || gameboard[check_brick_y][check_brick_x] == 3)
                            {    
                                move_ok = false;
                            }
                        }
                    }
                    
            if(move_ok)
            {
                playSound(samples[SAM_BRICKMOVE]);
                
                /* If successful, increment shape_type_rotation */
                /* And make sure it loops around to 0 when needed */
                brick_type_rotation += 1;
                if(brick_type_rotation > 3)
                    brick_type_rotation = 0;
                
                /* Remember color when rotating */
                int color;
                
                /* clear the gameboard of movables */
                for(i = GAMEBOARD_H-1; i >= 0; i--)
                    for(j = GAMEBOARD_W-1; j >= 0; j--)
                        if(gameboard[i][j] == 4 || gameboard[i][j] == 5 || gameboard[i][j] == 6)
                        {
                            color = gameboard[i][j];
                            gameboard[i][j] = 0;
                        }
                        
                        
                /* iterate through wanted brick */
                /* place on the gameboard at the brick_x, brick_y location */
                for(i = 0; i < 4; i++)
                    for(j = 0; j < 4; j++)
                        if(scanBrick(brick_type_current, brick_type_rotation, i, j))
                        {
                            int check_brick_y = i + brick_y;
                            int check_brick_x = j + brick_x;
                            
                            gameboard[check_brick_y][check_brick_x] = color;
                        }
            }
        }

        /*********************************************************************
        /* If down key is tapped, see if moving piece down is ok
        /*********************************************************************/
        if(move_down && secondary_timer <= 0 && !new_brick)
        {
            /* reset secondary timer so you 
               cant drop the brick too fast */
            secondary_timer = 8;
            
            bool move_ok = true;
    
            /* iterate through game board */
            int i, j;
            for(i = GAMEBOARD_H-1; i >= 0; i--)
                for(j = GAMEBOARD_W-1; j >= 0; j--)
                    if(gameboard[i][j] == 4 || gameboard[i][j] == 5 || gameboard[i][j] == 6)
                    {
                        /* if out of bounds */
                        if(i+1 > GAMEBOARD_H-1)
                            move_ok = false;
                        else 
                        {
                            /* if a brick is there */
                            if(gameboard[i+1][j] == 1 || gameboard[i+1][j] == 2 || gameboard[i+1][j] == 3)
                                move_ok = false;
                        }
                    }
                    
            if(move_ok) /* if detection is OK then move the brick */
            {
                
                /* iterate through game board */
                int i, j;
                for(i = GAMEBOARD_H-1; i >= 0; i--)
                    for(j = GAMEBOARD_W-1; j >= 0; j--)
                        if(gameboard[i][j] == 4 || gameboard[i][j] == 5 || gameboard[i][j] == 6)
                        {
                            int temp = gameboard[i][j];
                            gameboard[i][j] = 0;
                            gameboard[i+1][j] = temp;
                        }
                        
                /* increment the bricks y coordinate */
                brick_y += 1;
                brick_move_timer = brick_move_difficulty;
            }
        }
        
     
        /* brick_move_timer hits zero. game can now move bricks, spawn bricks etc */
        if(brick_move_timer <= 0) 
        {
            /* Reset the brick_move_timer*/
            brick_move_timer = brick_move_difficulty;
    
    
            /************************************************************
            /* Spawn a new brick if one is needed
            /************************************************************/
            if(new_brick)
            {
                brick_type_current = brick_type_next;
                brick_color_current = brick_color_next;
                
                /* Randomize next brick */
                brick_type_next = (rand() % MAX_BRICK_TYPES);
                
                /* If its the same as last time, try one more time so two in a row is less likely */
                if(brick_type_current == brick_type_next)
                    brick_type_next = (rand() % MAX_BRICK_TYPES);
    
    
                /* Randomize next brick color. +4 to get in the movable brick color range (4-6) */
                brick_color_next = (rand() % MAX_BRICK_COLORS) + 4;
                
                /* If its the same as last time, keep trying until its different */
                while(brick_color_current == brick_color_next)
                    brick_color_next = (rand() % MAX_BRICK_COLORS) + 4;
                    
                
                /* reset the brick rotation and location */
                brick_type_rotation = 0;
                brick_x = 3;
                brick_y = 0;
                
                /* Place new brick on board */
                int i, j;
                for(i = 0; i < 4; i++)
                    for(j = 3; j < 7; j++)
                    {
                        /* width needs -3 to keep in the 4x4 brick array 
                           (j = 3 when calling scanBrick, need to compensate) */
                        if(scanBrick(brick_type_current, brick_type_rotation, i, j-3))
                        {
                            /* if hit an already placed brick */
                            if(gameboard[i][j] == 1 || gameboard[i][j] == 2 || gameboard[i][j] == 3)
                            {
                                muteAllSound();
                                playSound(samples[SAM_GAMEOVER]);
                                game_over = true;
                            }
                                
                            gameboard[i][j] = brick_color_current;  
                        }
                    }
                        
                /* no more need for a new brick, turn flag off */                     
                new_brick = false; 
            }
    
            /************************************************************
            /* See if moving pieces have hit a brick or bottom
            /************************************************************/
            bool brick_landed = false;
            int i, j;
            /* iterate through game board */
            for(i = GAMEBOARD_H-1; i >= 0; i--) 
                for(j = GAMEBOARD_W-1; j >= 0; j--)
                    if(gameboard[i][j] == 4 || gameboard[i][j] == 5 || gameboard[i][j] == 6)
                    {
                        /* if at bottom, or hit a brick, brickify the moving piece */
                        if(i+1 >= GAMEBOARD_H || gameboard[i+1][j] == 1 || gameboard[i+1][j] == 2 || gameboard[i+1][j] == 3)
                        {
                            /* iterate through game board and brickify moving pieces */
                            int k, l;
                            for(k = GAMEBOARD_H-1; k >= 0; k--)
                                for(l = GAMEBOARD_W-1; l >= 0; l--)
                                    if(gameboard[k][l] == 4 || gameboard[k][l] == 5 || gameboard[k][l] == 6)
                                        gameboard[k][l] = gameboard[k][l]-3;
                                        
                            /* request new brick */
                            new_brick = true;
                            brick_landed = true;
                        }
                    }
                    
            /* if a brick was placed, add a small bit of score */
            if(brick_landed)
                score += level*10;
                
               
                    
            /************************************************************
            /* Move bricks down (only if a brick is falling)
            /************************************************************/
            if(!new_brick && !move_down)
            {
                /* iterate through game board */
                for(i = GAMEBOARD_H-1; i >= 0; i--) 
                    for(j = GAMEBOARD_W-1; j >= 0; j--)
                        if(gameboard[i][j] == 4 || gameboard[i][j] == 5 || gameboard[i][j] == 6)
                        {
                            int temp = gameboard[i][j];
                            gameboard[i][j] = 0;
                            gameboard[i+1][j] = temp;
                        }
                        
                /* increment the bricks y coordinate from moving */
                brick_y += 1;
            }
            
            /************************************************************
            /* Check if row should be scored
            /************************************************************/
            int score_multiplier = 0;
            bool check_repeat = true;
            while(check_repeat)
            {
                /* set multiplier to zero */
                check_repeat = false;
                
                /* iterate through game board */
                for(i = GAMEBOARD_H-1; i >= 0; i--)
                {
                    bool row_clear = true;
                    
                    for(j = GAMEBOARD_W-1; j >= 0; j--)
                        if(gameboard[i][j] == 0 || gameboard[i][j] == 4 || gameboard[i][j] == 5 || gameboard[i][j] == 6)
                        {
                            /* if row has empty spot, or active brick, do not clear row */
                            row_clear = false;
                        }
                    
                    /* clear row if it passes check */
                    if(row_clear && i > 0)
                    {
                        int k, l;
                        for(k = i; k > 0; k--)
                            for(l = GAMEBOARD_W-1; l >= 0; l--)
                                gameboard[k][l] = gameboard[k-1][l];
                                
                        /* there was a row clear this check, so repeat the process after this one is done 
                           to clear multiple rows at one time */
                        check_repeat = true;
                        /* increment score multiplier to multiply score and repeat score check 
                            processes for mega points */
                        if(!score_multiplier)
                            score_multiplier = 1; /* set initial value if multiplier == 0 */
                        score_multiplier *= 2; /* increase the multiplier */
                    }
                }
            }
            
            /* set the score glow according to how many rows were eliminated */
            if(score_multiplier >= 2)
                score_glow = 0.4f;
                
            if(score_multiplier >= 4)
                score_glow = 0.5f;
                
            if(score_multiplier >= 8)
                score_glow = 0.6f;
                
            if(score_multiplier >= 16)
                score_glow = 0.8f;
            
            /* if a rpw was cleared, add score. big points for multi rows */
            if(score_multiplier > 0)
                score += 40*level*score_multiplier;
    
    
        }
    } /* if(!game_over) */
    


    /************************************************************
    /* Update other general logic
    /************************************************************/
    /* decrement the brick_move_timer for timed game stuff */
    brick_move_timer -= time_delta * 0.1;
    /* animation theta aswell */
    theta += time_delta * 0.01;
    /* secondary timer for move_down input
       so you cant drop a brick too fast! */
    if(secondary_timer > 0)
        secondary_timer -= time_delta * 0.1;
        
    /* update scoring glow */
    if(score_glow > GLOW_MIN)
        score_glow -= time_delta * 0.001;
    if(score_glow < GLOW_MIN)
        score_glow = GLOW_MIN;
        
    /* update other stuff */
    updateStarRank();
    updateSkillLevel();
    
    /* if the player lost, do game over effects */
    if(game_over){
        updateGameOver();
    }        

}












  

/*****************************************************************************

    Function: screenGameplayDrawing

    Description: gameplay drawing here
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void screenGameplayDrawing()
{
    
    /************************************************************
    /* Draw the background
    /************************************************************/
    enableOrtho2D();
        draw2DTexture(0, 0, textures[TEX_BACKGROUND]);
    disableOrtho2D();

    /************************************************************
    /* Draw the 3d background and brick tray
    /* Do it manually as it is special.
    /************************************************************/
    int i, j;
    for(i = 0; i < BACKGROUND_H; i++)
    {
        for(j = 0; j < BACKGROUND_W; j++)
        {
            if(background[i][j] != 0)
            {
                cleanObject();
                glTranslatef((j*-1)+15.5,(i*-1)+1,10);
                glScalef(1, 1, 1);
                    
                switch(background[i][j])
                {
                    case 1:
                        glColor4f ( score_glow, score_glow, score_glow, 1.0f );                        
                        glutSolidCube(1);
                    break;
                    case 2:
                        glColor4f ( GREY_1, GREY_1, GREY_1, 1.0f );
                        glutSolidCube(0.95);
                    break; 
                    case 3:
                        glColor4f ( GREY_2, GREY_2, GREY_2, 1.0f );
                        glutSolidCube(0.95);
                    break; 
                    case 4:
                        glColor4f ( GREY_3, GREY_3, GREY_3, 1.0f );
                        glutSolidCube(0.95);
                    break; 
                }
                
            }
        }   
    }
    
    /************************************************************
    /* Draw the gameboard
    /************************************************************/
    for(i = 0; i < GAMEBOARD_H; i++)
    {
        for(j = 0; j < GAMEBOARD_W; j++)
        {
            if(gameboard[i][j] != 0)
            {
                switch(gameboard[i][j])
                {
                    
                    /* Stationary */
                    case 1:
                        drawBlockStationary((j*-1)+4.5,(i*-1), 0.5, 0.25, 0.035);
                    break;
                    case 2:
                        drawBlockStationary((j*-1)+4.5,(i*-1), 0.4, 0.4, 0.05);
                    break;
                    case 3:
                        drawBlockStationary((j*-1)+4.5,(i*-1), 0.45, 0.0, 0.0);
                    break;
                    
                    /* Movers */
                    case 4:
                        drawBlockMoving((j*-1)+4.5,(i*-1), 0.6, 0.3, 0.05);
                    break;
                    case 5:
                        drawBlockMoving((j*-1)+4.5,(i*-1), 0.5, 0.5, 0.06);
                    break;
                    case 6:
                        drawBlockMoving((j*-1)+4.5,(i*-1), 0.55, 0.0, 0.0);
                    break;
                    
                    /* Grey, gameover blocks. A special, draw them manually */
                    case 7:
                        drawBlockBackground((j*-1)+4.5,(i*-1), GREY_1, GREY_1, GREY_1);
                    break;
                    case 8:
                        drawBlockBackground((j*-1)+4.5,(i*-1), GREY_1, GREY_1, GREY_1);
                    break;
                    case 9:
                       drawBlockBackground((j*-1)+4.5,(i*-1), GREY_1, GREY_1, GREY_1);
                    break;
                }
            }
        }   
    }
    
    

    
    /************************************************************
    /* Create and draw "next brick" (ie the green one :)
    /* It is special, so draw it manually.
    /************************************************************/
    cleanObject();
    glTranslatef(-10.9f, 1.0f, -5.0f); /* move it over to the top right */
    
    switch(brick_type_next)
    {
        case 0:
            glTranslatef( 0.25, -8.5, 10);
            glRotatef(theta*10,3.0, 2.5, 0.0f);
        break;
        case 1:
            glTranslatef( 0.5, -9.0, 10);
            glRotatef(theta*10,2.0, 2.5, 0.0f);
        break;
        case 2:
            glTranslatef( 0.5, -8.75, 10);
            glRotatef(theta*10,2, 2, 0.0f);
        break;
        case 3:
            glTranslatef( -0.3, -9.25, 10);
            glRotatef(theta*10,2, 2, 0.0f);
        break;
        case 4:
            glTranslatef( 0, -9, 10);
            glRotatef(theta*10,2.0, 2.0, 0.0f);
        break;
        case 5:
            glTranslatef( 0.15, -9.5, 10);
            glRotatef(theta*10,2.0, 2.5, 0.0f);
        break;
        case 6:
            glTranslatef( 0.0, -8.5, 10);
            glRotatef(theta*10,2.0, 1.5, 0.0f);
        break;
    } 
         
    glScalef(1, 1, 1);               
		
    for(i = 0; i < GAMEPIECE_H; i++)
    {
        glTranslatef( 0, 1, 0);
        
        for(j = 0; j < GAMEPIECE_W; j++)
        {
            glTranslatef( 1, 0, 0);
            
            if(scanBrick(brick_type_next, 0, i, j))
            {
                /* Draw the shell */
                glScalef(1, 1, 0.9);
                glColor4f ( 0.0f, 0.0f, 0.0f, 1.0f );
                glutSolidCube(1.0);
                glScalef(1, 1, 1.1);
                
                /* Draw inner green color */
                glColor4f( 0.0f, 0.5f, 0.0f, 1.0f );
                glutSolidCube(.95);      
            }
        } 
             
        glTranslatef( -GAMEPIECE_W, 0, 0);
    }
    
                
    /************************************************************
    /* Draw HUD (score, star rank etc)
    /************************************************************/
    enableOrtho2D();

        draw2DTexture(0, 0, textures[TEX_HEADER]);
        draw2DNumberFromRight(788, 27, textures[TEX_NUMBERS], 14, 16, score);
        drawStarRank();
        
        if(game_over)
            drawGameOver();
            
    disableOrtho2D(); 
}
