#pragma once
#include <SFML/Graphics.hpp>
#include "Vector3.hpp"

class Renderer2D{
private:
    sf::RenderWindow window{sf::VideoMode({1000, 800}), "Solar System Simulator"};

public:
    Renderer2D() = default;

    // Draw Sun
    sf::CircleShape sun{30.f};

    // Draw Earth
    sf::CircleShape earth{10.f};

    void run(){
        window.setFramerateLimit(60);
        while (window.isOpen()){

            // Processing window events using polling
            while (const auto event = window.pollEvent()){
                if (event->is<sf::Event::Closed>()){
                    window.close();
                }
            }
            // Clear the window to black
            window.clear(sf::Color::Black);

            sun.setFillColor(sf::Color::Yellow);
            earth.setFillColor(sf::Color::Blue);

            sun.setPosition({500.f, 400.f});
            earth.setPosition({750.f, 400.f});

            window.draw(sun);
            window.draw(earth);

            window.display();
        }
    }

    sf::Vector2f worldToScreen(const Vector3& position) const{
        double scaleFactor = 250.0 / 1.496e11;

        double screenX = 500.0 + (position.getX() * scaleFactor);
        double screenY = 400.0 - (position.getY() * scaleFactor);

        float x = static_cast<float>(screenX);
        float y = static_cast<float>(screenY);

        return sf::Vector2f(x, y);

    }
};