#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "GraphicsManager.h"
#include "MouseEventHandler.h"
#include <filesystem>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Minesweeper - Aadit");
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/mine-sweeper.ttf"))
    {
        // std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        std::cout << "font unable to load" << std::endl;
        return EXIT_FAILURE;
    }

    GameManager gameManager();
    GraphicsManager graphicsRender(window, font);
    GameState currState = MainMenu;
    MouseEventHandler mouseEventHandler(window, currState, &graphicsRender);
    
    window.clear(sf::Color::White);
    graphicsRender.RenderMainMenu();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mouseEventHandler.MouseClicked(sf::Mouse::getPosition(window));
            }
        }
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}