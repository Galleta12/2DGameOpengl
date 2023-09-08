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


void Player::update(float deltaTime)
{
    //update the player motion
    motion.x = keydirX * speed;
    
    
    // std::cout << "keydir x" << keydirX << std::endl;
    // std::cout << "speed" << speed << std::endl;
    // std::cout << "Motion x" << motion.x << std::endl;
    //motion.y = 
    //update position
    
    position.x += motion.x * deltaTime;

    gun->updatePosition(deltaTime,motion);

    gun->update(deltaTime);

    // //we want to get the direction of the mouse from the vector position
    // Vector2D dir = (gun->getMousePosition() - position).Normalize();
    // Vector2D posDir = Vector2D::Normalized(position);

    
    
    // // std::cout << "Normalize dir" << dir << std::endl;
    // // std::cout << "Normalize position" << posDir << std::endl;
    
    
    // angleMouse = Vector2D::Angle(getUpVec(),dir);
    
    // std::cout << "angle: " << angleMouse << std::endl;
    // //std::cout << "up vector: " << getUpVec() << std::endl;


    //we need to update the gunposition aswell, even if the position is updated by the player in the matrix stack we need to do the same

    // std::cout << "New position x" << position.x << std::endl;
    //std::cout << "delta time" << SDWINDOW::delta_time << std::endl;



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

void Gun::setMousePosition(std::vector<int> mousePositions)
{
    mousePos.x = static_cast<float>(mousePositions[0]);
    mousePos.y =  *SDWINDOW::WindowHeight - static_cast<float>(mousePositions[1]);
    //std::cout<< "Mouse current X: " << mousePos.x << "Mouse current y: " << mousePos.y << std::endl;     

}

void Gun::updatePosition(float deltaTime, Vector2D motion)
{
    position.x += motion.x * deltaTime;

}

void Gun::rotateGun()
{
    //we want to get the direction of the mouse from the vector position
    Vector2D dir = (getMousePosition() - position).Normalize();
    Vector2D posDir = Vector2D::Normalized(position);

    
    
    // std::cout << "Normalize dir" << dir << std::endl;
    // std::cout << "Normalize position" << posDir << std::endl;
    
    
    //angleMouse = Vector2D::Angle(getUpVec(),dir);
    //angleMouse = Vector2D::SignedAngle(getRightVec(),dir);
    float angle = std::atan2(dir.y, dir.x) * 180.0f / PI;
    angleMouse = angle;
    
    //std::cout << "angle: " << angleMouse << std::endl;
    //std::cout << "up vector: " << getUpVec() << std::endl;

}

void Gun::update(float deltaTime)
{

    rotateGun();


}

void Gun::draw(float deltaTime)
{
    glPushMatrix();

    
    
    //std::cout<< "Current center" << centerPlayerTriangleRef << std::endl;
    Vector2D centerInLocal;
    centerInLocal.x = centerPlayerTriangleRef.x - position.x;
    centerInLocal.y = centerPlayerTriangleRef.y - position.y;
    
    glTranslatef(centerInLocal.x,centerInLocal.y,0.0f);
    //glTranslatef(0.0f,0.0f,0.0f);
    glRotatef(angleMouse,0.0f,0.0f,1.0f);
    
    


    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,1.0f);

    // Draw a thin box (rectangle)
    glVertex2f(0.0f, 0.0f);            // Top-left corner
    glVertex2f(width, 0.0f);           // Top-right corner
    glVertex2f(width, height);         // Bottom-right corner
    glVertex2f(0.0f, height);          // Bottom-left corner

    // glVertex2f(0.0f, -centerInLocal.y);            // Top-left corner
    // glVertex2f(width, -centerInLocal.y);           // Top-right corner
    // glVertex2f(width, height - centerInLocal.y);         // Bottom-right corner
    // glVertex2f(0.0f, height - centerInLocal.y);      
    // //std::cout << "Gun widht: " << width << " Heigh: " << height << std::endl;
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
