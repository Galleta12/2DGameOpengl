#pragma once
#include "SDWINDOW.h"
#include "Transform.h"


class BulletEnemy : public Transform{

    public:
        BulletEnemy(float x, float y, float _radius,int newSpeed, int newPower, float rotation, Vector2D newDir):Transform(x,y){
            position.x = x;
            position.y = y;
            Rotation = rotation;
            radius = _radius;
            speed = newSpeed;
            power = newPower;
            dir = newDir;
            Transform::isEnemyBullet = true;
            Transform::isBullet = true;
            Transform::AddPhysics2D();
            init();
            launchBall();

        }

        ~BulletEnemy(){}
        void launchBall();  
        void init() override;
        void update(float deltaTime ) override;
        void draw(float deltaTime) override;
        void OnCollision(float deltaTime,Transform* objectCollision,Vector2D normalCollision, float depth,Vector2D unmodifiedNormalCollision) override;



    private:
        Vector2D dir;
        int speed = 0;
        int power = 0;
        float radius = 0.0f;
        Vector2D motion;
        
        void updatePoints(float deltaTime);

};