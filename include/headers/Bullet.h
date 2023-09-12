#pragma once
#include "Transform.h"

#include "SDWINDOW.h"
#include "RadToDegree.h"
#include <iostream>

#include <vector>
#include <chrono>
#include <cmath>

#include <cstdlib>
#include <ctime>

#include "Gizmos.h"


class Bullet : public Transform{


    public:

        
        Bullet(float x, float y, float _radius,int newSpeed, int newPower, float rotation, Vector2D dirMouse):Transform(x,y){
            position.x = x;
            position.y = y;
            Rotation = rotation;
            radius = _radius;
            speed = newSpeed;
            power = newPower;
            dir = dirMouse;

            //std::cout << "this dir bullet: " << dir << std::endl;

            //we want to set the color
            r = randomFloat();
            g = randomFloat();
            b = randomFloat();
            Transform::basisVector = false;
            Transform::AddPhysics2D();
            //this is a parent
            init();
            launchBall();
            isBullet= true;
        }
        
        
        Bullet(float x, float y, float _radius,int newSpeed, int newPower, Vector2D launchPos, float rotation):Transform(x,y){
            position.x = x;
            position.y = y;
            Rotation = rotation;
            radius = _radius;
            speed = newSpeed;
            power = newPower;
            positionOfLaunch = launchPos;

            //we want to set the color
            r = randomFloat();
            g = randomFloat();
            b = randomFloat();
            //we set the bullet as local
            // Transform::isLocalSpace = true;
            // Transform::basisVector = true;
            //get the local space cordinates for the gizmos
            //Transform::convertLocalToWorld(launchPos);

            init();
        }
        ~Bullet();

        void launchBall();  
        void init() override;
        void update(float deltaTime ) override;
        void draw(float deltaTime) override;
        

    
    private:
        //Vector2D &gunTip;
        int speed = 0;
        int power = 0;
        float radius = 0.0f;
        float airFriction = 0.08f;
        float r,g,b = 0.0f;
        float timer = 0.0f;
        Vector2D positionOfLaunch;
        Vector2D dir;
        float randomFloat();
        Vector2D motion;
        Gizmos *debugVelocity = Gizmos::StartGizmos(0.8f,0.5f,1.0f);
        
        void updatePoints(float deltaTime);
     
     

};