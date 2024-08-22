#include "Tile.h"

Tile::Tile(bool t_isMine, sf::Vector2f size, sf::Vector2f position) : m_isMine(t_isMine), m_isRevealed(false), m_isFlagged(false), m_adjacentMines(0) {
    m_shape.setSize(size);
    sf::Color lightGray(211, 211, 211);
    m_shape.setFillColor(lightGray);
    m_shape.setOutlineThickness(1);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setPosition(position);
}

void Tile::setMine(bool t_isMine) {
    m_isMine = t_isMine;
}

bool Tile::isMine() const {
    return m_isMine;
}

void Tile::setRevealed(bool t_isRevealed) {
    m_isRevealed = t_isRevealed;
    if (t_isRevealed) {
        std::cout << this->m_adjacentMines << std::endl;
       
        // display number
        // if bomb, end game
        if (m_isMine) {
            m_shape.setFillColor(sf::Color::Red);
            // Handle Lose Game
        }
        else {
            sf::Color darkGray(120, 120, 120);
            m_shape.setFillColor(darkGray);
            // display number if between 1 and 8 inclusive
        }
    }
}

bool Tile::isRevealed() const {
    return m_isRevealed;
}

void Tile::toggleFlag() {
    m_isFlagged = !m_isFlagged;
    if (m_isFlagged) {
        // draw octagon on top of square
    }
    else {
        // remove octagon on top of square
    }
}

bool Tile::isFlagged() const {
    return m_isFlagged;
}

void Tile::setAdjacentMines(int t_adjacentMines) {
    m_adjacentMines = t_adjacentMines;
}

int Tile::getAdjacentMines() const {
    return m_adjacentMines;
}

void Tile::setPosition(int x, int y) {
    m_position = { x, y };
    // Update the shape's position based on the grid position
    m_shape.setPosition(static_cast<float>(x), static_cast<float>(y));
}

std::pair<int, int> Tile::getPosition() const {
    return m_position;
}

void Tile::render(sf::RenderWindow& window) {
    window.draw(m_shape);
}