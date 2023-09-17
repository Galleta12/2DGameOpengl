#pragma once
#include "Transform.h"
#include "EnemyGun.h"
#include <vector>
#include <memory>


class Enemy : public Transform{

    public:
        Enemy(float x, float y, Transform* _player):Transform(x,y){
            position.x = x;
            position.y = y;
            Transform::AddPhysics2D();
            init();
            startEnemyGun();
             
            Transform::isEnemy = true;
            //player = _player;
        }



    ~Enemy();
    void init()override;
    void update(float deltaTime)override;
    void draw(float deltaTime)override;
    void OnCollision(float deltaTime,Transform* objectCollision,Vector2D normalCollision, float depth, Vector2D unmodifiedNormalCollision) override;

    private:
        const Transform* player = nullptr;
        //pointer to enemygu
        std::unique_ptr<EnemyGun> enemyGun;  
        Gizmos *debugger = Gizmos::StartGizmos(1.0f,0.5f,1.0f);
        void startEnemyGun();
        void setEnemyPosition(float deltaTime);
        float timeSinceLastShot= 0.0f;
       

};
