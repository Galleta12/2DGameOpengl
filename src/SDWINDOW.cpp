#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <vector>


#include "SDWINDOW.h"
#include "MouseHandler.h"
#include "Clocker.h"
//gizmos
#include "Gizmos.h"


#include "Player.h"
#include "Gun.h"
#include "Floor.h"
#include "Platforms.h"
#include "Box.h"
#include "Enemy.h"





//static variables at the beggining
//window height and width
int* SDWINDOW::WindowWidth = nullptr;
int* SDWINDOW::WindowHeight = nullptr;

//keep track of SDL2 events
SDL_Event SDWINDOW::event;
//to know if the game is running or not
bool SDWINDOW::isRunning = false;

//mousehandler class
MouseHandler *mouseHandler = nullptr;


//transform list
//we want this to be static since the physics components must have access to this
std::vector<std::shared_ptr<Transform>> SDWINDOW::transformList;
//player object
//Player *player = nullptr;
std::shared_ptr<Player> player;

//state of Game
SDWINDOW::GameState SDWINDOW::gameState = SDWINDOW::GameState::ONGAME;


SDWINDOW::SDWINDOW() {
  
}
SDWINDOW::~SDWINDOW() {

    // Clean up dynamically allocated objects
    //delete player;
 
    delete mouseHandler;
    //delete bullet;

    // Clean up the objects in transformList vector
    // for (Transform* transform : transformList) {
    //    delete transform;
    // }
    transformList.clear(); // Optionally, clear the vector after deleting its elements
}

//start sdwindow and opengl
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
            //populate the world
            setObjectsLists();

        }
        else {
            std::cout << "No GL context" << std::endl;
        }

        
    }
    else {
        std::cout << "Error" << std::endl;
    }

}


void SDWINDOW::setObjectsLists()
{
    //start mouse class
    mouseHandler = new MouseHandler();
    //save player initial position
    initialPlayerX = 300.0f;
    initialPlayerY = 300.0f;
    //start the player instance
    player = std::make_shared<Player>(300.0f,300.0f,5);
    //set the bullet for test
    player->gunData(20,50);
    
    //floorObject
    //std::unique_ptr<Floor> floorObject = std::make_unique<Floor>(1.0f, *SDWINDOW::WindowHeight /10);
     
    transformList.push_back(std::make_unique<Floor>(1.0f, *SDWINDOW::WindowHeight /10));
    
    transformList.push_back(player);
    
    //set the boxes
    setMultipleBoxes();
    //set platforms
    setMultiplePlatforms();

    //set enemies
    setMultipleEnemies();


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

    
    objectsEvents();
}


void SDWINDOW::objectsEvents(){
    
    int mouseClickX = 0;
    int mouseClickY = 0;
    
   
    //update the camera cordinates
    updateCameraCordinates();
    
    
    //mouse set up positon relative to the camera
    mouseHandler->mousePos(cameraX ,cameraY);
    //get mouse position and set it up on the gun
    player->getGun()->setMousePosition(mouseHandler->getMousePos());
    //handle playerdirectionmoves
    player->keyboard();
    
    //check if there was a click
     if(event.type == SDL_MOUSEBUTTONDOWN){
        switch (event.button.button)
        {
            case SDL_BUTTON_LEFT:
            mouseClickX = SDWINDOW::event.button.x;
            mouseClickY = SDWINDOW::event.button.y;

            std::cout<< "Mouse X: " << mouseClickX << "Mouse y: " << mouseClickY << std::endl;

             std::cout<<  "Mouse y in gl context: " << cameraX << "Y" << cameraY << std::endl;        
            
            player->getGun()->mouseLeftPressed();
            
            break;
            
            case SDL_BUTTON_RIGHT:
            
            break;
            
            default:
            break;
        
        
        
        }
     }
    
    
    
}

void SDWINDOW::setMultiplePlatforms()
{
    
    
     transformList.push_back(std::make_unique<Platforms>(300.0f,600.0f, 500.0f, 600.0f));
     transformList.push_back(std::make_unique<Platforms>(1166.0f, 558.0f, 949.0f, 434.0f));
     transformList.push_back(std::make_unique<Platforms>(295.0f, 500.0f, 295.0f, 394.0f));
     transformList.push_back(std::make_unique<Platforms>(576.0f, 501.0f, 538.0f, 425.0f));
    
    
    //we want for now 3 platforms
    // Platforms* p1 = new Platforms(300.0f,600.0f, 500.0f, 600.0f);
    // transformList.emplace_back(p1);
    // // // Create the second diagonal platform (p2)  
    // Platforms* p2 = new Platforms(1166.0f, 558.0f, 949.0f, 434.0f);
    // transformList.emplace_back(p2);
    // // // Create the third diagonal platform (p3)
    // Platforms* p3 = new Platforms(295.0f, 500.0f, 295.0f, 394.0f);
    // transformList.emplace_back(p3);
    
    // Platforms* p4 = new Platforms(576.0f, 501.0f, 538.0f, 425.0f);
    // transformList.emplace_back(p4);

    // Platforms* p5 = new Platforms(576.0f, 150.0f, 538.0f, 400.0f);
    // transformList.emplace_back(p5);


}

