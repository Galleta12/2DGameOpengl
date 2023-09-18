#pragma once

#include "Vector2D.h"
#include "Gizmos.h"

#include "Physics2D.h"

#include <cmath>
#include <memory>

class Transform{

    public:
        
                
        //flags
        bool isEnemy = false;
        
        bool isFloor = false; 
        
        bool isPlayer=false;

        bool isBox=false;

        bool isBullet = false;

        bool isEnemyBullet = false;

        
        bool lineFlag=false;
        //normal vector for platforms and floor
        Vector2D normalVectorPlane;
           
        Vector2D position;
        
        Vector2D velocity;
        
        Vector2D right;
        Vector2D up;
        
        float Rotation = 0.0f;
        //this is also to draw a basis vector
        bool basisVector = false;

        Transform(float x, float y){
            position.x = x;
            position.y = y;
        }
        
        ~Transform();

        Vector2D getRightVec();
        
        Vector2D getUpVec();

        //for setting up the verticec
        virtual void init(){}
        virtual void update(float deltaTime);
        virtual void draw(float deltaTime){}

        //use this for shooting bullets with the enemy
        virtual void eventForEnemy(float deltaTime){}


        virtual void computeNormalEdges(){}

        virtual void OnCollision(float deltaTime,Transform* objectCollision,Vector2D normalCollision, float depth, Vector2D unmodifiedNormalCollision);

  
        void DrawUpGizmosTransform();
        void DrawRightGizmos();

        //virtual ~Transform(){}
        
        //create physics instance
        void AddPhysics2D();
  
        Physics2D *getPhysics2D();

        
        //list of points that confomr the picuture, worldpos
        std::vector<Vector2D*> vertices;

        std::vector<Vector2D*> normalEdgesList; 

        //for debuggin normal collisions
        Gizmos *normalDebug = Gizmos::StartGizmos(0.7f,0.5f,0.5f);
    
    private:
        //purple for the up gizmos
        Gizmos *upGizmos = Gizmos::StartGizmos(0.5f, 0.5f, 0.0f);
        // for the right right gizmos
        Gizmos *rightGizmos = Gizmos::StartGizmos(1.0f, 0.5f, 0.0f);
        //
        std::unique_ptr<Physics2D> physics2D;
        
        
        //Physics2D *physics2D = nullptr;
        
        


};