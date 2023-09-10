#pragma once
#include <vector>


class MouseHandler{


    public:
        
        static enum MousePress{
            ISLEFT,
            NOLEFT,
            ISRIGHT,
            NORIGHT,

        };

        
        MouseHandler();
        
        ~MouseHandler();
        
        static MousePress mousePressEnum;
        
        
        void mousePos();

        std::vector<int> getMouseClikPos(){

            return {mouseClickX, mouseClickY};
        }
        std::vector<int> getMousePos(){

            return {mousePosX, mousePosY};
        }
        bool getIsMouseLeft(){

            return ismouseleft;
        }


    private:
        int mouseClickX, mouseClickY, mousePosX, mousePosY;
        bool ismouseleft=false;
        bool ismouseRight = false;

};