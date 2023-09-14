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

    vertices.push_back(topRight);
    vertices.push_back(bottomRight);
    vertices.push_back(bottomLeft);
    vertices.push_back(topLeft);
    
    // vertices.push_back(topLeft);
    // vertices.push_back(bottomLeft);
    // vertices.push_back(bottomRight);
    // vertices.push_back(topRight);

    Gizmos* points = Gizmos::StartGizmos(0.45f, 0.9f, 0.2f);
    points->SetPointsDebug(vertices, 4.0f);
    computeNormalEdges();

}

void Box::computeNormalEdges()
{
            
    
    // for(int i=0; i<Transform::vertices.size();i++){
    //     Vector2D* a = vertices[i];
    //     Vector2D* b = vertices[(i+1)%vertices.size()];
    //     Vector2D n = Vector2D::NormalSuperfice(*a,*b);
    //     Gizmos *debugN = Gizmos::StartGizmos(0.5f,0.5f,0.5f);
    //     Vector2D halfN =  Vector2D::PositionBetween(*a,*b);      
    //     debugN->RenderRay(halfN ,n,50.0f);

    // }
    
    
    // for(int j=0;j<Transform::vertices.size();j++){
    //     Vector2D* a = vertices[j]; 
    //     Vector2D* b = vertices[(j+1)%vertices.size()];

    //     Vector2D n = Vector2D::NormalSuperfice(*a,*b);
        
    //     //Vector2D* nn = new Vector2D(n.x,n.y);
    //     //for placing
    //     Vector2D halfN =  Vector2D::PositionBetween(*a,*b);        
    //     // Vector2D offset = Vector2D(0.0f,-100.0f);
    //     // halfN = halfN + offset;
    //     //debug
        
    //     Gizmos *debugN = Gizmos::StartGizmos(0.5f,0.5f,0.5f);
    //     debugN->RenderRay(halfN ,n,100.0f);


    
    // for(int i =0; i<Transform::vertices.size();i++){
    //     Vector2D* v1 = vertices[i]; 
    //     float dot = Vector2D::Dot(n,*v1);
    //     Vector2D projectionVector = Vector2D::ScalarMultiplication(n,dot);
    //     Gizmos *debugP = Gizmos::StartGizmos(0.2f,1.0f,0.8f);
    //     debugP->RenderRay(*v1,Vector2D::Normalized(projectionVector),100.0f);
    // }
    // } 

}

void Box::update(float deltaTime)
{

    Transform::update(deltaTime);
    
   

}



void Box::draw(float deltaTime)
{
    glPushMatrix();

    glTranslatef(position.x,position.y,0.0f);
    
    glBegin(GL_QUADS);
    
    glColor3f(1.0f, 0.8f, 0.5f);
    
    //reference
    // glVertex3f(x1, y1, z1);  // Top-left
    // glVertex3f(x2, y2, z2);  // Top-right
    // glVertex3f(x3, y3, z3);  // Bottom-right
    // glVertex3f(x4, y4, z4);  // Bottom-left
    
    
    glVertex2f(0.0f,0.0f);
    glVertex2f(100.0f,0.0f);
    glVertex2f(100.0f ,100.0f);
    glVertex2f(0.0f,100.0f);
    
    glEnd();


    glPopMatrix();
    

}

void Box::OnCollision(float deltaTime, Transform *objectCollision, Vector2D normalCollision, float depth,Vector2D unmodifiedNormalCollision)
{

    
    Transform::OnCollision(deltaTime,objectCollision,normalCollision,depth,unmodifiedNormalCollision);
    
    if(objectCollision->isBullet)return;
    if(!isMove) return;
    Vector2D newMotion= Vector2D::ScalarMultiplication(normalCollision,depth);
    
    
    position.x += newMotion.x * deltaTime; 
    position.y += newMotion.y * deltaTime;

    for(auto& b : vertices){
        b->x += newMotion.x * deltaTime;
        b->y += newMotion.y * deltaTime;
        
    }



}
