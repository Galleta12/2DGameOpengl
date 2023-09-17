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
       
    updateXmovements(deltaTime);
    
   

    updateYmovements(deltaTime);
    

    gun->updatePosition(deltaTime,motion);

    gun->update(deltaTime);


}


void Player::checkIsCollisionGround(float deltaTime){
    //define the ray below
    // Vector2D currenttUp = Transform::up;
    // currenttUp.y *= -1;
    // bool hit = Transform::getPhysics2D()->raycastParametric(this,currenttUp,100.0f,true,deltaTime);
    // if(hit){
    //     Vector2D normal = Transform::getPhysics2D()->raycastHitinfo->hitnormal.Normalize();
        
    // }
     
}

void Player::updateXmovements(float deltaTime)
{

     
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

}

void Player::updateYmovements(float deltaTime)
{
        
        


        // if(!isCollisionFloor){

        //     //apply gravity when is in air
        //     motion.y -= 0.5f;
        //     //motion.y *= 0.5;
            
        // }else if(isCollisionFloor){
        //     motion.y = 0.0f;
        // }
        
        
        if(isJumping){
            //motion.y -= 0.2f;
            
            jumpHanlder(deltaTime);

            motion.y *= 0.5;
        }
        else{
            motion.y = keydirY * speed;
        }
        
        
        position.y += motion.y * deltaTime;
        leftVertex.y += motion.y * deltaTime;
        rightVertex.y += motion.y * deltaTime;
            
}

void Player::jumpHanlder(float deltaTime)
{
    
    motion.y += jumpForce;


}



void Player::draw(float deltaTime)
{

    glPushMatrix();
    
    //std::cout << "New position x" << position.x << std::endl;
    
    glTranslatef(position.x,position.y,0.0f);

    glRotatef(Transform::Rotation,0.0f,0.0f,1.0f);
    
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
            
           //if(!isCollisionFloor){

            keydirY=  -1.0f;    
           //}

            break;
        
        case SDLK_a:
            
            
            isKeyDirx = true;
            keydirX = -1.0f;
            
            break;
        
        case SDLK_d:
           
            isKeyDirx = true;
            keydirX = 1.0f;
            break;
        
        case SDLK_SPACE:
            
            

                isCollisionFloor = false;
                isJumping = true;
                jumpForce = 6.0f;


                
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
        case SDLK_SPACE:
            
            isJumping = false;

            break;
        
        default:
            break;
        }
    }


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
    
    
    
    std::shared_ptr<Vector2D> posPtr = std::make_shared<Vector2D>(position);
    std::shared_ptr<Vector2D> rightPtr = std::make_shared<Vector2D>(rightVertex);
    std::shared_ptr<Vector2D> leftPtr = std::make_shared<Vector2D>(leftVertex);

    
    
    
    
    vertices.push_back(posPtr);
    vertices.push_back(rightPtr);
    vertices.push_back(leftPtr);


    
    //refernce
    // glVertex2f(-25.0f,-50.0f); // Bottom-left vertex
    // glVertex2f(25.0f, -50.0f);  // Vertex 3
    



    
    
    //create a dubug gizmos instance
    Gizmos *points = Gizmos::StartGizmos(1.0f,0.0f,0.0f);
    points->SetPointsDebug(vertices,5.0f);

    computeNormalEdges();

}

void Player::OnCollision(float deltaTime,Transform* objectCollision,Vector2D normalCollision, float depth, Vector2D unmodifiedNormalCollision)
{
    
    Transform::OnCollision(deltaTime,objectCollision,normalCollision,depth,unmodifiedNormalCollision);
    
    normalDebug->RenderRay(objectCollision->position,normalCollision,100.0f);
   
    //std::cout << "Collision Player" << std::endl;
    //resolve collision
    Vector2D newMotion= Vector2D::ScalarMultiplication(normalCollision,depth);
    
   
    
    
    
    if(objectCollision->isBullet){
        // //set flag as death
        // isDeath = true;
        // //change state of game
        // SDWINDOW::gameState = SDWINDOW::GameState::LOSS;
        return;
    }
    
    
    //projection only on lines
    if(objectCollision->lineFlag){

        ProjectionAlongPlane(deltaTime,normalCollision,objectCollision, newMotion);
       
        return;
    }
     if(objectCollision->isFloor == true){
        
       isCollisionFloor = true;       

    }
        
        
    position.x += newMotion.x * deltaTime; 
    leftVertex.x += newMotion.x * deltaTime;
    rightVertex.x += newMotion.x * deltaTime;

    position.y += newMotion.y * deltaTime; 
    leftVertex.y += newMotion.y * deltaTime;
    rightVertex.y += newMotion.y * deltaTime;

}

