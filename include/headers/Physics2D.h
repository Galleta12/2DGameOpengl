#pragma once

#include "Vector2D.h"
#include "Gizmos.h"

class Transform;
class Physics2D{


    public:

        
        
        struct RayCastCollisionInfo
        {
            Vector2D hitposition;
            Vector2D hitnormal;

            // RayCastCollisionInfo(Vector2D  hitposition,Vector2D  hitnormal){
            //     hitposition = hitposition;
            //     hitnormal = hitnormal;
            // }

        };
        
        
        
        Physics2D(){};
        ~Physics2D();

        RayCastCollisionInfo *raycastHitinfo;

        //checkwindowcollision
        void checkwindowcollision(Vector2D& currentPosition);
        //check raycast
        bool raycast(Transform* me,Vector2D start, Vector2D direction, float distance, bool draw, float deltaTime);

        bool checkOnGround();
        //vector response reflect
        
        //othertypes of collision
        //gravity
        void gravityForce(float yDir);

    private:
        Gizmos *debugDrawRaycast =Gizmos::StartGizmos(1.0f,0.2f,0.8f);





};





