#include "Gun.h"

Gun::~Gun()
{
    //delete bullet;
    for(auto& b : bulletList){
        delete b;
    }
    bulletList.clear();
}

void Gun::setMousePosition(std::vector<int> mousePositions)
{
    mousePos.x = static_cast<float>(mousePositions[0]);
    mousePos.y =  *SDWINDOW::WindowHeight - static_cast<float>(mousePositions[1]);
    //std::cout<< "Mouse current X: " << mousePos.x << "Mouse current y: " << mousePos.y << std::endl;     

}

void Gun::updatePosition(float deltaTime, Vector2D motion)
{
    //position.x += motion.x * deltaTime;
    position =  centerPlayerTriangleRef;


}

void Gun::rotateGun()
{
    
    Vector2D gunOffset = getMousePosition();
    gunOffset.y = gunOffset.y + 5.0f;
    
    //we want to get the direction of the mouse from the vector position
    Vector2D dir = (gunOffset - position).Normalize();

  
    debugGizmos->RenderLine(centerPlayerTriangleRef,getMousePosition());
    //debugGizmos->RenderRay(centerPlayerTriangleRef,dir, 200.0f);

    //Vector2D posDir = Vector2D::Normalized(position);

    
    
    // std::cout << "Normalize dir" << dir << std::endl;
    // std::cout << "Normalize position" << posDir << std::endl;
    
    
    //angleMouse = Vector2D::Angle(getUpVec(),dir);
    //angleMouse = Vector2D::SignedAngle(getRightVec(),dir);
    float angle = std::atan2(dir.y, dir.x);
    
    angleMouse = RadToDegree::convert(angle);
    
    //save the rotation
    Rotation = angleMouse;

    getPositionofTip();

    //std::cout << "angle: " << angleMouse << std::endl;
    //std::cout << "up vector: " << getUpVec() << std::endl;

}

void Gun::update(float deltaTime)
{

    Transform::update(deltaTime);
    rotateGun();
    //for(auto& b : bulletList)b->update(deltaTime);



}

void Gun::draw(float deltaTime)
{
    
    glPushMatrix();
   
    //std::cout<< "Current center" << centerPlayerTriangleRef << std::endl;
    // Vector2D centerInLocal;
    // centerInLocal.x = centerPlayerTriangleRef.x - position.x;
    // centerInLocal.y = centerPlayerTriangleRef.y - position.y;
    
    glTranslatef(0.0f,-33.0f,0.0f);
    //glTranslatef(0.0f,0.0f,0.0f);
    glRotatef(angleMouse,0.0f,0.0f,1.0f);
    
    

    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,1.0f);

    // Draw a thin box (rectangle)
    glVertex2f(0.0f, 0.0f);            // Top-left corner
    glVertex2f(width, 0.0f);           // Top-right corner
    glVertex2f(width, height);         // Bottom-right corner
    glVertex2f(0.0f, height);          // Bottom-left corner

    // //std::cout << "Gun widht: " << width << " Heigh: " << height << std::endl;
    glEnd();

    //calculateGunTip();

    //for(auto& b : bulletList)b->draw(deltaTime);
        
    glPopMatrix();


}

void Gun::mouseLeftPressed(std::vector<int> mousePositions)
{
    Vector2D gunOffset = getMousePosition();
    gunOffset.y = gunOffset.y + 5.0f;
    
    //we want to get the direction of the mouse from the vector position
    Vector2D dir = (gunOffset - position).Normalize();

    //if pressed we want to create a bullet
    //std::cout << "This is the dir: " << dir << std::endl;
    
    //bulletList.push_back(new Bullet({width,0.0f,5.0f,5,10,getPositionofTip(),Rotation}));
    
    Vector2D positionLaunch = getPositionofTip();
    //refence to the bullet list on the gun.
    //bulletList.push_back(new Bullet({positionLaunch.x,positionLaunch.y,15.0f,1,10,Rotation,dir}));
    //we want the bullet list to be added to the transform list
    SDWINDOW::transformList.push_back(new Bullet({positionLaunch.x,positionLaunch.y,15.0f,3,10,Rotation,dir}));

    //std::cout<< "Mouse X: " << mouseClickX << "Mouse y: " << mouseClickY << std::endl;     

    
    //std::cout << "Mouse pos: " << mousePos << std::endl;
}

Vector2D Gun::convertCenterInLocal()
{
    Vector2D centerInLocal;
    centerInLocal.x = centerPlayerTriangleRef.x - position.x;
    centerInLocal.y = centerPlayerTriangleRef.y - position.y;
    return centerInLocal;
}

Vector2D Gun::getPositionofTip()
{
    
    Vector2D worldPosTip;
    Vector2D gunOffset = getMousePosition();
    gunOffset.y = gunOffset.y + 5.0f;
    
    //we want to get the direction of the mouse from the vector position
    Vector2D dir = (gunOffset - position).Normalize();
    
    Vector2D copycenter = centerPlayerTriangleRef;
    
    
    worldPosTip = copycenter + (dir * width);
    
    
    //debugGizmos->RenderLine(centerPlayerTriangleRef,worldPosTip);
    
    return worldPosTip;
}

void Gun::calculateGunTip()
{
    gunTip = position + Vector2D(10.0f,10.0f);


}



std::ostream &operator<<(std::ostream &stream, const Gun &g)
{
   
     stream << "Gun Pos(" << g.gunPosX << "," << g.gunPosY << ")\n"
     << "Gun TranformPos(" << g.position.x << "," << g.position.y << ")\n"
     << "Gun Refence of center player(" << g.centerPlayerTriangleRef << "This is the y component of sdl window "<< *SDWINDOW::WindowHeight - g.centerPlayerTriangleRef.y << ")";
     return stream;
}
