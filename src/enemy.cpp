#include "Enemy.h"

#include "SDWINDOW.h"

#include "Gizmos.h"

//#include "BulletEnemy.h"

#include <memory>


static auto lastPrintTime = std::chrono::system_clock::now();

Enemy::~Enemy()
{
    delete enemyGun;
}

void Enemy::init()
{

        
    Vector2D* topLeft = new Vector2D(position.x, position.y + 100.0f);
    Vector2D* topRight = new Vector2D(position.x + 100.0f, position.y + 100.0f);
    Vector2D* bottomRight = new Vector2D(position.x + 100.0f, position.y);
    Vector2D* bottomLeft = new Vector2D(position.x, position.y);

    vertices.push_back(topRight);
    vertices.push_back(bottomRight);
    vertices.push_back(bottomLeft);
    vertices.push_back(topLeft);
    
    // vertices.push_back(topLeft);
    // vertices.push_back(bottomLeft);
    // vertices.push_back(bottomRight);
    // vertices.push_back(topRight);

    Gizmos* points = Gizmos::StartGizmos(0.45f, 1.0f, 1.0f);
    points->SetPointsDebug(vertices, 4.0f);


}

void Enemy::update(float deltaTime)
{
    Transform::update(deltaTime);

    //std:: cout << "Playe ref" << player->position << std::endl;
    setEnemyPosition(deltaTime);
    enemyGun->update(deltaTime);

    

}

void Enemy::draw(float deltaTime)
{

    glPushMatrix();

    glTranslatef(position.x,position.y,0.0f);
    
    glBegin(GL_QUADS);
    
    glColor3f(0.0f, 0.5f, 0.5f);
    //glColor3f(1.0f, 1.0f, 1.0f);
    
    //reference
    // glVertex3f(x1, y1, z1);  // Top-left
    // glVertex3f(x2, y2, z2);  // Top-right
    // glVertex3f(x3, y3, z3);  // Bottom-right
    // glVertex3f(x4, y4, z4);  // Bottom-left
    
    
    glVertex2f(0.0f,0.0f);
    glVertex2f(100.0f,0.0f);
    glVertex2f(100.0f ,100.0f);
    glVertex2f(0.0f,100.0f);
    
    glEnd();

    enemyGun->draw(deltaTime);

    glPopMatrix();

}

void Enemy::OnCollision(float deltaTime, Transform *objectCollision, Vector2D normalCollision, float depth,Vector2D unmodifiedNormalCollision)
{
    
    Transform::OnCollision(deltaTime,objectCollision,normalCollision,depth,unmodifiedNormalCollision);
    
    if(objectCollision->isBullet)return;


}

void Enemy::eventForEnemy(float deltaTime)
{

    //if(SDWINDOW::)
    if(SDWINDOW::event.type == SDL_KEYDOWN){
        switch (SDWINDOW::event.key.keysym.sym)
        {
        case SDLK_g:
            
            std::cout << "Enemy Bullet" << std::endl;
            enemyGun->launchBullet(deltaTime, currentDir);
                        
            break;
        
        default:
            break;
        }
    }

}

void Enemy::setEnemyPosition(float deltaTime)
{

    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - lastPrintTime;
    Vector2D dir  = Vector2D::Substraction(playerRef->position,position);



    enemyGun->rotateGun(Vector2D::Normalized(dir));

    //save dir for enemy
    Vector2D dirToPlayer = Vector2D::Normalized(dir);
    currentDir = dirToPlayer;

    if (elapsedTime.count() >= 3) {

        
        lastPrintTime = currentTime;
        
        // Bullet* b = new Bullet(position.x, position.y, 15.0f, 3, 10, Rotation, dir, true);
        // if (b) {
        //     SDWINDOW::transformList.emplace_back(b);
        // } 
        
        //std::cout << b << std::endl;
       
   
        //enemyGun->launchBullet(deltaTime, Vector2D::Normalized(dir));

        //std::cout<< "what the hell" << std::endl;
        
    }

    
}

void Enemy::startEnemyGun()
{
   enemyGun = new EnemyGun(position.x,position.y, 2, 10);

}


