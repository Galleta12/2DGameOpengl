#pragma once



#include "Vector2D.h"
#include <vector>
#include <map>
#include "cmath"
#include "RadToDegree.h"

class Gizmos{


    public:

        

        Gizmos(float r, float g, float b):r(r), g(g), b(b){}
        ~Gizmos();

        static Gizmos* StartGizmos(float r, float g, float b);

        
        void RenderLine(Vector2D start, Vector2D end);
        void RenderRay(Vector2D start, Vector2D direction, float distance);

        void SetPointsDebug(std::vector<Vector2D*>& points, float _radius);  

        
        void changeColor(float r, float g, float b);
         
    



        void DrawLine();
        void DrawRay();
        void DrawPoints();

        bool checkInstanceExists(Gizmos* currentInstance);
        
        static void Cleanup();
        void ClearPointsDebug();

        static std::vector<Gizmos*> instances;
        static std::map<Gizmos*,bool> checkExist;
    
    private:
        
        float r,g,b;
        float rC,gC, bC;
        float radius;
        Vector2D lineStart, lineEnd;
        Vector2D rayStart, rayEnd;
        std::vector<Vector2D*> pointPointers;

};




