#include "Physics2D.h"
#include "SDWINDOW.h"
#include <cmath>



Physics2D::~Physics2D()
{

    raycastHitObjectList.clear();
    //I want to delete my instances
    
    for(auto& a : collisionInfoList){
        delete a->collisionObject;
    
    }   
    
    collisionInfoList.clear();
        
    Gizmos::instances.erase(std::remove(Gizmos::instances.begin(),Gizmos::instances.end(), debugDrawRaycast), Gizmos::instances.end());


     
   
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
            if(t->vertices.size() != 0){
                
            //std::cout << "line" << std::endl;
                
                const std::vector<Vector2D*>& verticesList = t->vertices;
         
                
                for(int i=0; i < verticesList.size(); i++){
                    
                

                    Vector2D* b1 = verticesList[i]; 
                    Vector2D* b2 = verticesList[(i+1)%verticesList.size()]; 

                    Vector2D n = Vector2D::NormalSuperfice(*b1,*b2);
                   //B - A
                    Vector2D BA;
                    BA.x = b1->x - newStart.x;
                    BA.y = b1->y - newStart.y;
                     //thit(ndot(B-A)/n dot c)
                    float thit = (Vector2D::Dot(n,BA)/Vector2D::Dot(n,newDir));
                     
                    //first check if the thit is between the current fram
                    if(!checkThitBetweenDeltaTime(thit,deltaTime)){
                        //break;
                        continue;
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
                        debugDrawRaycast->changeColor(0.0f,0.0f,0.0f);
                        //save the hit line and the distance
                        //float distance = Vector2D:
                        std::unique_ptr<RayCastCollisionInfo> collisionInfo = std::make_unique<RayCastCollisionInfo>();
                        collisionInfo->distance = Vector2D::DistanceVec(newStart,t->position);
                        collisionInfo->hitnormal = n;
                        
                        raycastHitObjectList[t] = std::move(collisionInfo);

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
       float newdist = pair.second->distance;

       if(newdist < minDist){
            minDist = newdist;
            hitTransform = pair.first;
       }
       
    }
    //we have the first hit now. Hence
    
    //save importan information
    raycastHitinfo =   std::move(raycastHitObjectList[hitTransform]);
    
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

bool Physics2D::satCollisionAlg(Transform *me, bool draw)
{

    //get a list of my own vertices
    //const std::vector<Vector2D*>& meVerticesList = me->vertices;
    for(auto& t : SDWINDOW::transformList){

        //check my vertices agains other vertices
        //inside this loop I dont want to check me.
        if(t==me)continue;
        
        //address of our shape
        Transform *poly1 = me;
        Transform *poly2 = t;

        if(poly1->vertices.size() ==0 || poly2->vertices.size() ==0)continue;

        //test first collision between two
        for(int shape = 0; shape < 2; shape++)
        {
            if(shape==1){
                poly1 = t;
                poly2 = me;
            }
            const std::vector<Vector2D*>& verticesList = poly1->vertices;
            const std::vector<Vector2D*>& verticesList2 = poly2->vertices;
            for(int i=0; i < verticesList.size(); i++){
                //normal axis
                Vector2D* b1 = verticesList[i]; 
                Vector2D* b2 = verticesList[(i+1)%verticesList.size()]; 
                //normal
                Vector2D axisProj = Vector2D::NormalSuperfice(*b1,*b2);

                //project all of the points of the first polygon into the axis
                //min and max of the projection line
                float minP1 = INFINITY, maxP1 = -INFINITY;
                //iterate through all the points on the first polygon    
                for(int p= 0; p < verticesList.size(); p++){
                    //dot product of the point and axis of porjection
                    float dot = Vector2D::Dot(*verticesList[p],axisProj);
                    minP1 = std::min(minP1,dot);    
                    maxP1 = std::min(maxP1,dot);    
                
                }
                //for next shape            
                float minP2 = INFINITY, maxP2 = -INFINITY;
                //iterate through all the points on the first polygon    
                for(int p= 0; p < verticesList2.size(); p++){
                    //dot product of the point and axis of porjection
                    float dot = Vector2D::Dot(*verticesList2[p],axisProj);
                    minP2 = std::min(minP2,dot);    
                    maxP2 = std::min(maxP2,dot);    
                
                }

                if(!(maxP2 >= minP1 || maxP1 >=minP2)){
                    //return false;
                    std::cout << "sos " << std::endl;
                }else{
                    std::cout << "yes " << std::endl;
                }
            
            }


        }
        
    }

    return true;
}

bool Physics2D::satColliderChecker(const Transform* p1, const Transform* p2, float& depth, Vector2D& normalCollision)
{

    depth = std::numeric_limits<float>::infinity();
    //normalCollision.Zero();
    

    const std::vector<Vector2D*>& verticesListA = p1->vertices;
    const std::vector<Vector2D*>& verticesListB = p2->vertices;

    const Transform* polygon1 = p1;
    const Transform* polygon2 = p2;
    for(int number=0; number < 2; number++){

        if(number == 1){
            std::swap(polygon1, polygon2); 
        }
        
        const std::vector<Vector2D*>& verticesList = polygon1->vertices;
        for(int i=0; i < verticesList.size(); i ++){
            //get the normals
            Vector2D *pointA = verticesList[i];
            Vector2D *pointB = verticesList[(i+1) % verticesList.size()];

            Vector2D axis = Vector2D::NormalSuperfice(*pointA,*pointB);
		    
            float minA = std::numeric_limits<float>::infinity();
            float maxA = -std::numeric_limits<float>::infinity();
		    
            float minB = std::numeric_limits<float>::infinity();
		    float maxB = -std::numeric_limits<float>::infinity();
            //project each the axis on the vertex of each polygon
            Physics2D::ProjecAxis(polygon1,axis,minA,maxA);
            Physics2D::ProjecAxis(polygon2,axis,minB,maxB);

            //there is a gap therefore there is separation
            if(minA >= maxB || minB >=maxA){
                return false;
            }
            //there is overlap
            //when there is no seperation both max are greater than the minimun 
            //compute the deltas and use the small value to get the depth
            float axisDepth = std::min(maxB - minA, maxA - minB);
            
            if(axisDepth < depth){
                depth = axisDepth;
                normalCollision = axis;
            }
            
        }
    
    }

    
    depth /= normalCollision.Magnitude();
    //maybe divide depth with the lenght of the n

    // Vector2D centerA = Physics2D::FindCenterMean(verticesListA);
    // Vector2D centerB = Physics2D::FindCenterMean(verticesListB);

    // Vector2D direction = Vector2D::Substraction(centerB,centerA);
    // //opposite invert normal
    // if(Vector2D::Dot(direction,normalCollision) < 0.0f){
    //     // normalCollision.x  *= -1; 
    //     // normalCollision.y  *= -1;
    //     normalCollision = Vector2D::InvertVector(normalCollision); 
    // }


    return true;




}


void Physics2D::ProjecAxis(const Transform* currentPolygon, Vector2D axis, float &min, float &max)
{
    const std::vector<Vector2D*>& verticesList = currentPolygon->vertices;
    for(int i=0; i < verticesList.size(); i++){
        Vector2D *vertex = verticesList[i];
        float proj = Vector2D::Dot(*vertex,axis);
        if(proj < min){min=proj;}
        if(proj > max){max=proj;}
    }

}

Vector2D Physics2D::FindCenterMean(const std::vector<Vector2D*> vertices)
{
    float sumX = 0.0f;
    float sumY = 0.0f;
    for(int i=0; i < vertices.size();i++){
        Vector2D *vec = vertices[i];
        sumX+= vec->x;
        sumY+= vec->y;
    }
    return Vector2D( sumX/static_cast<float>(vertices.size()), sumY/static_cast<float>(vertices.size()));     

}
