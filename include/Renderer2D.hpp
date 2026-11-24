#pragma once

#include <SFML/Graphics.hpp>
#include "Simulation.hpp"

class Renderer2D {
private:
    // SFML window
    sf::RenderWindow window;

    // Celestial body shapes
    sf::CircleShape sun{30.f};
    sf::CircleShape earth{10.f};

    // Convert physical coordinates (meters) to screen coordinates (pixels)
    sf::Vector2f worldToScreen(const Vector3& position) const;

    // For orbital trails
    std::vector<sf::Vector2f> earthTrail;

public:
    Renderer2D();

    // Run the graphical application
    void run(Simulation& simulation);
};