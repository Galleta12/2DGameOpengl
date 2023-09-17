#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>
#include <memory>
#include "Transform.h"


class Transform;
class SDWINDOW {

public:
    
    //mangae the sate of the game    
    static enum GameState{
        ONGAME,
        Map1,
        Map2,
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

    
    static std::vector<std::shared_ptr<Transform>> transformList;
        
    //start sdl2 and opengl
    void init(const char* title, int posX, int posY, int width, int height, bool fullscreen);
    //sdl2 events
    void handleEvents();

    //update, main logic of the game here
    void update();
    
    //display of the boxes
    void display();
    
    void clean();
    //check if the game is running
    bool running() { return isRunning; }

    //save the initial position of the player
    float initialPlayerX = 0.0f;
    float initialPlayerY = 0.0f;

private:
    //camera that will follow the player    
    float cameraX = 0.0f;
    float cameraY = 0.0f;
    //set the windo and the gl context
    SDL_Window* window = nullptr;
    
    SDL_GLContext glContext = nullptr;
    
    //set objects in the vector transfor
    void setObjectsLists();
    //render gizmos instances
    void renderGizmos();
    //other events
    void objectsEvents();
    //set multiple platforms
    void setMultiplePlatforms();
    //set boxes and enemies
    void setMultipleBoxes();
    //set the enemies
    void setMultipleEnemies();
    //restart game
    void restartGame();
    //update logic 
    void updateLogicHandler();
    //update the camera
    void updateCameraCordinates();
        

};

