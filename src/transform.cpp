#include "Transform.h"

Transform::~Transform()
{
   
    // Delete the vertices and normalEdgesList using smart pointers
        for (auto& vertex : vertices) {
            // No need to delete, smart pointers handle it
        }
        vertices.clear();

        for (auto& normal : normalEdgesList) {
            // No need to delete, smart pointers handle it
        }
        normalEdgesList.clear();
    }



void Transform::OnCollision(float deltaTime, Transform *objectCollision, Vector2D normalCollision, float depth, Vector2D unmodifiedNormalCollision)
{    

    //normalDebug->RenderRay(objectCollision->position,normalCollision,100.0f);

}

//get the right vector of the transform
Vector2D  Transform::getRightVec(){
        // Get the up vector
        Vector2D upVector = getUpVec();
        // Calculate the right vector by rotating the up vector 90 degrees counterclockwise
        Vector2D rightVector(-upVector.y, upVector.x);
        right = rightVector;
        
        return right * -1;
}


Vector2D Transform::getUpVec(){
       float angleRadians = Rotation * (3.14159265359f / 180.0f); // Convert degrees to radians
        float upX = -std::sin(angleRadians); // Negative sin for upwards direction
        float upY = std::cos(angleRadians);  // Cosine for upwards direction
        up.x = upX;
        up.y = upY;

        return up;
}

void Transform::update(float deltaTime)
{
        getUpVec();
        getRightVec();
            
        if(basisVector){
            DrawUpGizmosTransform();
            DrawRightGizmos();
        }

}


void  Transform::DrawUpGizmosTransform(){
     upGizmos->RenderRay(position,up.Normalize(),100.0f);
}

void Transform::DrawRightGizmos(){
    rightGizmos->RenderRay(position,right.Normalize(),100.0f);
}

void Transform::AddPhysics2D(){
    physics2D = std::make_unique<Physics2D>();
    //physics2D = new Physics2D();
}

Physics2D  *Transform::getPhysics2D(){
      //return physics2D;
    return physics2D.get(); 
}