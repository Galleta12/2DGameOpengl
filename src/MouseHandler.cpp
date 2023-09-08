#include <iostream>

#include "MouseHandler.h"
#include "SDWINDOW.h"

MouseHandler::MouseHandler()
{}

MouseHandler::~MouseHandler(){}




void MouseHandler::mousePos(){

    
    
      if (SDWINDOW::event.type == SDL_MOUSEMOTION) {
        mousePosX = SDWINDOW::event.motion.x;
        mousePosY = SDWINDOW::event.motion.y;
        //std::cout<< "Mouse current X: " << mousePosX << "Mouse current y: " << mousePosY << std::endl;     

    }
    
    
    if(SDWINDOW::event.type == SDL_MOUSEBUTTONDOWN){
        switch (SDWINDOW::event.button.button)
        {
        case SDL_BUTTON_LEFT:
            mouseClickX = SDWINDOW::event.button.x;
            mouseClickY = SDWINDOW::event.button.y;

            //std::cout<< "Mouse X: " << mouseClickX << "Mouse y: " << mouseClickY << std::endl;     

            break;
        case SDL_BUTTON_RIGHT:
            ismouseleft = true;
            break;
        default:
            break;
        }
    }
    ismouseleft = false;



}