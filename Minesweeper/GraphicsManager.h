#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class GraphicsManager {
private:

	sf::RenderWindow* m_windowRef;

public:
	GraphicsManager(sf::RenderWindow& t_window);

	void RenderMainMenu();

	void HideMainMenu();

	void RenderGameScene();

	void hideGameScene();
};