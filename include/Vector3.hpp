#include <cmath>

class Vector3{
private:
    double x;
    double y;
    double z;

public:
    Vector3() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vector3(double x_, double y_, double z_)
        : x(x_), y(y_), z(z_){
        }
    
    // Vector Addition
    Vector3 operator+(const Vector3& other) const{
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Vector Subtraction
    Vector3 operator-(const Vector3& other) const{
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    
    // Scalar Multiplication
    Vector3 operator*(double scalar) const{
        return Vector3(scalar * x, scalar * y, scalar * z);
    }

    // Vector Magnitude
    double magnitude() const{
        return sqrt((x * x) + (y * y) + (z * z));
    }

    // Vector Normalization
    Vector3 normalized() const{
        double mag = magnitude();
        if (mag == 0.0){
            return Vector3(0.0, 0.0, 0.0);
        }
    
        return Vector3((x / mag), (y / mag), (z / mag));
    }

    // Return the X coordinate
    double getX() const {
        return x;
    }

    // Return the Y coordinate
    double getY() const {
        return y;
    }

    // Return the Z coordinate
    double getZ() const {
        return z;
    }


    
};