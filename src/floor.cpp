#include "Floor.h"


#include "SDWINDOW.h"

void Floor::init()
{


    
    // vertices.push_back(&position);
    // vertices.push_back(&end);


    // Create shared pointers for vertices
    std::shared_ptr<Vector2D> posPtr = std::make_shared<Vector2D>(position);
    std::shared_ptr<Vector2D> endPtr = std::make_shared<Vector2D>(end);

    vertices.push_back(posPtr);
    vertices.push_back(endPtr);
    
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

void Floor::OnCollision(float deltaTime, Transform *objectCollision, Vector2D normalCollision, float depth, Vector2D unmodifiedNormalCollision)
{

    Transform::OnCollision(deltaTime,objectCollision,normalCollision,depth,unmodifiedNormalCollision);
    debugNormal->RenderRay(position,Transform::normalVectorPlane,100.0f);
    

}

bool Floor::IsGround()
{
    return false;
}