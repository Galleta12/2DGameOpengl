#include <iostream>

#include "MouseHandler.h"
#include "SDWINDOW.h"



MouseHandler::MousePress MouseHandler::mousePressEnum = MouseHandler::MousePress::NOLEFT;


MouseHandler::MouseHandler()
{}

MouseHandler::~MouseHandler(){}




void MouseHandler::mousePos(){

    
    
      if (SDWINDOW::event.type == SDL_MOUSEMOTION) {
        mousePosX = SDWINDOW::event.motion.x;
        mousePosY = SDWINDOW::event.motion.y;
        //std::cout<< "Mouse current X: " << mousePosX << "Mouse current y: " << mousePosY << std::endl;     

    }
    
    
    // if(SDWINDOW::event.type == SDL_MOUSEBUTTONDOWN){
    //     switch (SDWINDOW::event.button.button)
    //     {
    //     case SDL_BUTTON_LEFT:
    //         if(!ismouseleft){

    //             mouseClickX = SDWINDOW::event.button.x;
    //             mouseClickY = SDWINDOW::event.button.y;

    //             //std::cout<< "Mouse X: " << mouseClickX << "Mouse y: " << mouseClickY << std::endl;     
    //             ismouseleft = true;
    //             mousePressEnum = MousePress::ISLEFT;
    //         }
    //         break;
    //     case SDL_BUTTON_RIGHT:
            
    //         if(!ismouseRight){

    //             ismouseRight = true;
    //             mousePressEnum = MousePress::ISRIGHT;
    //         }

    //         break;
    //     default:
    //         break;
    //     }
    // }
    // if(SDWINDOW::event.type== SDL_MOUSEBUTTONUP){
    //     switch (SDWINDOW::event.button.button)
    //     {
    //     case SDL_BUTTON_LEFT:
    //         ismouseleft = false;
    //         mousePressEnum = MousePress::NOLEFT;
    //         break;
        
    //     case SDL_BUTTON_RIGHT:
    //         ismouseRight = false;
    //         mousePressEnum = MousePress::NORIGHT;

    //         break;
        
    //     default:
    //         break;
    //     }
    // }


}