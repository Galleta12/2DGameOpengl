#pragma once

const int Target_FPS = 144;
const float Target_DELTATIME = 1.5f;

class Clocker
{

    public:
        
        void Tick();
        inline float GetDelatTime(){return m_DeltaTime;}
        inline static Clocker* GetInstance(){return s_Instance = (s_Instance !=nullptr)? s_Instance : new Clocker();}


    private:
        Clocker(){}
        //singleton, we only want one instace
        static Clocker* s_Instance;
        
        float m_DeltaTime;
        float m_LasTime;


};