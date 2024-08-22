#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Board {
private:

	std::vector<std::vector<Tile>> m_grid;
	int m_numRows;
	int m_numCols;
	int m_numMines;
	bool m_isGameEnded;

public:

	Board(int t_numRows, int t_numCols, int t_numMines);

	void generateBoard(sf::RenderWindow* t_windowRef);
	void placeMines();
	void calculateAdjacency();
	void revealTile(int t_posX, int t_posY);
	bool checkWin() const;

	void render(sf::RenderWindow& window);
};