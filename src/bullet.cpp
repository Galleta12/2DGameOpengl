#include "Bullet.h"

//need deltatiem for the initial launch
#include "Clocker.h"

static auto lastPrintTime = std::chrono::system_clock::now();

Bullet::~Bullet()
{

  
}

void Bullet::launchBall()
{
    //velocity = dir; 
    motion.x = dir.x * speed;
    motion.y = dir.y * speed;
    

}

void Bullet::init()
{

    //vertices.push_back(&position);
    
    // Calculate points evenly spaced around the circumference of the ball
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

    
   
    //create a dubug gizmos instance
    Gizmos *points = Gizmos::StartGizmos(1.0f,0.0f,1.0f);
    points->SetPointsDebug(vertices,2.0f);

}



void Bullet::update(float deltaTime)
{
    
    //add the end we want to get the transform updates
    Transform::update(deltaTime);

    
    
 
    //std::cout<< "Dir update" << dir << std::endl;
    //I will compute each of this on different component there is a problem on my vectors
    // for(auto& a : vertices){

    // }
     
    bool isHit = Transform::getPhysics2D()->raycastParametric(this,dir,50.0f,true,deltaTime);
    
    if(isHit){
        //call the vector reflection
        Vector2D normal = Transform::getPhysics2D()->raycastHitinfo->hitnormal.Normalize();
        //use same direction used in the raycast
        Vector2D reflec = Vector2D::Reflection(dir, normal);

        //std::cout<<"reflect" << reflec << std::endl;

        dir = Vector2D::Normalized(reflec);
        motion.x = dir.x * speed;
        motion.y = dir.y * speed;
    }
    
    
    position.x +=  motion.x * deltaTime;
    position.y +=  motion.y * deltaTime;
    updatePoints(deltaTime);

  
   
       
    
    
    // Calculate time difference since last print
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - lastPrintTime;

    // Check if 5 seconds have passed since last print
    
    if (elapsedTime.count() >= 5) {
   
        lastPrintTime = currentTime;

       // Remove this bullet from the transformList
        SDWINDOW::transformList.erase(std::remove(SDWINDOW::transformList.begin(), SDWINDOW::transformList.end(), this), SDWINDOW::transformList.end());

        // Delete this bullet object
        delete this;
 
    }

    //we always want to reder the velocity
    //Vector2D end = Vector2D::Addition(position,(Vector2D::ScalarMultiplication(dir,30.0f)));
    
    //debugVelocity->RenderRay(position,dir, 30.0f); 
    //debugVelocity->RenderLine(position,end); 
    //collisions


}

void Bullet::draw(float deltaTime)
{

    glPushMatrix();
    
    glTranslatef(position.x, position.y, 0.0f);

    glLineWidth(2.0f); // Set the line width

    glBegin(GL_LINES);
    glColor3f(r,g,b); // Red color

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

float Bullet::randomFloat()
{
    // Function to generate a random float between 0 and 1
    
        return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    
    

}

void Bullet::updatePoints(float deltaTime)
{

    for(auto& b : vertices){
        b->x += motion.x * deltaTime;
        b->y += motion.y * deltaTime;
    }

}
