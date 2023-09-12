#include "Physics2D.h"
#include "SDWINDOW.h"
#include <cmath>
#include <limits>


Physics2D::~Physics2D()
{

    raycastHitObjectList.clear();
    //delete raycastHitinfo;
}




void Physics2D::checkwindowcollision(Vector2D& position)
{
    // Get the player's current position
    Vector2D currentPosition = position;

    // Get the dimensions of the window
    float windowWidth = *SDWINDOW::WindowWidth; // Replace with your actual window width
    float windowHeight = *SDWINDOW::WindowHeight; // Replace with your actual window height

    // Define some padding to keep the player within the window bounds
    float padding = 20.0f; // Adjust as needed

    // Check if the player is going off the left edge of the window
    if (currentPosition.x - padding < 0.0f) {
        currentPosition.x = padding; // Set the player's position to the left edge with padding
    }

    // Check if the player is going off the right edge of the window
    if (currentPosition.x + padding > windowWidth) {
        currentPosition.x = windowWidth - padding; // Set the player's position to the right edge with padding
    }

    // Check if the player is going off the top edge of the window
    if (currentPosition.y - padding < 0.0f) {
        currentPosition.y = padding; // Set the player's position to the top edge with padding
    }

    // Check if the player is going off the bottom edge of the window
    if (currentPosition.y + padding > windowHeight) {
        currentPosition.y = windowHeight - padding; // Set the player's position to the bottom edge with padding
    }

    // Update the player's position to the adjusted position
    position = currentPosition;


}

// bool Physics2D::raycast(Transform* me,Vector2D start,Vector2D direction, float distance, bool draw, float deltaTime)
// {
    
//     //new vector set to direction
//     bool isCollision = false;
//     Vector2D ray;
//     float newDist = distance;
//     Vector2D newStart = start;
//     ray = newStart + (direction * distance);
//     //check collisions
    
//     // I have the following equations
//     // loop thorugh all the objects in the scene?
//     for(auto& t : SDWINDOW::transformList){
//         if(t != me){
//             //std::cout <<"I found u" << std::endl;
//             //find the colllision if there is collision
//             //the parametric and line intersection formula
//             // P(thit) = start + thit * direction * distance
//             //thit formula with the normal
//             // p hit between x and y. of the plane
//             //thit must not be negative than the deltatime

//                         // Line parameters
//             Vector2D P0 = t->position;
//             Vector2D D = Vector2D(*SDWINDOW::WindowWidth, 0.0f); // Assuming floor extends the entire window width

//             // Calculate the determinant
//             float determinant = direction.x * (-D.y) - (-D.x) * direction.y;

//             // Check if the ray and line are not parallel
//             if (fabs(determinant) > 0.0001f) {
//                 // Calculate 't' and 's' values
//                 float t = ((P0.x - start.x) * (-D.y) - (-D.x) * (P0.y - start.y)) / determinant;
//                 float s = (direction.x * (P0.y - start.y) - (P0.x - start.x) * direction.y) / determinant;

//                 // Check if both 't' and 's' are within valid ranges
//                 if (t >= 0.0f && t <= distance && s >= 0.0f && s <= 1.0f) {
//                     // Intersection found
//                     isCollision = true;
//                     break; // No need to check other floors
//                 }
//             }


//         }
//         else
//         {
//             //std::cout <<"I found u" << std::endl;

//         }

//     }



//     if(isCollision){
//         //isCollision = true;
//         //change color
//         debugDrawRaycast->changeColor(1.0f,0.0f,0.0f);

//     }

//     if(draw){
    
//         debugDrawRaycast->RenderRay(start,direction,newDist);
    
    
//     }


    
    
//     return isCollision;



// }


