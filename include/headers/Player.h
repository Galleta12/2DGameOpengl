#pragma once
#include "Transform.h"






class Gun : public Transform{


    
    public:
        int speed=0;
        int power=0;
        float gunPosX = 0.0f;
        float gunPosY = 0.0f;
        Vector2D centerPlayerTriangleRef;
        
        Gun(float x, float y, int newSpeed, int newPower, Vector2D &center):Transform(x,y){
            position.x=x;
            position.y=y;
            gunPosX=x;
            gunPosY=y;
            speed = newSpeed;
            power = newPower;
            centerPlayerTriangleRef = center; 
        }

        void rotateGun();
        void update() override;
        void draw() override;

        friend std::ostream& operator <<(std::ostream& stream, const Gun& g);


    private:
        float width=100.0f;
        float height=10.0f;

};





class Player:public Transform{

      
    public:
        
            
        Player(float x, float y, int newSpeed):Transform(x,y){
            //the position are position of the transform object
            position.x = x;
            position.y = y;
            playerPosX = x;
            playerPosY = y;        
            speed = newSpeed;

        }

        
        void gunData(int newSpeed, int newPower);
        
        ~Player();
        
        void update() override;
        void draw() override;

        void keyboard();

    private:
        int speed = 0;
        float playerPosX=0.0f;
        float playerPosY=0.0f;

        float keydirX = 0.0f;
        float keydirY = 0.0f;

        Vector2D motion;

        Gun *gun=nullptr;
        Vector2D centerTriangle;
        void calculateCenter();
        
};





