#include "Simulation.hpp"


// Return a read-only reference to the bodies vector
const std::vector<CelestialBody>& Simulation::getBodies() const {
    return bodies;
}

// Add a new celestial body to the simulation
void Simulation::addBody(const CelestialBody& body) {
    bodies.push_back(body);
}

// Calculate the gravitational acceleration of every body
void Simulation::calculateAccelerations() {

    // Outer loop: select the body experiencing acceleration
    for (std::size_t i = 0; i < bodies.size(); i++) {

        Vector3 totalAcceleration(0.0, 0.0, 0.0);

        // Inner loop: calculate gravity from every other body
        for (std::size_t j = 0; j < bodies.size(); j++) {

            // A body should not gravitationally interact with itself
            if (i == j) {
                continue;
            }

            // Calculate acceleration of body i caused by body j
            Vector3 objectAcceleration =
                bodies[i].calculateGravitationalAcceleration(bodies[j]);

            // Add this contribution to the total acceleration
            totalAcceleration = totalAcceleration + objectAcceleration;
        }

        // Save the total acceleration of body i
        bodies[i].setAcceleration(totalAcceleration);
    }
}

// Advance the simulation by dt seconds
void Simulation::step(double dt) {

    // Calculate acceleration before moving any bodies
    calculateAccelerations();

    // Update the velocity of every body
    for (CelestialBody& body : bodies) {
        body.updateVelocity(dt);
    }

    // Update positions using the updated velocities
    for (CelestialBody& body : bodies) {
        body.updatePosition(dt);
    }
}
