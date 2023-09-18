#pragma once
#include "Transform.h"


class Floor : public Transform{


    public:

     
        
        Floor(float x, float y):Transform(x,y){
            position.x =x;
            position.y = y;
            end.x = position.x + (2500.0f - 2.0f);
            end.y = position.y; 
            lineFlag = true;
            Transform::AddPhysics2D();
            Transform::isFloor = true;
            init();
        }
     


        void init() override;
        void update(float deltaTime) override;
        void draw(float deltaTime) override;
        void OnCollision(float deltaTime,Transform* objectCollision,Vector2D normalCollision, float depth, Vector2D unmodifiedNormalCollision) override;

        bool IsGround();


    private:
        Vector2D end;

        Gizmos *debugNormal= Gizmos::StartGizmos(1.0f,0.0f,0.0f);


};