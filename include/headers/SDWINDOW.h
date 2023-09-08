#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>


class SDWINDOW {

public:
    
    
    
    
    //constructor
    SDWINDOW();
    //deconstuctor
    ~SDWINDOW();

    
    static int* WindowWidth, * WindowHeight;
    //
    static bool isRunning;

    static SDL_Event event;

    //static float delta_time;


    
    //start sdl2 and opengl
    void init(const char* title, int posX, int posY, int width, int height, bool fullscreen);
    //sdl2 events
    void handleEvents();
    //update, main logic of the game here
    void update();
    //display of the boxes
    void display();
    
    void clean();
    
    bool running() { return isRunning; }



private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;


};

