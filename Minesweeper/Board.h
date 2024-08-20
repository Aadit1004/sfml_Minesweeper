#pragma once
#include <vector>
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

	void generateBoard();

	void placeMines();

	void calculateAdjacency();

	// Reveal the tile and recursively reveal adjacent tiles if no adjacent mines
	void revealTile(int t_posX, int t_posY);

	bool checkWin(); // return m_isGameEnded,maybe check if win or not
};