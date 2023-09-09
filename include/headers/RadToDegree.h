#pragma once

#include <iostream>
#include <cmath>

class RadToDegree{


    private:
        //initialize static inside the class
        static constexpr float PI = 3.14159265358979323846f;
        //private constractor to prevent initialization      
        RadToDegree(){}
    public:

        static float convert(float angleRad){
            return (angleRad * 180.0f)/PI;
        }


};