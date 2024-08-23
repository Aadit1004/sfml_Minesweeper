#pragma once
#include <utility>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameManager.h"

class Tile {
private:

	bool m_isMine;
	bool m_isRevealed;
	bool m_isFlagged;
	int m_adjacentMines;
	std::pair<int, int> m_position; // (row, column)

	sf::RectangleShape m_shape; // Shape for rendering the tile

    sf::Text m_text;

public:

    Tile(bool t_isMine, sf::Vector2f size, sf::Vector2f position, sf::Font& t_font);

    void setMine(bool t_isMine);
    bool isMine() const;

    void setRevealed(bool t_isRevealed);
    bool isRevealed() const;

    void toggleFlag();
    bool isFlagged() const;

    void setAdjacentMines(int t_adjacentMines);
    int getAdjacentMines() const;

    void setPosition(int x, int y);
    std::pair<int, int> getPosition() const;

    void render(sf::RenderWindow& window, GameState& currState);
};