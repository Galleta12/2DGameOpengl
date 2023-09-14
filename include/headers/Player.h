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

            //allow physics for this
            Transform::AddPhysics2D();
            //allow basis
            Transform::basisVector = false;
            //set up the vertices
            Transform::isPlayer=true;
            
            init();
           
        }

        
        void gunData(int newSpeed, int newPower);
        
        ~Player();
        
        void init() override;
        void update(float deltaTime) override;
        void draw(float deltaTime) override;
        void computeNormalEdges() override;
        void keyboard();

        void OnCollision(float deltaTime,Transform* objectCollision,Vector2D normalCollision, float depth) override;

        Gun* getGun(){return gun;}

        const Vector2D getPlayerPos(){return position;}
        

        void resetPosition(float x, float y);

        bool getIsDeath(){return isDeath;}

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
        void checkIsCollisionGround(float deltaTime);

        void yMovements(float deltaTime);

        const float friction = 0.9f;

        bool isKeyDirx = false;
        
        bool isCollisionFloor = false;

        bool isDeath = false;


        Vector2D leftVertex;
        Vector2D rightVertex;

};





