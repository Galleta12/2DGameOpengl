#include "Gizmos.h"

#include "SDWINDOW.h"


std::vector<Gizmos*> Gizmos::instances;
std::map<Gizmos*,bool> Gizmos::checkExist;

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

bool Gizmos::checkInstanceExists(Gizmos *currentInstance)
{
    return false;
}

void Gizmos::Cleanup()
{
    for(Gizmos* i : instances){
        delete i;
    }
    instances.clear();

}
