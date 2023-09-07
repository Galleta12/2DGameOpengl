#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <vector>

#include "SDWINDOW.h"



//start the sdlwindow
SDWINDOW *sdWindow= nullptr;


int main(int argc, char *argv[])
{

	//size screen
	const int WIDTH = 1200;
	const int HEIGHT = 600;

	//cap frame rate
	const int FPS = 144;

	//how long a frame is meant to take
	//this gives max we have between frames
	const int frameDelay = 1000/FPS;
    //how many seconds it has been since we first initialize sdl
	Uint32 frameStart;
	int frameTime;
	



	//start sdl
	sdWindow = new SDWINDOW();
	sdWindow->init("Game 2D", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,false);

	

	//main loop game
	while(sdWindow->running()){
		frameStart = SDL_GetTicks();

		//deltatime
		//sdWindow->delta_time = (SDL_GetTicks() - frameStart)/1000.0f;
		
		SDWINDOW::clock.tick();
		
		std::cout <<"deltatime in main: "<< SDWINDOW::clock.deltaTime << std::endl;
		


		//events of sdl2
		sdWindow->handleEvents();
		
		//sdWindow->delta_time = SDL_GetTicks()/1000.0f;
		
		//the update of the game
		sdWindow->update();
		//the render of the game
		sdWindow->display();

		
		//frameRate control
		//this is for controlling the frame rate and have a consisten frame rate on the window.
		
		//the frame time in miliseconds
		frameTime=SDL_GetTicks() - frameStart;
		//we can check if we need to delay
		//we need to delay if this is true
		if(frameDelay > frameTime){
			SDL_Delay(frameDelay-frameTime);	
		}

		
	
	
	}

	sdWindow->clean();

	return 0;
}