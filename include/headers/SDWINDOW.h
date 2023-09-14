#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>
#include "Transform.h"

class Transform;
class SDWINDOW {

public:
    
    
    
    
    static enum GameState{
        ONGAME,
        WIN,
        LOSS
    };
    
    static GameState gameState;
    //constructor
    SDWINDOW();
    //deconstuctor
    ~SDWINDOW();

    
    static int* WindowWidth, * WindowHeight;
    //
    static bool isRunning;

    static SDL_Event event;

    
    
    static std::vector<Transform*> transformList;
    
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

    static void GameStateUpdater();


    float initialPlayerX = 0.0f;
    float initialPlayerY = 0.0f;

private:
    
    float cameraX = 0.0f;
    float cameraY = 0.0f;
    
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
    //for rendering gizmis
    void setObjectsLists();
    void renderGizmos();
    void objectsEvents();
    void setMultiplePlatforms();
    void setMultipleBoxes();
    void setMultipleEnemies();
    void restartGame();
    void updateLogicHandler();
    void updateCameraCordinates();
        

};

