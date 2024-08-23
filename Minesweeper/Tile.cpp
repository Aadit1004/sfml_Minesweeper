#include "Tile.h"

Tile::Tile(bool t_isMine, sf::Vector2f size, sf::Vector2f position, sf::Font& t_font) : m_isMine(t_isMine), m_isRevealed(false), m_isFlagged(false), m_adjacentMines(0) {
    m_shape.setSize(size);
    sf::Color lightGray(211, 211, 211);
    m_shape.setFillColor(lightGray);
    m_shape.setOutlineThickness(1);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setPosition(position);

    m_text.setFont(t_font);
    m_text.setCharacterSize(static_cast<unsigned int>(size.y * 0.6f));
}

void Tile::setMine(bool t_isMine) {
    m_isMine = t_isMine;
    // m_shape.setFillColor(sf::Color::Red);
}

bool Tile::isMine() const {
    return m_isMine;
}

void Tile::setRevealed(bool t_isRevealed) {
    m_isRevealed = t_isRevealed;
    if (t_isRevealed) {
        sf::Color darkGray(120, 120, 120);
        m_shape.setFillColor(darkGray);
        // display number if between 1 and 8 inclusive
        m_text.setString(std::to_string(this->m_adjacentMines));
        sf::FloatRect textRect = m_text.getLocalBounds();
        m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        m_text.setPosition(
        m_shape.getPosition().x + m_shape.getSize().x / 2,
        m_shape.getPosition().y + m_shape.getSize().y / 2);
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
    if (this->m_adjacentMines >= 1 && this->m_adjacentMines <= 3) {
        m_text.setFillColor(sf::Color::Blue);
    }
    else if (this->m_adjacentMines <= 6) {
        m_text.setFillColor(sf::Color::Magenta);
    }
    else {
        m_text.setFillColor(sf::Color::Red);
    }
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

void Tile::render(sf::RenderWindow& window, GameState& currState) {
    if (currState == GameWin || currState == GameLose) {
        return;
    }
    window.draw(m_shape);
    if (m_isRevealed && m_adjacentMines > 0) {
        window.draw(m_text);
    }
}