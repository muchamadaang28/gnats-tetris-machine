#include "master.h"

TEXTURE* textures[TEXTURE_COUNT];
FSOUND_SAMPLE *samples[SAMPLE_COUNT];

/*****************************************************************************

    Function: loadTexture

    Description: Loads a texture from filename and returns a pointer to
        the TEXTURE structure allocated (stores width, height and opengl id)
    Parameters: filename
    Return: Pointer to allocated TEXTURE struct

*****************************************************************************/
TEXTURE* loadTexture(char *filename) 
{
    SDL_Surface* surface;
    GLuint textureid;
    int mode;

    surface = IMG_Load(filename);
    
    /* Or if you don't use SDL_image you can use SDL_LoadBMP here instead:
    surface = SDL_LoadBMP(filename); */

    /* Could not load image */
    if (!surface) 
    {
        printf("Could not load image: %s", filename);
        return 0;
    }
    
    /* Work out what format to tell glTexImage2D to use... */
    if (surface->format->BytesPerPixel == 3) /* RGB 24bit */
    { 
        mode = GL_RGB;
    } 
    else if (surface->format->BytesPerPixel == 4) /* RGBA 32bit */
    { 
        mode = GL_RGBA;
    } 
    else 
    {
        printf("Could not determine pixel format of image: %s", filename);
        SDL_FreeSurface(surface);
        return 0;
    }

    /* Create one texture name */
    glGenTextures(1, &textureid);

    /* Tell opengl to use the generated texture name */
    glBindTexture(GL_TEXTURE_2D, textureid);

    /* Read from the sdl surface and put it into an opengl texture */
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

    /* Set up texture filters */
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    /* Allocate memory for Texture structure and fill it up */
    TEXTURE* texture = (TEXTURE*)malloc(sizeof(TEXTURE));
    
    /* Could not allocate memory */
    if (!texture)
    {
        printf("Could not create TEXTURE struct for image: %s", filename);
        return 0;
    }
    
    /* Set up TEXTURE structure */
    texture->width = surface->w;
    texture->height = surface->h;
    texture->id = textureid;
    
    
    /* Clean up */
    SDL_FreeSurface(surface);
    
    /* return pointer to image structure */
    return texture;
}
/*****************************************************************************

    Function: loadSample

    Description: Loads a sample from filename and returns a pointer to
        the FSOUND_SAMPLE structure allocated
    Parameters: filename
    Return: Pointer to FSOUND_SAMPLE struct

*****************************************************************************/
FSOUND_SAMPLE* loadSample(char *filename) 
{
    FSOUND_SAMPLE* sample;
    
    sample = FSOUND_Sample_Load(FSOUND_FREE, filename, FSOUND_STEREO, 0, 0); 

    /* Could not load sample */
    if (!sample) 
    {
        printf("Could not load sample: %s", filename);
        return 0;
    }
    
    return sample;
}
/*****************************************************************************

    Function: loadData

    Description: Loading data here
    Parameters: n/a
    Return: n/a

*****************************************************************************/
void loadData()
{
    /* Load textures */
    textures[TEX_HEADER] = loadTexture("data/textures/header.png");
    textures[TEX_BACKGROUND] = loadTexture("data/textures/background.png");
    textures[TEX_NUMBERS] = loadTexture("data/textures/numbers.png");
    textures[TEX_STARLIT] = loadTexture("data/textures/starlit.png");
    textures[TEX_STARBLANK] = loadTexture("data/textures/starblank.png");
    textures[TEX_GAMEOVER] = loadTexture("data/textures/gameover.png");
    /* Load samples */
    samples[SAM_BRICKMOVE] = loadSample("data/samples/brickmove.ogg");
    samples[SAM_BRICKLAND] = loadSample("data/samples/brickland.ogg");
    samples[SAM_GAMEOVER] = loadSample("data/samples/gameover.ogg");
} 
