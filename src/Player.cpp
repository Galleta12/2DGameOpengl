#include "Player.h"



#include "SDWINDOW.h"

#include <iostream>

#include <vector>
#include <chrono>
#include <algorithm> 


void Player::gunData(int newSpeed, int newPower)
{
    calculateCenter();
    gun = new Gun(playerPosX,playerPosY,newSpeed,newPower,centerTriangle);

    //print gun
    std::cout << *gun << std::endl;
}

Player::~Player()
{
    delete gun;
}


void Player::update(float deltaTime)
{
    
    //this means that there is movement    
    if(isKeyDirx){

        //update the player motion
        motion.x = keydirX * speed;
        motion.x *= friction;
        //std::cout << "motion" << motion.x << std::endl;
    }
    else if(!isKeyDirx && motion.x != 0.0f){
        
        motion.x = std::max(motion.x, 0.0f);
        
        if(motion.x > 0.0f){
            motion.x *= 0.2f;
            
            //std::cout << "motion false" << motion.x << std::endl;
        }
     
    }


    
    
    
    //std::cout << "friction" << friction << std::endl;
    // std::cout << "keydir x" << keydirX << std::endl;
    // std::cout << "speed" << speed << std::endl;
    // std::cout << "Motion x" << motion.x << std::endl;
    //motion.y = 
    //update position
    
    position.x += motion.x * deltaTime;

    
    gun->updatePosition(deltaTime,motion);

    gun->update(deltaTime);

 


}


void Player::draw(float deltaTime)
{

    glPushMatrix();
    
    //std::cout << "New position x" << position.x << std::endl;
    
    glTranslatef(position.x,position.y,0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    
   

    
    glVertex2f(0.0f, 0.0f); // Top vertex
    glVertex2f(-25.0f,-50.0f); // Bottom-left vertex
    glVertex2f(25.0f, -50.0f);  // Vertex 3
    // glVertex2f(playerPosX, playerPosY); // Top vertex
    // glVertex2f(playerPosX - 50.0f, playerPosY - 100.0f); // Bottom-left vertex
    // glVertex2f(playerPosX + 50.0f, playerPosY - 100.0f);  // Vertex 3

    //std::cout<<"Playerpox: " << playerPosX << std::endl;
   
    glEnd();


    //we want to calculate the current center
    calculateCenter();
    
    gun->draw(deltaTime);
    //std::cout << "Gun draw: " <<*gun << std::endl;
    glPopMatrix();

}

void Player::keyboard()
{
    if(SDWINDOW::event.type == SDL_KEYDOWN){
        switch (SDWINDOW::event.key.keysym.sym)
        {
        // case SDLK_UP:
            
        //     yDir =  1;    
        //     break;
        
        // case SDLK_DOWN:
            
        //     yDir =  -1;    

        //     break;
        
        case SDLK_a:
            
            
            isKeyDirx = true;
            keydirX = -1.0f;
            
            break;
        
        case SDLK_d:
           
            isKeyDirx = true;
            keydirX = 1.0f;
            break;
        
        default:
            break;
        }
    }
    //when release the keyboard
    if(SDWINDOW::event.type == SDL_KEYUP){
        switch (SDWINDOW::event.key.keysym.sym)
        {
        // case SDLK_UP:
        // case SDLK_DOWN:
        //     yDir =  0;    
            
        //     break;        
        case SDLK_a:
        case SDLK_d:
            
            
            //we dont want to abruptely stop the movment hence we use this flag
            isKeyDirx = false;
            keydirX = 0.0f;
            break;
        
        default:
            break;
        }
    }

    //std::cout << "keydir: " <<keydirX << std::endl;

}

void Player::calculateCenter()
{
    
    //formula
    //
    // Vector2D top(playerPosX,playerPosY);
    // Vector2D leftButton (playerPosX-50.0f,playerPosY-100.0f);
    // Vector2D rightButton (playerPosX + 50.0f, playerPosY - 100.0f);

    
    Vector2D top(position.x,position.y);
    Vector2D leftButton (position.x-25.0f,position.y-50.0f);
    Vector2D rightButton (position.x + 25.0f, position.y - 50.0f);

    
    
    float centerX = (leftButton.x + top.x + rightButton.x) / 3.0f;
    float centerY = (leftButton.y + top.y + rightButton.y) / 3.0f;

    centerTriangle.x = centerX;
    //sdl on the y is different
    centerTriangle.y =  centerY;
    //print vector center
    //std::cout << "Center triangle: " <<centerTriangle << " For the cordinates on mouse on y " << *SDWINDOW::WindowHeight -centerTriangle.y << std::endl;

}

