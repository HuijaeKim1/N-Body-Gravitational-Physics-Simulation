#include "Renderer2D.hpp"

// Constructor: Create the SFML window
Renderer2D::Renderer2D()
    : window(sf::VideoMode({1000, 800}), "Solar System Simulator") {

    // Limit rendering to 60 frames per second
    window.setFramerateLimit(60);

    // Set planet colors
    sun.setFillColor(sf::Color::Yellow);
    earth.setFillColor(sf::Color::Blue);

    // Set origins to the centers of the circles
    sun.setOrigin({30.f, 30.f});
    earth.setOrigin({10.f, 10.f});
}

// Convert physics coordinates (meters) to screen coordinates (pixels)
sf::Vector2f Renderer2D::worldToScreen(const Vector3& position) const {

    // Earth-Sun distance corresponds to 250 pixels
    double scaleFactor = 250.0 / 1.496e11;

    // Convert world position to screen position
    double screenX = 500.0 + position.getX() * scaleFactor;
    double screenY = 400.0 - position.getY() * scaleFactor;

    // SFML uses floats for drawing coordinates
    float x = static_cast<float>(screenX);
    float y = static_cast<float>(screenY);

    return sf::Vector2f(x, y);
}

double dt = 21600.0;

// Main graphical application loop
void Renderer2D::run(Simulation& simulation) {

    // Access the celestial bodies stored in the simulation
    const std::vector<CelestialBody>& bodies = simulation.getBodies();

    // Main rendering loop
    while (window.isOpen()) {

        // Process window events
        while (const auto event = window.pollEvent()) {

            // Close the window when the X button is pressed
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        simulation.step(dt);

        // Get Sun and Earth positions from the physics engine
        const Vector3& sunPosition = bodies[0].getPosition();
        const Vector3& earthPosition = bodies[1].getPosition();

        // Convert physics coordinates to pixel coordinates
        sf::Vector2f sunScreen = worldToScreen(sunPosition);
        sf::Vector2f earthScreen = worldToScreen(earthPosition);

        // Update the visual positions
        sun.setPosition(sunScreen);
        earth.setPosition(earthScreen);

        // Clear the previous frame
        window.clear(sf::Color::Black);

        // Draw the celestial bodies
        window.draw(sun);
        window.draw(earth);

        // Display the finished frame
        window.display();
    }
}
