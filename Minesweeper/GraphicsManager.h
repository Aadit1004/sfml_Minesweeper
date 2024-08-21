#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class GraphicsManager {
private:

	sf::RenderWindow* m_windowRef;
	sf::Font m_font;

public:
	GraphicsManager(sf::RenderWindow& t_window, sf::Font& t_font);

	void createButton(const std::string& text, const sf::Vector2f& position, float buttonWidth, float buttonHeight, sf::RectangleShape& buttonShape, sf::Text& buttonText);

	void RenderMainMenu();

	void HideUI();

	void RenderGameScene();
};