#include "Platforms.h"

#include "SDWINDOW.h"

#include "Gizmos.h"


void Platforms::init()
{
    //
    vertices.push_back(&position);
    vertices.push_back(&end);
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
    
    
    debugNormal->RenderRay(position,Transform::normalVectorPlane,100.0f);

}


