#include "LTexture.h"
#include "LUtil.h"


#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
#define SCREEN_FPS 30

LTexture* gCheckerBoardTexture;


bool initGL()
{
    glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    glEnable( GL_TEXTURE_2D );
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

bool loadMedia()
{
    const int CHECKERBOARD_WIDTH = 128;
    const int CHECKERBOARD_HEIGHT = 128;
    const int CHECKERBOARD_PIXEL_COUNT = CHECKERBOARD_WIDTH * CHECKERBOARD_HEIGHT;
    GLuint checkerBoard[ CHECKERBOARD_PIXEL_COUNT ];
	for( int i = 0; i < CHECKERBOARD_PIXEL_COUNT; ++i )
    {
        GLubyte* colors = (GLubyte*)&checkerBoard[ i ];
		if( i / 128 & 16 ^ i % 128 & 16 )
        {
            //Set pixel to white
            colors[ 0 ] = 0xFF;
            colors[ 1 ] = 0xFF;
            colors[ 2 ] = 0xFF;
            colors[ 3 ] = 0xFF;
        }
        else
        {
            //Set pixel to red
            colors[ 0 ] = 0xFF;
            colors[ 1 ] = 0x00;
            colors[ 2 ] = 0x00;
            colors[ 3 ] = 0xFF;
        }
    }
	if( (gCheckerBoardTexture = (LoadTextureFromPixels32( checkerBoard, CHECKERBOARD_WIDTH, CHECKERBOARD_HEIGHT ) )) == NULL)
    {
        printf( "Unable to load checkerboard texture!\n" );
        return false;
    }

    return true;
}

void render()
{
    glClear( GL_COLOR_BUFFER_BIT );
	GLfloat x = ( SCREEN_WIDTH - gCheckerBoardTexture->mTextureWidth ) / 2.f;
	GLfloat y = ( SCREEN_HEIGHT - gCheckerBoardTexture->mTextureHeight ) / 2.f;
    RenderTexture(gCheckerBoardTexture, x, y );
    glutSwapBuffers();
}

void runMainLoop( int val )
{
    //Frame logic
    update();
    render();

    //Run frame one more time
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );
}