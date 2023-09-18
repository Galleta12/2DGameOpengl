#include "BulletEnemy.h"

void BulletEnemy::launchBall()
{
    motion.x = dir.x * speed;
    motion.y = dir.y * speed;

}

void BulletEnemy::init()
{

    const int numPoints = 10; // You want four points
    for (int i = 0; i < numPoints; ++i)
    {
        float angle = i * (2.0f * RadToDegree::PI / numPoints); // Calculate angle between points
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);

       // Create Vector2D for the point
        Vector2D* point = new Vector2D(x + position.x, y + position.y);
        // Add the point to the vertices list
        vertices.push_back(point);
    }


}

void BulletEnemy::update(float deltaTime)
{

    Transform::update(deltaTime);

    position.x +=  motion.x * deltaTime;
    position.y +=  motion.y * deltaTime;
    updatePoints(deltaTime);
}

void BulletEnemy::draw(float deltaTime)
{

     glPushMatrix();
    
    glTranslatef(position.x, position.y, 0.0f);

    glLineWidth(2.0f); // Set the line width

    glBegin(GL_LINES);
    glColor3f(0.95f,0.59f,0.4f); 

    const int numSegments = 10; // Number of line segments to approximate the circle
    const float angleIncrement = 2.0f * RadToDegree::PI / numSegments;
    float angle = 0.0f;

    while(angle < 2.0f * RadToDegree::PI)
    {
        // Calculate the coordinates of the endpoints of each line segment
        float x1 = radius * std::cos(angle);
        float y1 = radius * std::sin(angle);
        float x2 = radius * std::cos(angle + angleIncrement);
        float y2 = radius * std::sin(angle + angleIncrement);

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);

        angle += angleIncrement;
    }

    glEnd();

    glPopMatrix();


}

void BulletEnemy::OnCollision(float deltaTime, Transform *objectCollision, Vector2D normalCollision, float depth, Vector2D unmodifiedNormalCollision)
{
    Transform::OnCollision(deltaTime,objectCollision,normalCollision,depth,unmodifiedNormalCollision);
    Vector2D normal = normalCollision;
    Vector2D reflec = Vector2D::Reflection(dir, normal);
    dir = Vector2D::Normalized(reflec);
    motion.x = (dir.x * speed) + (depth * normalCollision.x);
    motion.y = (dir.y * speed) + (depth * normalCollision.y);

}

void BulletEnemy::updatePoints(float deltaTime)
{
    for(auto& b : vertices){
        b->x += motion.x * deltaTime;
        b->y += motion.y * deltaTime;
    }

}
