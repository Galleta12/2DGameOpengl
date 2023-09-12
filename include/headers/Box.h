#pragma once
#include "Transform.h"
#include <vector>

class Box : public Transform{

    public:
        Box(float x, float y):Transform(x,y){
            position.x = x;
            position.y = y;
            init();
            //Transform::basisVector = true;

        }
        ~Box();

        void init()override;
        void computeNormalEdges() override;
        void update(float deltaTime)override;
        void draw(float deltaTime)override;


    private:

        Gizmos *debugger = Gizmos::StartGizmos(1.0f,0.5f,1.0f);



};