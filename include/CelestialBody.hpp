#include <string>
#include "Vector3.hpp"

class CelestialBody{
private:
    std::string name;
    double mass;
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

public:
    CelestialBody(std::string n, double m, Vector3 ip, Vector3 iv) 
        : name(n), mass(m), position(ip), velocity(iv), acceleration(0.0, 0.0, 0.0) {
        }


    // Getter Functions
    const std::string& getName() const{
        return name;
    }

    double getMass() const{
        return mass;
    }
    
    /* 1st const Vector3&: Read-only reference to the existing vector
       2nd const: Guarantees that the function won't modify the object */
    const Vector3& getPosition() const{
        return position;
    }

    const Vector3& getVelocity() const{
        return velocity;
    }

    const Vector3& getAcceleration() const{
        return acceleration;
    }

    Vector3 calculateGravitationalAcceleration(const CelestialBody& other) const{
        constexpr double G = 6.67430e-11;

        Vector3 displacement = other.position - position;
        double distance = displacement.magnitude();

        // Return 0 vector to avoid division by 0
        if (distance == 0.0){
            return Vector3(0.0, 0.0, 0.0);
        }

        double accelerationMagnitude = (G * other.mass) / (distance * distance);

        Vector3 gravitationalAcceleration = displacement.normalized() * accelerationMagnitude;

        return gravitationalAcceleration;
    }

    void setAcceleration(const Vector3& newAcceleration){
        acceleration = newAcceleration;
    }

    void updateVelocity(double dt){
        Vector3 dv = acceleration * dt;

        velocity = velocity + dv;
    }

    void updatePosition(double dt){
        Vector3 dx = velocity * dt;

        position = position + dx;
    }


};