#pragma once
#include "Transform.h"
#include <vector>

class Box : public Transform{

    public:
        
        Box(float x, float y):Transform(x,y){
            position.x = x;
            position.y = y;
            Transform::isBox = true;
            Transform::AddPhysics2D();
            init();
            //Transform::basisVector = true;

        }
        
        Box(float x, float y, bool _isMove):Transform(x,y){
            position.x = x;
            position.y = y;
            Transform::isBox = true;
            Transform::AddPhysics2D();
            init();
            isMove = _isMove;
            //Transform::basisVector = true;

        }




        ~Box();

        void init()override;
        void computeNormalEdges() override;
        void update(float deltaTime)override;
        void draw(float deltaTime)override;
        void OnCollision(float deltaTime,Transform* objectCollision,Vector2D normalCollision, float depth) override;


    private:

        Gizmos *debugger = Gizmos::StartGizmos(1.0f,0.5f,1.0f);
        bool isMove = false;


};