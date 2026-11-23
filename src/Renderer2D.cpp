#pragma once
#include <SFML/Graphics.hpp>

class Renderer2D {
private:
    sf::RenderWindow window;

public:
    Renderer2D();
    void run();
};