void SDWINDOW::setMultipleBoxes()
{
    
      transformList.push_back(std::make_unique<Box>(600.0f,250.0f,true));
      transformList.push_back(std::make_unique<Box>(100.0f,250.0f,true));
    
    // Box* p1 = new Box(600.0f,250.0f,true);
    // transformList.emplace_back(p1);
    
    // Box* p2 = new Box(100.0f,250.0f,true);
    // transformList.emplace_back(p2);
    
    

}

void SDWINDOW::setMultipleEnemies()
{
    
     //transformList.push_back(std::make_unique<Enemy>(1200.0f,200.0f,player.get()));
    // Enemy* e1 = new Enemy(1200.0f,200.0f,player);
    // transformList.emplace_back(e1);

}


void SDWINDOW::display()
{
        
        updateCameraCordinates();

        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        //gluOrtho2D(0, *WindowWidth, 0, *WindowHeight);
        gluOrtho2D(cameraX, cameraX + *WindowWidth, cameraY, cameraY + *WindowHeight);
        
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        glViewport(0, 0, *WindowWidth, *WindowHeight);
        
   
        glClear(GL_COLOR_BUFFER_BIT);



        //render transforms objects
        
        float dt = Clocker::GetInstance()->GetDelatTime();
        
        for(auto& a : transformList){
            if(a!=nullptr){

                a->draw(dt);
            }
        }
        
        //render gizmos instances
        renderGizmos();
    
        // swap to new updated screen to render
        SDL_GL_SwapWindow(window);

}


void SDWINDOW::renderGizmos()
{

    for(auto& g : Gizmos::instances){
        g->DrawLine();
        g->DrawRay();
        g->DrawPoints();
    }

}

void SDWINDOW::update() {

    
     
    //handle the main loop depending on the state of the game
    
         
    switch (gameState)
    {
    case GameState::ONGAME:
        updateLogicHandler();
        break;
    case GameState::LOSS:
        
        restartGame();
        //we also want to reset the state of the game
        gameState = SDWINDOW::GameState::ONGAME;
        
        break;
    case GameState::WIN:
        break;
    default:
        break;
    }
    
    



}



//clean everything with the gizmos
void SDWINDOW::clean() {
    SDL_DestroyWindow(window);
    window = NULL;
    //cleangizmos
    Gizmos::Cleanup();
    SDL_Quit();
    std::cout << "Game closed" << std::endl;
}



//this will restart the game and delete any bullet transform
void SDWINDOW::restartGame()
{
    player->resetPosition(initialPlayerX, initialPlayerY);

    // Create a new vector to store the updated transform list without bullets
    std::vector<std::shared_ptr<Transform>> updatedTransformList;

    // Iterate through the transformList and move non-bullet objects to the updated list
    for (auto& transform : transformList) {
        if (!transform->isBullet) {
            updatedTransformList.push_back(transform);
        }
    }

    // Clear the original transformList
    transformList.clear();

    // Move ownership of updatedTransformList to transformList
    transformList = updatedTransformList;
}


void SDWINDOW::updateCameraCordinates()
{

    // Calculate the camera's x-coordinate centered around the player
    //the same for y
    
    const Vector2D playerPosition = player->getPlayerPos();
    cameraX = 300 - (*WindowWidth / 4.0f);
    cameraY = 300 - (*WindowHeight/ 2.0f);


}



void SDWINDOW::updateLogicHandler()
{

    float dt = Clocker::GetInstance()->GetDelatTime();
    
    for(auto& a : transformList){
            if(a!=nullptr){

                a->update(dt);
            }
    }
        
    
    
    //only collision for transforms with physics added to it
    for(int a=0; a < transformList.size()-1; a++){
        //store first object
        Transform* polygon1 = transformList[a].get(); 
        if(polygon1->getPhysics2D() == nullptr)continue;
        
        for(int b=a+1; b<transformList.size();b++){
            Transform* polygon2 = transformList[b].get(); 
            
            if(polygon2->getPhysics2D() == nullptr)continue;
           
            float depth = std::numeric_limits<float>::infinity();; 
            Vector2D normalCollision;
            
            bool isIntersection = Physics2D::satColliderChecker(polygon1,polygon2,depth,normalCollision);
            if (isIntersection) {
                //std::cout << "Collision" << std::endl;
                polygon1->OnCollision(dt,polygon2,Vector2D::InvertVector(normalCollision),depth/2.0f,normalCollision);
                
                polygon2->OnCollision(dt,polygon1,normalCollision,depth/2.0f,normalCollision);
            
            }
        
        }
    }
 

}
