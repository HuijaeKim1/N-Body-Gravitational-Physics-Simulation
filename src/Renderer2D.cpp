#include "Renderer2D.hpp"

// Constructor: Create the SFML window
Renderer2D::Renderer2D()
    : window(sf::VideoMode({1000, 800}), "Solar System Simulator") {

    window.setFramerateLimit(60);

    window.setKeyRepeatEnabled(false);

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


void Renderer2D::run(Simulation& simulation) {

    bool paused = false;

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

            // Detect space key and toggle paused
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->code == sf::Keyboard::Key::Space){
                    paused = !paused;
                }
            }
        }

        // Update physics if its not paused
        if (!paused){
            simulation.step(dt);
        }

        sf::VertexArray trail(sf::PrimitiveType::LineStrip);

        // Get Sun and Earth positions from the physics engine
        const Vector3& sunPosition = bodies[0].getPosition();
        const Vector3& earthPosition = bodies[1].getPosition();

        // Convert physics coordinates to pixel coordinates
        sf::Vector2f sunScreen = worldToScreen(sunPosition);
        sf::Vector2f earthScreen = worldToScreen(earthPosition);

        // Store Earth's current position
        earthTrail.push_back(earthScreen);
        
        if (earthTrail.size() > 2000) {
            earthTrail.erase(earthTrail.begin());
        }

        // Create vertexes and connect them to create the orbital route
        for (const sf::Vector2f& point : earthTrail){
            sf::Vertex vertex(point, sf::Color::Blue);
            trail.append(vertex);
        }

        // Update the visual positions
        sun.setPosition(sunScreen);
        earth.setPosition(earthScreen);

        // Clear the previous frame
        window.clear(sf::Color::Black);

        window.draw(trail);

        // Draw the celestial bodies
        window.draw(sun);
        window.draw(earth);
        
        window.display();
    }
}
