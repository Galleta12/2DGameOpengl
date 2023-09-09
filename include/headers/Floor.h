#pragma once
#include "Transform.h"


class Floor : public Transform{


    public:

        Floor(float x, float y):Transform(x,y){
            position.x =x;
            position.y = y;
        }
     


        void update(float deltaTime) override;
        void draw(float deltaTime) override;

        bool IsGround();


    private:



};