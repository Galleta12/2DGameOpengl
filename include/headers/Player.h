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
            Transform::basisVector = true;
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

        void OnCollision(float deltaTime,Transform* objectCollision,Vector2D normalCollision, float depth,Vector2D unmodifiedNormalCollision) override;

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
        void updateXmovements(float deltaTime);
        void updateYmovements(float deltaTime);
        void jumpHanlder(float deltaTime);

        void ProjectionAlongPlane(float deltaTime, Vector2D normal,const Transform* objectedCollided, Vector2D newMotion);
        float AngleWithPlane(Vector2D ortho, Vector2D normal);
        const float friction = 0.9f;

        bool isKeyDirx = false;
        
        bool isCollisionFloor = false;

        bool isDeath = false;

        bool isJumping = false;

        Vector2D leftVertex;
        Vector2D rightVertex;
        float jumpForce = 0.0f;
        //int jumpSpeed = 3;
        //gizmos for debuggin projection
        Gizmos *debuggerLine = Gizmos::StartGizmos(1.0f,0.5f,1.0f);
        Gizmos *debuggerMotion = Gizmos::StartGizmos(0.0f,0.0f,0.0f);


};





