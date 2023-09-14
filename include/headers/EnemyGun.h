#pragma once
#include "Transform.h"
#include <vector>

class EnemyGun: public Transform{


    public:
        
        EnemyGun(float x, float y, int newSpeed, int newPower):Transform(x,y){
            //50 for x and 28 for y for best precision of the position placement
            position.x=x + 50.0f;
            position.y=y + 28.0f;
            speed = newSpeed;
            power = newPower;


            Transform::basisVector = true;

        }

        ~EnemyGun();
        
        
        void update(float deltaTime ) override;
        
        void draw(float deltaTime) override;

    
        void rotateGun(Vector2D dir);
    
    private:
        
        float width=70.0f;
        float height=40.0f;
        
        float anglePlayer = 0.0f;
        
        int speed=0;
        int power=0;

         //black color
        Gizmos *debugGizmos = Gizmos::StartGizmos(0.0f,0.0f,0.0f);
        



};