void Player::ProjectionAlongPlane(float deltaTime, Vector2D normal, const Transform* objectedCollided, Vector2D newMotion)
{
    //first get the orthographic of the normal
    Vector2D orthographic;
    orthographic.x = -normal.y;
    orthographic.y = normal.x;
    //calculate to see if they are parallel to the motion if they are not we want to flip it
    //we flip if they are not pointing in the same direction
    if(Vector2D::Dot(orthographic,motion) < 0.0f){
        orthographic = Vector2D::InvertVector(orthographic);
    }
    //we dont want to do anything if the player up vector is not pointing the same dir of the normal
    //Vector up similar to Vecto3D.up in unity a unit lenght vector pointing always upwards
    Vector2D up(0.0f, 1.0f);
    
    float angle = AngleWithPlane(up,normal);
    
    
    
    //to the normal collision
    if(Vector2D::Dot(Transform::up,normal) < 0.0f || angle == 90.0f || angle == 0.0f){
        //just collide and apply gravity.    
        //handle movements
        position.x += newMotion.x * deltaTime; 
        leftVertex.x += newMotion.x * deltaTime;
        rightVertex.x += newMotion.x * deltaTime;

        position.y += newMotion.y * deltaTime; 
        leftVertex.y += newMotion.y * deltaTime;
        rightVertex.y += newMotion.y * deltaTime;
        return;
    }
    
    //we can start projection the vector, we can just project, new motion and flip it 
    //only if is facing another direction
    //std::cout << "currnet angle" << angle << std::endl;
    //draw to see if working
    ProjectVectorNormalMotion(deltaTime,orthographic,normal,objectedCollided,newMotion);

}





void Player::ProjectVectorNormalMotion(float deltaTime,Vector2D orthographic ,Vector2D normal, const Transform *objectedCollided, Vector2D newMotion)
{
    //project the newmotion into the plane
    //the plane is orthographic
    //project only the x dir
    //the projected vector is not normalized
    
    // orthographic = Vector2D::Normalized(orthographic);
    
    // Vector2D projected = Vector2D::VectorProjection(motion,orthographic);
    // //normalize it
    // projected = Vector2D::Normalized(projected);
    
    
    Vector2D projected = Vector2D::VectorProjection(motion,orthographic);
    //projected = Vector2D::Normalized(projected);
    if(Vector2D::Dot(Vector2D::Normalized(projected), orthographic) < 0.0f ){
        projected = Vector2D::InvertVector(projected);
    }
    
    Vector2D newProjectedMotion;
    newProjectedMotion.x = projected.x + newMotion.x;
    newProjectedMotion.y = projected.y + newMotion.y;

    //lets rotate
    float angle = std::atan2(projected.y, projected.x);
    //float angleDeg = RadToDegree::convert(angle);

    // float motionDot = Vector2D::Dot(motion, normal);
    // Vector2D motionProjection = Vector2D::ScalarMultiplication(normal, motionDot);
    // Vector2D newProjectedMotion = Vector2D::Substraction(motion,motionProjection) ;
    

    //std::cout<< "project" << projected << std::endl;
    //motion = newProjectedMotion;
    
    
    debuggerLine->RenderRay(objectedCollided->position,orthographic,300.0f);
    
    debuggerMotion->RenderRay(position,projected,300.0f);
    

    position.x += newProjectedMotion.x * deltaTime; 
    position.y += newProjectedMotion.y * deltaTime; 
    
    
    leftVertex.x += newProjectedMotion.x * deltaTime ;
    leftVertex.y += newProjectedMotion.y * deltaTime;
    rightVertex.x += newProjectedMotion.x * deltaTime;
    rightVertex.y += newProjectedMotion.y * deltaTime;

  

}

bool Player::checkIfFloorCollision(float deltaTime, Vector2D normal, const Transform *objectedCollided)

{
    Vector2D up(0.0f,1.0f);
    float angleWithPlane = AngleWithPlane(up,normal);

   return angleWithPlane == 0.0f;

}

float Player::AngleWithPlane(Vector2D ortho, Vector2D normal){

    float angle = Vector2D::Angle(ortho,normal);

    return angle;

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

void Player::handleRotations(float angle, float deltaTime)
{
    float angleDeg = RadToDegree::convert(angle);

    float leftXRot = (std::cos(angle) * -25.0f) - (std::sin(angle)* -50.0f); 
    float leftYRot = (std::sin(angle) * -25.0f) + (std::cos(angle)* -50.0f); 
    
    float rightXRot = (std::cos(angle) * 25.0f) - (std::sin(angle)* -50.0f); 
    float rightYRot = (std::sin(angle) * 25.0f) + (std::cos(angle)* -50.0f); 
    
    
    leftVertex.x = position.x + leftXRot;
    leftVertex.y = position.y + leftYRot;

    rightVertex.x = position.x + rightXRot;
    rightVertex.y = position.y + rightYRot;

    Rotation = angleDeg;


}

bool Player::checkIfRotationGood(Vector2D normal)
{

    return Vector2D::Angle(normal,Transform::up) == 0.0f;

}
