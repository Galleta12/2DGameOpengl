#pragma once

#include "Vector2D.h"
#include "cmath"

class Transform{

    public:
        
        Vector2D position;
        Vector2D velocity;
        
        Vector2D right;
        Vector2D up;
        
        float Rotation = 0.0f;
        
        
        Transform(float x, float y){
            position.x = x;
            position.y = y;
        }
       
        // Transform(){
        //    position.Zero();
        //    velocity.Zero();
        // }
        
        ~Transform(){}

        Vector2D getRightVec(){

            // Get the up vector
            Vector2D upVector = getUpVec();

            // Calculate the right vector by rotating the up vector 90 degrees counterclockwise
            Vector2D rightVector(-upVector.y, upVector.x);
            right = rightVector;
            
            return right;
        }
        Vector2D getUpVec(){
            
            float angleRadians = Rotation * (3.14159265359f / 180.0f); // Convert degrees to radians
            float upX = -std::sin(angleRadians); // Negative sin for upwards direction
            float upY = std::cos(angleRadians);  // Cosine for upwards direction
            up.x = upX;
            up.y = upY;

            return up;

        }

        
        virtual void init(){}
        virtual void update(float deltaTime){}
        virtual void draw(float deltaTime){}

        //virtual ~Transform(){}
        

    private:



};