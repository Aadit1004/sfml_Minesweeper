#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "GraphicsManager.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Minesweeper - Aadit");
    GraphicsManager graphicsRender(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        // Clear screen
        window.clear();
        
        graphicsRender.RenderMainMenu();

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}