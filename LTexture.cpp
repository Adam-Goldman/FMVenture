//fallowed tutorila from Lazy Foo http://lazyfoo.net/tutorials/OpenGL/05_texture_mapping_and_pixel_manipulation/index.php

#include "LTexture.h"
LTexture listOfTexture[MAX_TEXTURE];
int max_texture;

LTexture* NewTexture(void)
{
	int i;

	LTexture* tex = NULL;

	for(i = 0; i < max_texture; i++)
	{
		if(listOfTexture[i].inUse == false)	//see if memory is free
		{
			tex = &listOfTexture[i];
			tex->inUse = true;
			return tex;
		}
	}
	if(max_texture < 255)				//if there is memory at the end of the list
	{
		tex = &listOfTexture[max_texture++];
		tex->inUse = true;
	}
	else
	{
		fprintf(stderr, "Help me");
		exit(1);
	}
	return tex;
}

void InitLTexture(LTexture* tex)
{
	tex->mTextureID = 0;
	tex->mTextureWidth = 0;
	tex->mTextureHeight = 0;
}

LTexture* LoadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height )
{
	LTexture* tex = NewTexture();
	tex->mTextureWidth = width;
	tex->mTextureHeight = height;
	glGenTextures(1, &tex->mTextureID );
	glBindTexture(GL_TEXTURE_2D, tex->mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glBindTexture( GL_TEXTURE_2D, NULL );
	GLenum error = glGetError();
    if( error != GL_NO_ERROR )
	{
        printf( "Error loading texture from %p pixels! %s\n", pixels, gluErrorString( error ) );
        return false;
    }

    return tex;
}

void FreeTexture(LTexture* tex)
{
    if( tex->mTextureID != 0 )
    {
        glDeleteTextures( 1, &(tex->mTextureID));
        tex->mTextureID = 0;
    }

    tex->mTextureWidth = 0;
    tex->mTextureHeight = 0;
}

void RenderTexture(LTexture* tex, GLfloat x, GLfloat y )
{
    if( tex->mTextureID != 0 )
    {
        glLoadIdentity();
        glTranslatef( x, y, 0.f );
        glBindTexture( GL_TEXTURE_2D, tex->mTextureID );
        glBegin( GL_QUADS );
            glTexCoord2f( 0.f, 0.f ); glVertex2f(           0.f,            0.f );
            glTexCoord2f( 1.f, 0.f ); glVertex2f( tex->mTextureWidth,            0.f );
            glTexCoord2f( 1.f, 1.f ); glVertex2f( tex->mTextureWidth, tex->mTextureHeight );
            glTexCoord2f( 0.f, 1.f ); glVertex2f(           0.f, tex->mTextureHeight );
        glEnd();
    }
}

GLuint getTextureID(LTexture* tex)
{
    return tex->mTextureID;
}

GLuint textureWidth(LTexture* tex)
{
    return tex->mTextureWidth;
}

GLuint textureHeight(LTexture* tex)
{
    return tex->mTextureHeight;
}
