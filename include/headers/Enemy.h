#pragma once
#include "Transform.h"
#include "EnemyGun.h"
#include "Player.h"
#include <vector>
#include <memory>


class Enemy : public Transform{

    public:
        Enemy(float x, float y, std::shared_ptr<Player> _player):Transform(x,y){
            position.x = x;
            position.y = y;
            Transform::AddPhysics2D();
            init();
            startEnemyGun();
             
            Transform::isEnemy = true;
            playerRef = _player;
        }



    ~Enemy();
    void init()override;
    void update(float deltaTime)override;
    void draw(float deltaTime)override;
    void OnCollision(float deltaTime,Transform* objectCollision,Vector2D normalCollision, float depth, Vector2D unmodifiedNormalCollision) override;

    private:
        std::shared_ptr<Transform> playerRef;
        //pointer to enemygu
        EnemyGun* enemyGun;  
        Gizmos *debugger = Gizmos::StartGizmos(1.0f,0.5f,1.0f);
        void startEnemyGun();
        void setEnemyPosition(float deltaTime);
        float timeSinceLastShot= 0.0f;
       

};
