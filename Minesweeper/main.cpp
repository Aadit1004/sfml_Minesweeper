#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "GraphicsManager.h"

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

    GraphicsManager graphicsRender(window, font);

    GameState currState = MainMenu;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                std::cout << "Mouse clicked at: " << mousePos.x << ", " << mousePos.y << std::endl;
            }
        }

        // Clear screen
        window.clear(sf::Color::White);
        
        switch (currState) {
        case MainMenu:
            graphicsRender.RenderMainMenu();
            break;
        case InGame:
            break;
        case GameLose:
            break;
        case GameWin:
            break;
        }

        // check LMB button click based on currState

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}