#pragma once

#include "Vector2D.h"

class Transform{

    public:
        
        Vector2D position;
        Vector2D velocity;
        float Rotation = 0.0f;
        
        
        Transform(float x, float y){
            position.x = x;
            position.y = y;
        }
       
        // Transform(){
        //    position.Zero();
        //    velocity.Zero();
        // }
        
        ~Transform(){}

        

        
        virtual void init(){}
        virtual void update(){}
        virtual void draw(){}

        //virtual ~Transform(){}
        

    private:



};