bool Physics2D::raycast(Transform* me,Vector2D start,Vector2D direction, float distance, bool draw, float deltaTime)
{
    return false;
}
Vector2D Physics2D::calculateNormalSuperfice(Vector2D pos, Vector2D end)
{
    return Vector2D::NormalSuperficeNoNormalized(pos,end);
}
bool Physics2D::checkThitBetweenDeltaTime(float thit, float deltaTime)
{
    if(0.0f < thit && thit < deltaTime){
        return true;

    }
    return false;
}
Vector2D Physics2D::calculateEndRay(Vector2D start, Vector2D dir, float dist)
{
    //calculate end of ray
    Vector2D end = Vector2D::Addition(start,(Vector2D::ScalarMultiplication(dir,dist)));
    //Vector2D end = start + (dir * dist);
    
    return end;
}
bool Physics2D::checkConditionsCollisionParametric(Vector2D hitPoint, Vector2D b1, Vector2D b2)
{
    
    //first check if we should check for collision on the x or y components
    float yDelta = std::abs(b1.y - b2.y); 
    float XDelta = std::abs(b1.x - b2.x); 
    //check only y
    if(yDelta > XDelta){

        if(hitPoint.y >= b1.y &&  hitPoint.y <= b2.y){
            return true;
        }
        else{
            return false;
        }
    
    }
    else{

        if(hitPoint.x >= b1.x && hitPoint.x <= b2.x){
            return true;
        }else{

            return false;
        }
    }

    
}
bool Physics2D::raycastParametric(const Transform *me, Vector2D direction, float distance, bool draw, float deltaTime)
{

    bool isCollision=false;
    Vector2D newDir = direction;
    //this becomes the newStart
    Vector2D newStart = calculateEndRay(me->position,direction,distance);
      if(draw){
       

        debugDrawRaycast->RenderLine(me->position,newStart);
    }

    for(auto& t : SDWINDOW::transformList){
        if(t != me){
         
            //first find the thit
            
            //check if it is a line and get the normal and the vertices
            //caculate the normal
            //thir formula
            //thit(ndot(B-A)/n dot c)
            
            
            //loop through the transform vertices
            //if it is a line
            if(t->lineFlag){
                
            //std::cout << "line" << std::endl;
                
                const std::vector<Vector2D*>& verticesList = t->vertices;
         
                
                for(int i=0; i < verticesList.size(); i++){
                    
                    Vector2D* b1 = verticesList[i]; 
                    Vector2D* b2 = verticesList[(i+1)%verticesList.size()]; 

                    Vector2D n = Vector2D::NormalSuperficeNoNormalized(*b1,*b2);
                    //B - A
                    Vector2D BA;
                    BA.x = b1->x - newStart.x;
                    BA.y = b1->y - newStart.y;
                     //thit(ndot(B-A)/n dot c)
                    float thit = (Vector2D::Dot(n,BA)/Vector2D::Dot(n,newDir));
                     
                    //first check if the thit is between the current fram
                    if(!checkThitBetweenDeltaTime(thit,deltaTime)){
                        break;
                    }
                    //formula p=A+(thit x c)
                    Vector2D pointHit;
                    Vector2D currentDir = newDir;
                    Vector2D thitC =  currentDir * thit;
                    Vector2D currentPos = newStart;
                    pointHit = currentPos + thitC;
                    //check conditions
                    
                    if(checkConditionsCollisionParametric(newStart,*b1,*b2)){
                        //std::cout << "Yes collision" << std::endl;
                        //debugDrawRaycast->changeColor(0.0f,0.0f,0.0f);
                        //save the hit line and the distance
                        //float distance = Vector2D:
                        raycastHitObjectList[t] = Vector2D::DistanceVec(newStart,t->position);

                        continue;
                    }
                    else{                       
                        
                        continue;

                    }
                                        

                }
            }
            
                     
         }
    }



   if(!raycastHitObjectList.empty()){
        isCollision = true;       
        getFirstHitRayCast();
        return isCollision;
    }
  
  

    return isCollision;
}

void Physics2D::getFirstHitRayCast()
{

    
    float minDist = std::numeric_limits<float>::infinity();;
    Transform* hitTransform=nullptr;
    for(auto& pair : raycastHitObjectList){
       float newdist = pair.second;

       if(newdist < minDist){
            minDist = newdist;
            hitTransform = pair.first;
       }
       
    }
    //we have the first hit now. Hence
    //save importan information
    raycastHitinfo->hitnormal = hitTransform->normalVectorPlane;
    
    //clear everything
    raycastHitObjectList.clear();
}
bool Physics2D::checkOnGround()
{
    return false;
}

void Physics2D::gravityForce(float yDir)
{
}

