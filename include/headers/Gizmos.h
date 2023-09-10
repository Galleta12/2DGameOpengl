#pragma once

#include "Vector2D.h"
#include <vector>
#include <map>

class Gizmos{


    public:

        Gizmos(float r, float g, float b):r(r), g(g), b(b){}
        ~Gizmos(){}

        static Gizmos* StartGizmos(float r, float g, float b);
        
        void RenderLine(Vector2D start, Vector2D end);
        void RenderRay(Vector2D start, Vector2D direction, float distance);

         
        
        void changeColor(float r, float g, float b);




        void DrawLine();
        void DrawRay();
        

        bool checkInstanceExists(Gizmos* currentInstance);
        
        static void Cleanup();

        static std::vector<Gizmos*> instances;
        static std::map<Gizmos*,bool> checkExist;
    
    private:
        float r,g,b;
        Vector2D lineStart, lineEnd;
        Vector2D rayStart, rayEnd;




};




