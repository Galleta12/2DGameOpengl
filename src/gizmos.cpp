#include "Gizmos.h"

#include "SDWINDOW.h"


std::vector<Gizmos*> Gizmos::instances;
std::map<Gizmos*,bool> Gizmos::checkExist;


Gizmos::~Gizmos()
{
    // for(auto& v : pointPointers){
    //     delete v;
    // }
    // pointPointers.clear();

}
void Gizmos::ClearPointsDebug()
{
    
    // if(pointPointers.size()==0)return;
    // for(auto& pointer : pointPointers) {
    //     delete pointer;
    // }
    //pointPointers.clear();
}

Gizmos *Gizmos::StartGizmos(float r, float g, float b)
{
    Gizmos* instance = new Gizmos(r,g,b);    
    instances.push_back(instance);
    
    return instance;
}

void Gizmos::RenderLine(Vector2D start, Vector2D end)
{
    this->lineStart = start; 
    this->lineEnd = end;


}

void Gizmos::RenderRay(Vector2D start, Vector2D direction, float distance)
{
    
    this->rayStart = start;
    this->rayEnd = start + (direction * distance);

}

void Gizmos::SetPointsDebug(std::vector<Vector2D*>& points, float _radius)
{
    
    for(auto& a : points){
        //std::cout<< *a << "point" << std::endl;
        pointPointers.push_back(a);
    }

    //set the radius
    radius = _radius;
    
    //pointPointers = points;


}



void Gizmos::changeColor(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;

}

void Gizmos::DrawLine()
{
    glPushMatrix();

    glLineWidth(2.0f);

    glBegin(GL_LINES);
    glColor3f(this->r,this->g,this->b);

    glVertex2f(this->lineStart.x, this->lineStart.y);
    glVertex2f(this->lineEnd.x, this->lineEnd.y);


    glEnd();
    glPopMatrix();
}

void Gizmos::DrawRay()
{
    
    glPushMatrix();

    glLineWidth(2.0f);

    glBegin(GL_LINES);
    glColor3f(this->r,this->g,this->b);

    glVertex2f(this->rayStart.x, this->rayStart.y);
    glVertex2f(this->rayEnd.x, this->rayEnd.y);


    glEnd();
    glPopMatrix();

}

void Gizmos::DrawPoints()
{
    if(pointPointers.size()==0){return;}
    //std::cout<< "point" << *(pointPointers)[0] << std::endl;
    
    
    for(auto & t : pointPointers){
        glPushMatrix();

        glTranslatef(t->x, t->y, 0.0f);

        glLineWidth(2.0f); // Set the line width

        glBegin(GL_LINES);
        glColor3f(r,g,b); // Red color

        const int numSegments = 100; // Number of line segments to approximate the circle
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
    


}





void Gizmos::Cleanup()
{
    
     
   
    for(Gizmos* i : instances){
        
        // if(i->pointPointers.size()!=0){
        //     i->ClearPointsDebug();
        // }
        delete i;
    }

    
    instances.clear();

}
