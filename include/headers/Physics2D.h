#pragma once

#include "Vector2D.h"
#include "Gizmos.h"
#include <map>
#include <memory>
#include <limits>


class Transform;
class Physics2D{


    public:

        
        
        struct RayCastCollisionInfo
        {
            Vector2D hitposition;
            
            Vector2D hitnormal;

            float distance;

        };
        

        struct CollisionSatInfo
        {
            //normal for the direction where we need to push the second object
            Vector2D hitNormal;
            //depth value to move away fron the collision
            float depthValue = std::numeric_limits<float>::infinity();
            //transform object of collision
            Transform *collisionObject = nullptr;

        };
        
        
        Physics2D(){};
        ~Physics2D();

        std::unique_ptr<RayCastCollisionInfo> raycastHitinfo = std::make_unique<RayCastCollisionInfo>();
        
        std::vector<std::unique_ptr<CollisionSatInfo>> collisionInfoList;

        std::unique_ptr<CollisionSatInfo> collisionSATALGINFO = std::make_unique<CollisionSatInfo>();

        
        
        //RayCastCollisionInfo *raycastHitinfo=nullptr;

        //checkwindowcollision
        void checkwindowcollision(Vector2D& currentPosition);
        //check raycast
        bool raycast(Transform* me,Vector2D start, Vector2D direction, float distance, bool draw, float deltaTime);
        
        bool raycastParametric(const Transform* me,Vector2D direction, float distance, bool draw, float deltaTime);

        bool checkOnGround();
        bool satCollisionAlg(Transform* me, bool draw);
        //vector response reflect
        
        //othertypes of collision
        //gravity
        void gravityForce(float yDir);

        static bool satColliderChecker(const Transform* p1, const Transform* p2,float& depth, Vector2D& normalCollision);

        //list with the current collisions



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
        //collision separate axis theorem
        std::map<Transform*,std::unique_ptr<RayCastCollisionInfo>> raycastHitObjectList;

        static void ProjecAxis(const Transform* currentPolygon, Vector2D axis, float &min, float &max);

        //arimetic mean to get center of polygon
        static Vector2D  FindCenterMean(const std::vector<Vector2D*> vertices);


};





