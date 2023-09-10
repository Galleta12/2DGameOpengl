#pragma once

#include "Vector2D.h"
#include "Gizmos.h"
#include "cmath"

class Transform{

    public:
        
        
        
        Vector2D localPosToWorld;
        
        Vector2D position;
        Vector2D velocity;
        
        Vector2D right;
        Vector2D up;
        
        float Rotation = 0.0f;
        
        bool isLocalSpace=false;
        
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
            
            return right * -1;
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
        virtual void update(float deltaTime){
            getUpVec();
            getRightVec();
            DrawUpGizmosTransform();
            DrawRightGizmos();
        }
        virtual void draw(float deltaTime){}
        

        void convertLocalToWorld(Vector2D parentPosition){
            //localPosToWorld = parentPosition + position;                                     
            localPosToWorld = parentPosition;                                     

        }

        void DrawUpGizmosTransform(){
            //std::cout<<"DrawGizmos" << std::endl;
            if(!isLocalSpace){

                upGizmos->RenderRay(position,up.Normalize(),100.0f);
            }
            else{
                upGizmos->RenderRay(localPosToWorld,up.Normalize(),100.0f);

            }
        }
        void DrawRightGizmos(){
            if(!isLocalSpace){

                rightGizmos->RenderRay(position,right.Normalize(),100.0f);
            }
            else
            {
                rightGizmos->RenderRay(localPosToWorld,right.Normalize(),100.0f);

            }
        }
        //virtual ~Transform(){}
        

    private:
        //purple
        Gizmos *upGizmos = Gizmos::StartGizmos(0.5f, 0.5f, 0.0f);
        // Set the color to orange (RGB: 1.0, 0.5, 0.0)
        Gizmos *rightGizmos = Gizmos::StartGizmos(1.0f, 0.5f, 0.0f);


};