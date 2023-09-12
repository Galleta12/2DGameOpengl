#pragma once

#include "Vector2D.h"
#include "Gizmos.h"

#include "Physics2D.h"

#include <cmath>

class Transform{

    public:
        
                
        bool isBullet=false;
        
        Vector2D normalVectorPlane;
        
        bool lineFlag=false;
           
        Vector2D localPosToWorld;
        
        Vector2D position;
        Vector2D velocity;
        
        Vector2D right;
        Vector2D up;
        
        float Rotation = 0.0f;
        
        bool isLocalSpace=false;

        bool basisVector = false;

        Transform(float x, float y){
            position.x = x;
            position.y = y;
        }
       
        // Transform(){
        //    position.Zero();
        //    velocity.Zero();
        // }
        
        ~Transform(){
            delete physics2D;
             for(auto& v : vertices){
                    delete v;
                }
              for (Vector2D* normalPtr : normalEdgesList) {
                        delete normalPtr; // Deallocate the memory for each Vector2D object
                }
                normalEdgesList.clear();
                vertices.clear();
        }

        Vector2D getRightVec(){

            // Get the up vector
            Vector2D upVector = getUpVec();

            // Calculate the right vector by rotating the up vector 90 degrees counterclockwise
            Vector2D rightVector(-upVector.y, upVector.x);
            right = rightVector;
            
            return right * -1;
        }
        
        Vector2D getUpVec(){
            
            float angleRadians = Rotation * (3.14159265359f / 180.0f); // Convert degrees to radians
            float upX = -std::sin(angleRadians); // Negative sin for upwards direction
            float upY = std::cos(angleRadians);  // Cosine for upwards direction
            up.x = upX;
            up.y = upY;

            return up;

        }

        //for setting up the vertices
        virtual void init(){}
        virtual void update(float deltaTime){
            
            getUpVec();
            getRightVec();
            
            if(basisVector){
                DrawUpGizmosTransform();
                DrawRightGizmos();
            }
        }
        virtual void draw(float deltaTime){}

        virtual void computeNormalEdges(){}


        void convertLocalToWorld(Vector2D parentPosition){
            //localPosToWorld = parentPosition + position;                                     
            localPosToWorld = parentPosition;                                     

        }

        void DrawUpGizmosTransform(){
            //std::cout<<"DrawGizmos" << std::endl;
            if(!isLocalSpace){

                upGizmos->RenderRay(position,up.Normalize(),100.0f);
            }
            else{
                upGizmos->RenderRay(localPosToWorld,up.Normalize(),100.0f);

            }
        }
        void DrawRightGizmos(){
            if(!isLocalSpace){

                rightGizmos->RenderRay(position,right.Normalize(),100.0f);
            }
            else
            {
                rightGizmos->RenderRay(localPosToWorld,right.Normalize(),100.0f);

            }
        }


        //create physics instance
        void AddPhysics2D(){
            physics2D = new Physics2D();
        }
        //virtual ~Transform(){}
        Physics2D *getPhysics2D(){
            return physics2D;
        }

        //std::vector<Vector2D*> getVertices(){return vertices;}
        
        //list of points that confomr the picuture, worldpos
        std::vector<Vector2D*> vertices;

        std::vector<Vector2D*> normalEdgesList; 
    private:
        //purple
        Gizmos *upGizmos = Gizmos::StartGizmos(0.5f, 0.5f, 0.0f);
        // Set the color to orange (RGB: 1.0, 0.5, 0.0)
        Gizmos *rightGizmos = Gizmos::StartGizmos(1.0f, 0.5f, 0.0f);
        //
        Physics2D *physics2D = nullptr;
        
        


};