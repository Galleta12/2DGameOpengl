#include "Player.h"


#include <iostream>

#include <vector>
#include <chrono>

#include "SDWINDOW.h"




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


void Player::update()
{
    //update the player motion
    motion.x = keydirX * speed;
    
    
    // std::cout << "keydir x" << keydirX << std::endl;
    // std::cout << "speed" << speed << std::endl;
    // std::cout << "Motion x" << motion.x << std::endl;
    //motion.y = 
    //update position
    //position.x += motion.x;
    position.x += motion.x * SDWINDOW::delta_time;

    // std::cout << "New position x" << position.x << std::endl;
    //std::cout << "delta time" << SDWINDOW::delta_time << std::endl;



}


void Player::draw()
{

    glPushMatrix();
    
    //std::cout << "New position x" << position.x << std::endl;
    
    glTranslatef(position.x,position.y,0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    

    
    glVertex2f(0.0f, 0.0f); // Top vertex
    glVertex2f(-50.0f,-100.0f); // Bottom-left vertex
    glVertex2f(50.0f, -100.0f);  // Vertex 3
    // glVertex2f(playerPosX, playerPosY); // Top vertex
    // glVertex2f(playerPosX - 50.0f, playerPosY - 100.0f); // Bottom-left vertex
    // glVertex2f(playerPosX + 50.0f, playerPosY - 100.0f);  // Vertex 3

    //std::cout<<"Playerpox: " << playerPosX << std::endl;
   
    glEnd();
    //glTranslatef(gun->position.x,gun->position.y,0.0f);
    gun->draw();
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
        
        case SDLK_LEFT:
            
            
            keydirX = -1.0f;
            
            break;
        
        case SDLK_RIGHT:
           
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
        case SDLK_LEFT:
        case SDLK_RIGHT:
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
    Vector2D leftButton (position.x-50.0f,position.y-100.0f);
    Vector2D rightButton (position.x + 50.0f, position.y - 100.0f);

    
    
    float centerX = (leftButton.x + top.x + rightButton.x) / 3.0f;
    float centerY = (leftButton.y + top.y + rightButton.y) / 3.0f;

    centerTriangle.x = centerX;
    //sdl on the y is different
    centerTriangle.y =  centerY;
    //print vector center
    std::cout << "Center triangle: " <<centerTriangle << " For the cordinates on mouse on y " << *SDWINDOW::WindowHeight -centerTriangle.y << std::endl;

}

void Gun::rotateGun()
{
}

void Gun::update()
{



}

void Gun::draw()
{
    glPushMatrix();

    //glTranslatef(centerPlayerTriangleRef.x,centerPlayerTriangleRef.y,0.0f);
    glTranslatef(0.0f,0.0f,0.0f);

    
    
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,1.0f);

    // Draw a thin box (rectangle)
    // glVertex2f(0.0f, 0.0f);            // Top-left corner
    // glVertex2f(width, 0.0f);           // Top-right corner
    // glVertex2f(width, height);         // Bottom-right corner
    // glVertex2f(0.0f, height);          // Bottom-left corner

    glVertex2f(0.0f, -60.0f);            // Top-left corner
    glVertex2f(width, -60.0f);           // Top-right corner
    glVertex2f(width, height-60.0f);         // Bottom-right corner
    glVertex2f(0.0f, height-60.0f);      
    //std::cout << "Gun widht: " << width << " Heigh: " << height << std::endl;
    glEnd();

    glPopMatrix();



}

std::ostream &operator<<(std::ostream &stream, const Gun &g)
{
    // TODO: insert return statement here
     stream << "Gun Pos(" << g.gunPosX << "," << g.gunPosY << ")\n"
     << "Gun TranformPos(" << g.position.x << "," << g.position.y << ")\n"
     << "Gun Refence of center player(" << g.centerPlayerTriangleRef << "This is the y component of sdl window "<< *SDWINDOW::WindowHeight - g.centerPlayerTriangleRef.y << ")";
     return stream;
}
