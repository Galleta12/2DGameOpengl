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
        

          
        Physics2D(){};
        ~Physics2D();
        //unique pointer of the collison info this is use for the parametric collision
        std::unique_ptr<RayCastCollisionInfo> raycastHitinfo = std::make_unique<RayCastCollisionInfo>();
        
      
        
        bool raycastParametric(const Transform* me,Vector2D direction, float distance, bool draw, float deltaTime);



        //separate axis theorem collider
        static bool satColliderChecker(const Transform* p1, const Transform* p2,float& depth, Vector2D& normalCollision);




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

        std::map<const Transform*,std::unique_ptr<RayCastCollisionInfo>> raycastHitObjectList;

        //project axis for the algorithm
        static void ProjecAxis(const Transform* currentPolygon, Vector2D axis, float &min, float &max);

        //arimetic mean to get center of polygon
        static Vector2D  FindCenterMean(const std::vector<Vector2D*> vertices);


};





