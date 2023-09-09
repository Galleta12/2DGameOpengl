#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <vector>


#include "SDWINDOW.h"
#include "MouseHandler.h"

#include "Transform.h"
#include "Player.h"
#include "Gun.h"
#include "Floor.h"
#include "Clocker.h"

//gizmos
#include "Gizmos.h"


//static variables at the beggining
//window height and width
int* SDWINDOW::WindowWidth = nullptr;
int* SDWINDOW::WindowHeight = nullptr;

//keep track of SDL2 events
SDL_Event SDWINDOW::event;
//to know if the game is running or not
bool SDWINDOW::isRunning = false;

//float SDWINDOW::delta_time = 0.0f;


//mousehandler class
MouseHandler *mouseHandler = nullptr;


//transform list
std::vector<Transform*> transformList;
//player object
Player *player = nullptr;
//floor object
Floor *floorObject = nullptr;




SDWINDOW::SDWINDOW() {
  
}
SDWINDOW::~SDWINDOW() {

    // Clean up dynamically allocated objects
    delete player;
    delete floorObject;
    delete mouseHandler;

    // Clean up the objects in transformList vector
    for (Transform* transform : transformList) {
       delete transform;
    }
    transformList.clear(); // Optionally, clear the vector after deleting its elements
}


void SDWINDOW::init(const char* title, int posX, int posY, int width, int height, bool fullscreen) {

    WindowWidth = &width;
    WindowHeight = &height;

    int flags = 0;

    if (fullscreen)flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        std::cout << "Subsysteam intialized" << std::endl;

        

        window = SDL_CreateWindow(title, posX, posY, width, height, SDL_WINDOW_OPENGL);
        if (window) {
            std::cout << "Winwdow Created" << std::endl;
        }

        //start gl 2.1 version
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        
        // important to always start the context, after the window
        glContext = SDL_GL_CreateContext(window);

       
        if (glContext != nullptr)
        {
            
            glClearColor(0.8f, 1.0f, 1.0f, 5.0f);


            
            isRunning = true;

            //start mouse class
            mouseHandler = new MouseHandler();
            player = new Player(300.0f,300.0f,5);
            //gun data
            player->gunData(20,50);
            
            //floorObject
            floorObject = new Floor(1.0f, height /4);
            
       
            transformList.emplace_back(floorObject);
            
            transformList.emplace_back(player);

        }
        else {
            std::cout << "No GL context" << std::endl;
        }

        
        
    }
    else {
        std::cout << "Error" << std::endl;
    }

}



void SDWINDOW::handleEvents() {
    
    SDL_PollEvent(&event);
    //first check if the user close the screen
    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
       
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            //move box with keyboard
            case SDLK_m:
                
                
                std::cout << "Change to the move state " << std::endl;
                
                break;
            //add move boxes with mouse pos
            case SDLK_a:
                
                
                break;
            //bounce box
            case SDLK_b:
                
                
                break;
            
            default:
                break;
            }
        
        
        default:
            break;
    }

    //mouse
    mouseHandler->mousePos();
    //get mouse position
    player->getGun()->setMousePosition(mouseHandler->getMousePos());
    
    //handle playerdirectionmoves
    player->keyboard();
}

void SDWINDOW::display()
{



        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        gluOrtho2D(0, *WindowWidth, 0, *WindowHeight);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        glViewport(0, 0, *WindowWidth, *WindowHeight);
        
   
        glClear(GL_COLOR_BUFFER_BIT);



        //render transforms objects

        
        float dt = Clocker::GetInstance()->GetDelatTime();
        for(auto& a : transformList){
            a->draw(dt);
        }
        

        renderGizmos();
    
        // swap to new updated screen to render
        SDL_GL_SwapWindow(window);

}


void SDWINDOW::renderGizmos()
{

    for(auto& g : Gizmos::instances){
        g->DrawLine();
        g->DrawRay();
    }

}

void SDWINDOW::update() {

    
    float dt = Clocker::GetInstance()->GetDelatTime();
    
    for(auto& a : transformList){
        a->update(dt);
    }
    
    

}




void SDWINDOW::clean() {
    SDL_DestroyWindow(window);
    window = NULL;
    //cleangizmos
    Gizmos::Cleanup();
    SDL_Quit();
    std::cout << "Game closed" << std::endl;
}

