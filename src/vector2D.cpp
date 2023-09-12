#include "Vector2D.h"

#include "RadToDegree.h"



Vector2D::Vector2D():x(0.0f),y(0.0f){}


Vector2D::Vector2D(float x, float y){
    this->x=x;
    this->y=y;

}

Vector2D::~Vector2D()
{
}






Vector2D& Vector2D::Add(const Vector2D& vec){
    this->x += vec.x;
    this->y += vec.y;


    //return the vector that we got
    return *this;

}
Vector2D& Vector2D::Substract(const Vector2D& vec){
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;


//return the vector that we got
}

Vector2D& Vector2D::Multiply(const Vector2D& vec){
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;


//return the vector that we got
}
Vector2D& Vector2D::Divide(const Vector2D& vec){
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;


//return the vector that we got
}

//do the operator overloader

Vector2D& operator+(Vector2D& v1, const Vector2D& v2){
    return v1.Add(v2);
}
Vector2D& operator-(Vector2D& v1, const Vector2D& v2){
    return v1.Substract(v2);
}
Vector2D& operator*(Vector2D& v1, const Vector2D& v2){
    return v1.Multiply(v2);
}
Vector2D& operator/(Vector2D& v1, const Vector2D& v2){
    return v1.Divide(v2);
}




Vector2D& Vector2D::operator+=(const Vector2D& vec){
    return this->Add(vec);
  }
Vector2D& Vector2D::operator-=(const Vector2D& vec){
    return this->Substract(vec);
  }
Vector2D& Vector2D::operator*=(const Vector2D& vec){
    return this->Multiply(vec);
  }
Vector2D& Vector2D::operator/=(const Vector2D& vec){
    return this->Divide(vec);
  }


Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}



Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}



Vector2D& Vector2D::Normalize()
{
    float magnitude = this->Magnitude();

    //unit vector
    this->x = this->x / magnitude;
    this->y = this->y / magnitude;
    
    return *this;
}

Vector2D Vector2D::Addition(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(v1.x + v2.x,v1.y+v2.y);
}

Vector2D Vector2D::Substraction(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(v1.x - v2.x, v1.y- v2.y);
}

Vector2D Vector2D::Multiplication(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(v1.x * v2.x,v1.y *v2.y);
}

Vector2D Vector2D::Divition(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(v1.x / v2.x,v1.y / v2.y);
}

Vector2D Vector2D::ScalarMultiplication(const Vector2D &v1, float scalar)
{
    return Vector2D(v1.x * scalar, v1.y * scalar);
}

float Vector2D::Angle(const Vector2D &v1, const Vector2D &v2)
{
    
    
    //std::cout << "Angle being call"  << std::endl;
    //firt the dot product
    float dotProduct =Vector2D::Dot(v1,v2);

    //std::cout << "dot product" << dotProduct << std::endl;
    //multiplicaiton of their magnitudes
    float magnitude1 = v1.Magnitude();
    float magnitude2 = v2.Magnitude();
    
    float angleRad = std::acos(dotProduct/(magnitude1 * magnitude2));
    //convert into degrees
    float angleDeg = RadToDegree::convert(angleRad);
    
    //float angleDegRounded = std::round(angleDeg * 100.0f)/100.0f;

    return angleDeg;
}

Vector2D Vector2D::Normalized(const Vector2D& v1)
{
    float magnitud = v1.Magnitude();
    float x = v1.x / magnitud;
    float y = v1.y / magnitud;
    
    return Vector2D(x,y);
}

float Vector2D::Magnitude() const
{
    
    //std::cout << "Magnitude"  << std::endl;
    return std::sqrt((this->x * this->x) + (this->y * this->y));
}


float Vector2D::Dot(const Vector2D &v1, const Vector2D &v2)
{
    /*std::cout << "dot calls"  << std::endl;
    std::cout << "this vi: "  <<v1  << std::endl;
    std::cout << "this v2: " << v2  << std::endl;*/
    
    float dotProduct = (v1.x * v2.x) + (v1.y * v2.y); 
    
    return dotProduct;
}
float Vector2D::SignedAngle(const Vector2D &v1, const Vector2D &v2)
{
    // Calculate the dot product
    float dotProduct = Vector2D::Dot(v1, v2);

    // Calculate the magnitudes of v1 and v2
    float magnitude1 = v1.Magnitude();
    float magnitude2 = v2.Magnitude();

    // Calculate the angle in radians
    float angleRad = std::acos(dotProduct / (magnitude1 * magnitude2));

    // Calculate the sign of the angle using the cross product (z-component)
    float crossProduct = v1.x * v2.y - v1.y * v2.x;
    if (crossProduct < 0.0f) {
        angleRad = -angleRad; // Negative angle for clockwise rotation
    }

    // Convert the angle into degrees
    float angleDeg = RadToDegree::convert(angleRad);

    return angleDeg;
}




float Vector2D::DistanceVec(const Vector2D& v1, const Vector2D& v2)
{
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;

    return std::sqrt((dx * dx) + (dy * dy));
}

Vector2D Vector2D::Reflection(const Vector2D& v1, const Vector2D& v2)
{
    Vector2D reflection;
    //formula, the normal should be normalize, the normal is v2
    Vector2D normal = v2;
    //c(v1) - 2(c:n)n
    float dotProduct = Vector2D::Dot(v1,normal);
    Vector2D scalarProducts =  Vector2D::ScalarMultiplication(normal,dotProduct) * 2.0f ;
    
    reflection = Vector2D::Substraction(v1,scalarProducts);

    return reflection;
}

Vector2D Vector2D::NormalSuperfice(Vector2D v1, Vector2D v2)
{
    Vector2D r = v2 - v1;    
    //flip
    float tempX = r.x;
    r.x = -r.y;
    r.y = tempX;
    
    return r.Normalize();

}
Vector2D Vector2D::NormalSuperficeNoNormalized(Vector2D v1, Vector2D v2)
{
    Vector2D r = v2 - v1;    
    //flip
    float tempX = r.x;
    r.x = -r.y;
    r.y = tempX;
    
    return r;
}

Vector2D Vector2D::PositionBetween(Vector2D &a, Vector2D &b)
{
    float x = (a.x + b.x) * 0.5f;
    float y = (a.y + b.y) * 0.5f;
    return Vector2D(x, y);
}


std::ostream& operator <<(std::ostream& stream, const Vector2D& vec){
    stream << "Vector2D(" << vec.x << "," << vec.y << ")";
    return stream;
}
