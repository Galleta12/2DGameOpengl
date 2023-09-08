#pragma once
#include "Transform.h"

#include <vector>




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
            keydirX = 0.0f; // Initialize keydirX to 0
            keydirY = 0.0f; // Initialize keydirY to 0

           
        }

        
        void gunData(int newSpeed, int newPower);
        
        ~Player();
        
        void update(float deltaTime) override;
        void draw(float deltaTime) override;

        void keyboard();

        
        
        //gun pointer    
        Gun* gun = nullptr;
    
    private:
        
        
        int speed = 0;
        float playerPosX=0.0f;
        float playerPosY=0.0f;

        float keydirX = 0.0f;
        float keydirY = 0.0f;

     

        Vector2D motion;

        Vector2D centerTriangle;
        void calculateCenter();
        
};





