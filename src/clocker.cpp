#include "Clocker.h"


#include <iostream>

#include <vector>
#include <chrono>

#include <SDL.h>

//set nullptr to the clocker
Clocker * Clocker::s_Instance = nullptr;

//tick function on the main loop to get the deltatime
void Clocker::Tick()
{
    m_DeltaTime = (SDL_GetTicks() - m_LasTime) * (Target_FPS/1000.0f);

    //update the deltatie only if it is bigger that our desired deltatime
    if(m_DeltaTime > Target_DELTATIME){
        m_DeltaTime = Target_DELTATIME;
    }

    m_LasTime = SDL_GetTicks();

}