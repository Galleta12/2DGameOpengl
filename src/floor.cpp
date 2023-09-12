#include "Floor.h"


#include "SDWINDOW.h"

void Floor::init()
{

    vertices.push_back(&position);
    vertices.push_back(&end);
    Gizmos *points = Gizmos::StartGizmos(0.4f,1.0f,1.0f);
    points->SetPointsDebug(vertices, 15.0f);


}

void Floor::update(float deltaTime)
{

      // normalVec = norm;
    Transform::normalVectorPlane = Vector2D::NormalSuperfice(position,end);
    
    
    debugNormal->RenderRay(position,Transform::normalVectorPlane,100.0f);



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
    glVertex2f(end.x,end.y);
    //end point


    glEnd();

    glPopMatrix();


}

bool Floor::IsGround()
{
    return false;
}