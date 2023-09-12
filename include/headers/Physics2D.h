#pragma once

#include "Vector2D.h"
#include "Gizmos.h"
#include <map>
#include <memory>

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

        std::unique_ptr<RayCastCollisionInfo> raycastHitinfo = std::make_unique<RayCastCollisionInfo>();
        //RayCastCollisionInfo *raycastHitinfo=nullptr;

        //checkwindowcollision
        void checkwindowcollision(Vector2D& currentPosition);
        //check raycast
        bool raycast(Transform* me,Vector2D start, Vector2D direction, float distance, bool draw, float deltaTime);
        
        bool raycastParametric(const Transform* me,Vector2D direction, float distance, bool draw, float deltaTime);

        bool checkOnGround();
        //vector response reflect
        
        //othertypes of collision
        //gravity
        void gravityForce(float yDir);

    private:
        float r= 1.0f;
        float g= 0.2f;
        float b= 0.8f;
        
        Gizmos *debugDrawRaycast = Gizmos::StartGizmos(r,g,b);
        Vector2D calculateNormalSuperfice(Vector2D pos, Vector2D end);
        bool checkConditionsCollisionParametric(Vector2D hitPoint, Vector2D b1, Vector2D b2);
        bool checkThitBetweenDeltaTime(float thit, float deltaTime);
        Vector2D calculateEndRay(Vector2D start, Vector2D dir, float dist);
        void getFirstHitRayCast();
        //void reflectPosition(const Vector2D& movement);
        
        std::map<Transform*,float> raycastHitObjectList;



};





