#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "GraphicsManager.h"
#include <vector>
#include "Board.h"

class MouseEventHandler {
private:
	sf::RenderWindow* m_windowRef;
	GameState* m_currState;
	GraphicsManager* m_graphicsRender;

	void handleMainMenu(sf::Vector2i mousePos);

	void handleInGame();

	void handleLoseGame();

	void handleWinGame();

public:
	MouseEventHandler(sf::RenderWindow& t_window, GameState& currState, GraphicsManager* t_graphicsRender);

	void MouseClicked(sf::Vector2i t_mousePos);
};