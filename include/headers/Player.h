#pragma once
#include "Transform.h"
#include "Gun.h"
#include <vector>

class Gun;

class Player:public Transform{

      
    public:
        
            
        Player(float x, float y, int newSpeed):Transform(x,y){
            //the position are position of the transform object
            position.x = x;
            position.y = y;
            playerPosX = x;
            playerPosY = y;        
            speed = newSpeed;
            keydirX = 0.0f; // Initialize keydirX to 0
            keydirY = 0.0f; // Initialize keydirY to 0

           
        }

        
        void gunData(int newSpeed, int newPower);
        
        ~Player();
        
        void update(float deltaTime) override;
        void draw(float deltaTime) override;

        void keyboard();

        Gun* getGun(){return gun;}
        
    
    private:
        
        //gun pointer    
        Gun* gun = nullptr;
        
        int speed = 0;
        float playerPosX=0.0f;
        float playerPosY=0.0f;

        float keydirX = 0.0f;
        float keydirY = 0.0f;

        Vector2D motion;

        Vector2D centerTriangle;
        void calculateCenter();

        const float friction = 0.9f;

        bool isKeyDirx = false;
        

};





