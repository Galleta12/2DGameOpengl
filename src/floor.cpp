#include "Floor.h"


#include "SDWINDOW.h"




void Floor::update(float deltaTime)
{
}

void Floor::draw(float deltaTime)
{
    glPushMatrix();

    //glTranslatef()    
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.2f); // Set color to green
    //start point
    glVertex2f(position.x,position.y);
    glVertex2f(position.x + (*SDWINDOW::WindowWidth - 2.0f) ,position.y );
    //end point


    glEnd();

    glPopMatrix();


}

bool Floor::IsGround()
{
    return false;
}