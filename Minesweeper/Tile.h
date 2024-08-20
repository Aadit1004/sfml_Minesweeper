#pragma once
#include <utility>

class Tile {
private:

	bool m_isMine;
	bool m_isRevealed;
	bool m_isFlagged;
	int m_adjacentMines;
	std::pair<int, int> position;

public:

	Tile(bool t_isMine);

	void setValue();

	void Reveal();

	void toggleFlag();

	void setPosition();
};