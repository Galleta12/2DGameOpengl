#pragma once

#include <iostream>
#include <cmath>

class RadToDegree{


    private:
        //private constractor to prevent initialization      
        RadToDegree(){}
    public:
        //initialize static inside the class
        static constexpr float PI = 3.14159265358979323846f;

        static float convert(float angleRad){
            return (angleRad * 180.0f)/PI;
        }


};