#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Board.h"

class GraphicsManager {
private:

	sf::RenderWindow* m_windowRef;
	sf::Font m_font;
	std::vector<sf::FloatRect> m_MainMenuButtonGlobalBounds;

public:
	GraphicsManager(sf::RenderWindow& t_window, sf::Font& t_font);

	void createButton(const std::string& text, const sf::Vector2f& position, float buttonWidth, float buttonHeight, sf::RectangleShape& buttonShape, sf::Text& buttonText);

	void RenderMainMenu();

	void HideUI();

	void RenderGameScene(Board& board);

	std::vector<sf::FloatRect> getMMGB() { return this->m_MainMenuButtonGlobalBounds;}
};