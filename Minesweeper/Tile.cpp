#include "Tile.h"

Tile::Tile(bool t_isMine) {
	this->m_adjacentMines = 0;
	this->m_isFlagged = false;
	this->m_isMine = t_isMine;
	this->m_isRevealed = false;
	this->position.first = -1;
	this->position.second = -1;
}

void Tile::setValue() {

}


void Tile::Reveal() {

}

void Tile::toggleFlag() {

}

void Tile::setPosition() {

}