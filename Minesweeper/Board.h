#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <string> 
#include "GameManager.h"

class Board {
private:

	std::vector<std::vector<Tile>> m_grid;
	int m_numRows;
	int m_numCols;
	int m_numMines;
	sf::Font m_font;

	void revealTileHelper(int t_posX, int t_posY, sf::RenderWindow& t_window);

public:

	Board(int t_numRows, int t_numCols, int t_numMines, sf::Font& t_font);

	void generateBoard(sf::RenderWindow* t_windowRef);
	void placeMines();
	void calculateAdjacency();
	void revealTile(int t_posX, int t_posY, sf::RenderWindow& t_window, GameState& currState);
	bool checkWin() const;

	int getNumRows() { return this->m_numRows; }
	int getNumCols() { return this->m_numCols; }
	int getNumMines() { return this->m_numMines; }
	Tile getTile(int t_posX, int t_posY) { return this->m_grid[t_posX][t_posY];}

	void render(sf::RenderWindow& window);
};