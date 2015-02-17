//fallowed tutorila from Lazy Foo http://lazyfoo.net/tutorials/OpenGL/05_texture_mapping_and_pixel_manipulation/index.php


#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "LOpenGL.h"
#include <stdio.h>

#define MAX_TEXTURE 255

struct LTexture
{
	GLuint mTextureID;
	GLuint mTextureWidth;
    GLuint mTextureHeight;
	bool inUse;

};

LTexture *NewTexture();
void FreeTexture(LTexture *tex);
LTexture *LoadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height );
void RenderTexture(LTexture *tex, GLfloat x, GLfloat y );

extern LTexture listOfTexture[MAX_TEXTURE];
extern int max_texture;

#endif
