#include <iostream>
#include <SFML/Audio.hpp>
#include "SFML/Graphics.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        sf::CircleShape circle;
        circle.setRadius(50);
        circle.setOutlineColor(sf::Color::Red);
        circle.setOutlineThickness(5);
        // Set the origin to the center of the circle
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        // Position the circle in the center of the window
        circle.setPosition(window.getSize().x / 2, window.getSize().y / 2);
        window.draw(circle);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}