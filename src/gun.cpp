#include "Gun.h"


#include "SDWINDOW.h"
#include "RadToDegree.h"
#include <iostream>

#include <vector>
#include <chrono>

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
    float angle = std::atan2(dir.y, dir.x);
    
    angleMouse = RadToDegree::convert(angle);
    
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
