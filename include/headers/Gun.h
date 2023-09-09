#pragma once
#include "Transform.h"

#include "SDWINDOW.h"
#include "RadToDegree.h"
#include <iostream>

#include <vector>
#include <chrono>


#include "Gizmos.h"


class Gun : public Transform{


    
    public:
        int speed=0;
        int power=0;
        float gunPosX = 0.0f;
        float gunPosY = 0.0f;
        Vector2D &centerPlayerTriangleRef;
        
        Gun(float x, float y, int newSpeed, int newPower, Vector2D &center):Transform(x,y), centerPlayerTriangleRef(center){
            position.x=x;
            position.y=y;
            gunPosX=x;
            gunPosY=y;
            speed = newSpeed;
            power = newPower;
            //centerPlayerTriangleRef = center;
        }

        
        void setMousePosition(std::vector<int> mousePositions);

        Vector2D getMousePosition(){return mousePos;}
       
        void updatePosition(float deltaTime, Vector2D motion);
        void rotateGun();
        void update(float deltaTime ) override;
        void draw(float deltaTime) override;

        friend std::ostream& operator <<(std::ostream& stream, const Gun& g);


    private:
        float width=60.0f;
        float height=10.0f;
        Vector2D mousePos;
        float angleMouse = 0.0f;
        //black color
        Gizmos *debugGizmos = Gizmos::StartGizmos(0.0f,0.0f,0.0f);
};
