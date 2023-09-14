#include "Player.h"



#include "SDWINDOW.h"

#include <iostream>

#include <vector>
#include <chrono>
#include <algorithm> 


void Player::gunData(int newSpeed, int newPower)
{
    calculateCenter();
    gun = new Gun(playerPosX,playerPosY,newSpeed,newPower,centerTriangle);

    //print gun
    std::cout << *gun << std::endl;
}

Player::~Player()
{
    delete gun;
}


void Player::update(float deltaTime)
{
    
    
    Transform::update(deltaTime);

    
    //we dont want to do anything if player is death
    if(isDeath)return;
    
    
    
    if(isKeyDirx){

        //update the player motion
        motion.x = keydirX * speed;
        motion.x *= friction;
        //std::cout << "motion" << motion.x << std::endl;
    }
    else if(!isKeyDirx && motion.x != 0.0f){
        
        motion.x = std::max(motion.x, 0.0f);
        
        if(motion.x > 0.0f){
            motion.x *= 0.4f;
            
            //std::cout << "motion false" << motion.x << std::endl;
        }
     
    }


    position.x += motion.x * deltaTime;
    
    
    leftVertex.x += motion.x * deltaTime;
    rightVertex.x += motion.x * deltaTime;





    yMovements(deltaTime);
    
    
    gun->updatePosition(deltaTime,motion);

    gun->update(deltaTime);

    //set collision floor as false, again
    isCollisionFloor = false;
    
    

}
void Player::yMovements(float deltaTime)
{


    motion.y = keydirY * speed;
    motion.y *= friction;
    
    position.y += motion.y * deltaTime;
    
    
    leftVertex.y += motion.y * deltaTime;
    rightVertex.y += motion.y * deltaTime;
    


}

void Player::checkIsCollisionGround(float deltaTime){
    //define the ray below
    // Vector2D currenttUp = Transform::up;
    // currenttUp.y *= -1;
    //Transform::getPhysics2D()->raycast(this,position,currenttUp,100.0f,true,deltaTime);
    
     
}


