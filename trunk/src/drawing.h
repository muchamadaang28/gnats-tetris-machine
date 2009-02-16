#ifndef _DRAWING_H_
#define _DRAWING_H_

extern void blitScreen();
extern void enableOrtho2D();
extern void disableOrtho2D();
extern void draw2DTexture(float _x, float _y, TEXTURE* _tex);
extern void draw2DTextureEx(float _x, float _y, float _z, float _alpha,  TEXTURE* _tex);
extern void draw2DNumberFromRight(float _x, float _y, TEXTURE* _tex, int _char_width, int _char_height, int _number);
extern void draw2DNumberFromRightEx(float _x, float _y, float _z, float _alpha, TEXTURE* _tex, int _char_width, int _char_height, int _number);
extern void drawBlockStationary(float _x, float _y, float _r, float _g, float _b);
extern void drawBlockMoving(float _x, float _y, float _r, float _g, float _b);
extern void drawBlockBackground(float _x, float _y, float _r, float _g, float _b);
extern void doDrawing();

#endif
