#include "Box.h"
#include "SDWINDOW.h"

#include "Gizmos.h"

Box::~Box()
{
}



void Box::init()
{

    
    // Define the vertices in the order expected by your rendering code
    
    
    Vector2D* topLeft = new Vector2D(position.x, position.y + 100.0f);
    Vector2D* topRight = new Vector2D(position.x + 100.0f, position.y + 100.0f);
    Vector2D* bottomRight = new Vector2D(position.x + 100.0f, position.y);
    Vector2D* bottomLeft = new Vector2D(position.x, position.y);

    vertices.push_back(topLeft);
    vertices.push_back(bottomLeft);
    vertices.push_back(bottomRight);
    vertices.push_back(topRight);

    Gizmos* points = Gizmos::StartGizmos(0.45f, 0.9f, 0.2f);
    points->SetPointsDebug(vertices, 4.0f);
    computeNormalEdges();

}

void Box::computeNormalEdges()
{
    for(int i =0; i<Transform::vertices.size();i++){
        Vector2D* a = vertices[i]; 
        Vector2D* b = vertices[(i+1)%vertices.size()];

        Vector2D n = Vector2D::NormalSuperfice(*a,*b);
        n.x *= -1;
        n.y *= -1;
     
        //Vector2D* nn = new Vector2D(n.x,n.y);
        //for placing
        Vector2D halfN = Vector2D::PositionBetween(*a,*b);        
        //debug
        
        Gizmos *debugN = Gizmos::StartGizmos(0.5f,0.5f,0.5f);
        debugN->RenderRay(halfN ,n,100.0f);
        
        float dot = Vector2D::Dot(*vertices[i],n);

        Vector2D projectionVector = Vector2D::ScalarMultiplication(n,dot);
        
        Gizmos *debugP = Gizmos::StartGizmos(0.2f,1.0f,0.8f);
        debugP->RenderRay( *vertices[i],projectionVector.Normalize(),100.0f);

    }

}

void Box::update(float deltaTime)
{

    Transform::update(deltaTime);
    
   

}



void Box::draw(float deltaTime)
{
    glPushMatrix();

    glBegin(GL_QUADS);
    
    glColor3f(1.0f, 0.8f, 0.5f);
    
    glVertex2f(position.x,position.y);
    glVertex2f(position.x + 100,position.y);
    glVertex2f(position.x +100 ,position.y +100);
    glVertex2f(position.x,position.y + 100);
    
    glEnd();


    glPopMatrix();
    

}
