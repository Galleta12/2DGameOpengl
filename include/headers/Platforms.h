#pragma once
#include "Transform.h"
#include <vector>

class Platforms: public Transform{

    public:
        
        
        Platforms(float x, float y, float _endX, float _endY):Transform(x,y){ 
            position.x = x;
            position.y = y;
            end.x = _endX;
            end.y = _endY;
            lineFlag = true;
            Transform::AddPhysics2D();
            init();
        }
        
        ~Platforms(){}


        void init()override;
        
        void update(float deltaTime)override;
              
        void draw(float deltaTime)override;
    
    private:
        Vector2D end;
        Vector2D normalVec;
        
        Gizmos *debugNormal= Gizmos::StartGizmos(1.0f,0.0f,0.0f);
    
};