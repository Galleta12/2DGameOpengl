#include "Bullet.h"

//need deltatiem for the initial launch
#include "Clocker.h"

#pragma once




void Bullet::launchBall()
{
    //velocity = dir; 
    motion.x = dir.x * speed;
    motion.y = dir.y * speed;
    

}



void Bullet::update(float deltaTime)
{
    
    //add the end we want to get the transform updates
    //Transform::update(deltaTime);

    //std::cout<< "Dir update" << dir << std::endl;
   //I will compute each of this on different component there is a problem on my vectors

    
    
    position.x +=  motion.x * deltaTime;
    position.y +=  motion.y * deltaTime;
    //we always want to reder the velocity
    debugVelocity->RenderRay(position,dir, 200.0f); 
}




void Bullet::draw(float deltaTime)
{

    glPushMatrix();
    
    glTranslatef(position.x, position.y, 0.0f);

    glLineWidth(2.0f); // Set the line width

    glBegin(GL_LINES);
    glColor3f(r,g,b); // Red color

    const int numSegments = 100; // Number of line segments to approximate the circle
    const float angleIncrement = 2.0f * RadToDegree::PI / numSegments;
    float angle = 0.0f;

    while(angle < 2.0f * RadToDegree::PI)
    {
        // Calculate the coordinates of the endpoints of each line segment
        float x1 = radius * std::cos(angle);
        float y1 = radius * std::sin(angle);
        float x2 = radius * std::cos(angle + angleIncrement);
        float y2 = radius * std::sin(angle + angleIncrement);

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);

        angle += angleIncrement;
    }

    glEnd();

    glPopMatrix();


}

float Bullet::randomFloat()
{
    // Function to generate a random float between 0 and 1
    
        return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    
    

}
