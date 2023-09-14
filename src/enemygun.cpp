#include "EnemyGun.h"
#include "SDWINDOW.h"
#include "RadToDegree.h"


EnemyGun::~EnemyGun()
{
}



void EnemyGun::update(float deltaTime)
{

    Transform::update(deltaTime);
  


}

void EnemyGun::draw(float deltaTime)
{

    glPushMatrix();

    glTranslatef(50.0f,28.0f,0.0f);
    
    glRotatef(anglePlayer,0.0f,0.0f,1.0f);
    
    glBegin(GL_QUADS);
    
    glColor3f(1.0f, 0.84f, 0.0f);
    
    // Draw a thin box (rectangle)
    glVertex2f(0.0f, 0.0f);            // Top-left corner
    glVertex2f(width, 0.0f);           // Top-right corner
    glVertex2f(width, height);         // Bottom-right corner
    glVertex2f(0.0f, height);          // Bottom-left corner

   
    glEnd();

  
    glPopMatrix();


}

void EnemyGun::rotateGun(Vector2D dir)
{

    debugGizmos->RenderRay(position,dir,40.0f);
    //update the angle player rotation
    float angle = std::atan2(dir.y,dir.x);
    anglePlayer = RadToDegree::convert(angle);
    Rotation = anglePlayer;

    


}
