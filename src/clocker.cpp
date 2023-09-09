#include "Clocker.h"


#include <iostream>

#include <vector>
#include <chrono>

#include <SDL.h>


Clocker * Clocker::s_Instance = nullptr;


void Clocker::Tick()
{
    m_DeltaTime = (SDL_GetTicks() - m_LasTime) * (Target_FPS/1000.0f);

    if(m_DeltaTime > Target_DELTATIME){
        m_DeltaTime = Target_DELTATIME;
    }

    m_LasTime = SDL_GetTicks();

}