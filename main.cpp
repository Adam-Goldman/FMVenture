#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_net.h>
#include<SDL_ttf.h>
#include<GL\freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include<stdio.h>
#include "LTexture.h"
#include "LUtil.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
#define SCREEN_FPS 30

long game_time = 0;
long delta = 0;
void input(); //takes in player input
void update(); //this will update game world
void draw();	/// draws the screen

int main(int argc, char* argv[])
{

	/*long last_time;
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("fmventure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//begining of game loop
	while(true)
	{
		last_time = game_time;
		game_time = SDL_GetTicks();
		delta = last_time - game_time;
		input();
		update();
		draw();
		if(delta < 17)
		{
			SDL_Delay(17 - delta);
		}
	}
	// end of game loop
	SDL_Quit();*/
	//Initialize FreeGLUT
    glutInit( &argc, argv );

    //Create OpenGL 2.1 context
    glutInitContextVersion( 2, 1 );

    //Create Double Buffered Window
    glutInitDisplayMode( GLUT_DOUBLE );
    glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
    glutCreateWindow( "OpenGL" );

    //Do post window/context creation initialization
    if( !initGL() )
    {
        printf( "Unable to initialize graphics library!\n" );
        return 1;
    }

    //Load media
    if( !loadMedia() )
    {
        printf( "Unable to load media!\n" );
        return 2;
    }

    //Set rendering function
    glutDisplayFunc( &render );

    //Set main loop
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );

    //Start GLUT main loop
    glutMainLoop();
	return 0;
}

void update()
{

}
void draw()
{
}
void input()
{
}