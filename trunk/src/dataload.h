#ifndef _DATALOAD_H_
#define _DATALOAD_H_

extern void loadData();

/* TEXTURE structure */
typedef struct
{
    GLuint id;
    int width, height;
} TEXTURE;

/* List of textures */
enum { TEX_HEADER, TEX_BACKGROUND, TEX_NUMBERS, TEX_STARLIT, TEX_STARBLANK, TEX_GAMEOVER, TEXTURE_COUNT };
/* Array of textures */
extern TEXTURE* textures[TEXTURE_COUNT];

/* List of samples */
enum { SAM_BRICKMOVE, SAM_BRICKLAND, SAM_GAMEOVER, SAMPLE_COUNT };
/* Array of samples */
extern FSOUND_SAMPLE* samples[SAMPLE_COUNT];

#endif