void Player::draw(float deltaTime)
{

    glPushMatrix();
    
    //std::cout << "New position x" << position.x << std::endl;
    
    glTranslatef(position.x,position.y,0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    
   

    
    glVertex2f(0.0f, 0.0f); // Top vertex
    glVertex2f(-25.0f,-50.0f); // Bottom-left vertex
    glVertex2f(25.0f, -50.0f);  // Vertex 3
    // glVertex2f(playerPosX, playerPosY); // Top vertex
    // glVertex2f(playerPosX - 50.0f, playerPosY - 100.0f); // Bottom-left vertex
    // glVertex2f(playerPosX + 50.0f, playerPosY - 100.0f);  // Vertex 3

    //std::cout<<"Playerpox: " << playerPosX << std::endl;
   
    glEnd();


    //we want to calculate the current center
    calculateCenter();
    
    gun->draw(deltaTime);
    //std::cout << "Gun draw: " <<*gun << std::endl;
    glPopMatrix();
    //the bullets are independent from the player and gun pos
    //for(auto& b : gun->getVectorBullet())b->draw(deltaTime);

}

//populate the list of normal edges, we also want to draw then for visualization
//only for debuggin porpuses
void Player::computeNormalEdges()
{

        
    // for(int j=0;j<Transform::vertices.size();j++){
    //     Vector2D* a = vertices[j]; 
    //     Vector2D* b = vertices[(j+1)%vertices.size()];

    //     Vector2D n = Vector2D::NormalSuperfice(*a,*b);
        
    //     //Vector2D* nn = new Vector2D(n.x,n.y);
    //     //for placing
    //     Vector2D halfN =  Vector2D::PositionBetween(*a,*b);        
    //     Vector2D offset = Vector2D(0.0f,-100.0f);
    //     // halfN = halfN + offset;
    //     //debug
        
    //     Gizmos *debugN = Gizmos::StartGizmos(0.5f,0.5f,0.5f);
    //     debugN->RenderRay(halfN ,n,1000.0f);


    
    // for(int i =0; i<Transform::vertices.size();i++){
    //     Vector2D* v1 = vertices[i]; 
    //     float dot = Vector2D::Dot(n,*v1);
    //     Vector2D projectionVector = Vector2D::ScalarMultiplication(n,dot);
    //     Gizmos *debugP = Gizmos::StartGizmos(0.2f,1.0f,0.8f);
    //     debugP->RenderRay(*v1,Vector2D::Normalized(projectionVector),1000.0f);
    // }
    // }    
    



}

void Player::keyboard()
{
    if(SDWINDOW::event.type == SDL_KEYDOWN){
        switch (SDWINDOW::event.key.keysym.sym)
        {
        case SDLK_w:
            
            keydirY =  1.0f;    
            break;
        
        
        case SDLK_s:
            
           if(!isCollisionFloor){

            keydirY=  -1.0f;    
           }

            break;
        
        case SDLK_a:
            
            
            isKeyDirx = true;
            keydirX = -1.0f;
            
            break;
        
        case SDLK_d:
           
            isKeyDirx = true;
            keydirX = 1.0f;
            break;
        
        default:
            break;
        }
    }
    //when release the keyboard
    if(SDWINDOW::event.type == SDL_KEYUP){
        switch (SDWINDOW::event.key.keysym.sym)
        {
        case SDLK_w:
        case SDLK_s:
            keydirY =  0.0f;    
            
            break;        
        case SDLK_a:
        case SDLK_d:
            
            
            //we dont want to abruptely stop the movment hence we use this flag
            isKeyDirx = false;
            keydirX = 0.0f;
            break;
        
        default:
            break;
        }
    }

    //std::cout << "keydir: " <<keydirX << std::endl;

}


void Player::calculateCenter()
{
    
    //formula
    //
    // Vector2D top(playerPosX,playerPosY);
    // Vector2D leftButton (playerPosX-50.0f,playerPosY-100.0f);
    // Vector2D rightButton (playerPosX + 50.0f, playerPosY - 100.0f);

    
    Vector2D top(position.x,position.y);
    Vector2D leftButton (position.x-25.0f,position.y-50.0f);
    Vector2D rightButton (position.x + 25.0f, position.y - 50.0f);

    
    
    float centerX = (leftButton.x + top.x + rightButton.x) / 3.0f;
    float centerY = (leftButton.y + top.y + rightButton.y) / 3.0f;

    centerTriangle.x = centerX;
    //sdl on the y is different
    centerTriangle.y =  centerY;
    //print vector center
    //std::cout << "Center triangle: " <<centerTriangle << " For the cordinates on mouse on y " << *SDWINDOW::WindowHeight -centerTriangle.y << std::endl;

}


//set up the vertices of the player.
void Player::init()
{

    
    //get all points and put it on the vertices
    //top corner

    //  // Calculate positions of other two vertices
    // Vector2D leftVertex(position.x - 25.0f, position.y - 50.0f);
    // Vector2D rightVertex(position.x + 25.0f, position.y - 50.0f);
    
    
    leftVertex.x = position.x - 25.0f;
    leftVertex.y = position.y - 50.0f;
    rightVertex.x = position.x + 25.0f;
    rightVertex.y = position.y - 50.0f;
    
    vertices.push_back(&position);
    vertices.push_back(&rightVertex);
    vertices.push_back(&leftVertex);


    
    //refernce
    // glVertex2f(-25.0f,-50.0f); // Bottom-left vertex
    // glVertex2f(25.0f, -50.0f);  // Vertex 3
    



    
    
    //create a dubug gizmos instance
    Gizmos *points = Gizmos::StartGizmos(1.0f,0.0f,0.0f);
    points->SetPointsDebug(vertices,5.0f);

    computeNormalEdges();

}

void Player::OnCollision(float deltaTime,Transform* objectCollision,Vector2D normalCollision, float depth)
{

    
    
    
    
    //std::cout << "Collision Player" << std::endl;
    //resolve collision
    Vector2D newMotion= Vector2D::ScalarMultiplication(normalCollision,depth);
    
    if(objectCollision->isBullet){
        //set flag as death
        isDeath = true;

        //change state of game
        SDWINDOW::gameState = SDWINDOW::GameState::LOSS;


        return;
    }
    
    if(objectCollision->isFloor){
        newMotion.y = 0.0f;
        keydirY =  0.0f;
        motion.y = 0.0f;
        isCollisionFloor = true;       
    }
    
    
    position.x += newMotion.x * deltaTime; 
    leftVertex.x += newMotion.x * deltaTime;
    rightVertex.x += newMotion.x * deltaTime;

    position.y += newMotion.y * deltaTime; 
    leftVertex.y += newMotion.y * deltaTime;
    rightVertex.y += newMotion.y * deltaTime;


}

void Player::resetPosition(float x, float y)
{
    
    
    position.x = x;
    position.y = y;
    
    //reset everything
    leftVertex.x = position.x - 25.0f;
    leftVertex.y = position.y - 50.0f;
    rightVertex.x = position.x + 25.0f;
    rightVertex.y = position.y - 50.0f;
    //set it back a false after changing position
    isDeath = false;
  


}
