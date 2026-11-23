#pragma once

#include <vector>
#include "CelestialBody.hpp"

class Simulation {
private:
    std::vector<CelestialBody> bodies;

public:
    Simulation() = default;

    void addBody(const CelestialBody& body);
    void calculateAccelerations();
    void step(double dt);

    const std::vector<CelestialBody>& getBodies() const;
};