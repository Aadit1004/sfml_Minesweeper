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
	Board* m_gameBoard;
	sf::Font m_font;

	void handleMainMenu(sf::Vector2i mousePos);

	void handleInGame(sf::Vector2i mousePos);

	void handleLoseGame();

	void handleWinGame();

public:
	MouseEventHandler(sf::RenderWindow& t_window, GameState& currState, GraphicsManager* t_graphicsRender, sf::Font& t_font);

	void MouseClicked(sf::Vector2i t_mousePos);
};