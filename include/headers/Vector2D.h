#pragma once
#include <iostream>

//#define _USE_MATH_DEFINES
#include <cmath>


class Vector2D{


    public:

        
        float x,y;

        Vector2D();
        Vector2D(float x, float y);

        ~Vector2D();



        Vector2D& Add(const Vector2D& vec);
        Vector2D& Substract(const Vector2D& vec);
        Vector2D& Multiply(const Vector2D& vec);
        Vector2D& Divide(const Vector2D& vec);

        
        //operator overload
        friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);
        
        
        //we want the same but for accumulations operators
        Vector2D& operator+=(const Vector2D& vec);
        Vector2D& operator-=(const Vector2D& vec);
        Vector2D& operator*=(const Vector2D& vec);
        Vector2D& operator/=(const Vector2D& vec);

        Vector2D& operator*(const int& i);
        Vector2D& Zero();
        
        //normalize
        Vector2D& Normalize();
        
        
        //static vector multiplication to avoid refernece problems
        static Vector2D Addition(const Vector2D& v1, const Vector2D& v2);
        static Vector2D Substraction(const Vector2D& v1, const Vector2D& v2);
        static Vector2D Multiplication(const Vector2D& v1, const Vector2D& v2);
        static Vector2D Divition(const Vector2D& v1, const Vector2D& v2);
        static Vector2D ScalarMultiplication(const Vector2D& v1, float scalar);
        
        
        
        //vector angle
        static float Angle(const Vector2D& v1, const Vector2D& v2);
        
        static Vector2D Normalized(const Vector2D& v1);

        //maginute
        float Magnitude() const;

        //this can be static since it doesnt depend on a instance of a vector object
        static float Dot(const Vector2D& v1, const Vector2D& v2);

        static float SignedAngle(const Vector2D& v1, const Vector2D& v2);


        static float DistanceVec(const Vector2D& v1, const Vector2D& v2);

        static Vector2D Reflection(const Vector2D& v1, const Vector2D& v2);
        
        static Vector2D NormalSuperfice(Vector2D v1, Vector2D v2);
        static Vector2D NormalSuperficeNoNormalized(Vector2D v1, Vector2D v2);
        static Vector2D PositionBetween(Vector2D& a, Vector2D& b);    
        static Vector2D InvertVector(Vector2D& a);    
        //clean way to print the vectors
        friend std::ostream& operator <<(std::ostream& stream, const Vector2D& vec);


};