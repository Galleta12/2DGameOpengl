#include "Platforms.h"

#include "SDWINDOW.h"

#include "Gizmos.h"


void Platforms::init()
{
     //
    vertices.push_back(&end);
    vertices.push_back(&position);
    Gizmos *points = Gizmos::StartGizmos(0.4f,1.0f,1.0f);
    points->SetPointsDebug(vertices, 15.0f);

}

void Platforms::draw(float deltaTime)
{

    glPushMatrix();

    glLineWidth(7.0f);
    
    glBegin(GL_LINES);
    
    glColor3f(1.0f, 0.3f, 1.0f); 


    glVertex2f(position.x,position.y);
    glVertex2f(end.x,end.y);


    glEnd();

    glPopMatrix();


}

void Platforms::OnCollision(float deltaTime, Transform *objectCollision, Vector2D normalCollision, float depth, Vector2D unmodifiedNormalCollision)
{
    Transform::OnCollision(deltaTime,objectCollision,normalCollision,depth,unmodifiedNormalCollision);


    // if(objectCollision->isBullet){
    //     Vector2D newMotion= Vector2D::ScalarMultiplication(normalCollision,depth);
        
    //     objectCollision->position.x += newMotion.x;
    //     objectCollision->position.y += newMotion.y;
    //     //objectCollision->position 
    //     //objectCollision->vertices
        
    //     for(auto& b : objectCollision->vertices){
    //         b->x += newMotion.x * deltaTime;
    //         b->y += newMotion.y * deltaTime;
    //     }
    
    
    // }


}

void Platforms::update(float deltaTime)
{
    // //calculate normal
    // Vector2D positionR;
    // //B1 position
    // Vector2D copyPos = position;      
    // Vector2D copyEnd = end;
    // positionR = copyEnd - copyPos;
    // //flip
    // Vector2D norm(-positionR.y,positionR.x);
    // normalVec = norm;
    Transform::normalVectorPlane = Vector2D::NormalSuperfice(position,end);
    
    
    //debugNormal->RenderRay(position,Transform::normalVectorPlane,100.0f);

    



}


