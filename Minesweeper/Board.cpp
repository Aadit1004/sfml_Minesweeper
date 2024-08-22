#include "Board.h"

Board::Board(int t_numRows, int t_numCols, int t_numMines, sf::Font& t_font) : m_numRows(t_numRows), m_numCols(t_numCols), m_numMines(t_numMines), m_isGameEnded(false), m_font(t_font) {}

void Board::generateBoard(sf::RenderWindow* t_windowRef) {
    float tileSize;
    if (m_numMines == 10) {
        tileSize = 50.0f;
    } else if (m_numCols == 16) {
        tileSize = 35.0f;
    } else {
        tileSize = 26.0f;
    }
    float boardWidth = m_numCols * tileSize;
    float boardHeight = m_numRows * tileSize;

    float startX = (t_windowRef->getSize().x - boardWidth) / 2;
    float startY = (t_windowRef->getSize().y - boardHeight) / 2;

    m_grid.resize(m_numRows, std::vector<Tile>(m_numCols, Tile(false, { tileSize, tileSize }, { 0.0f, 0.0f }, this->m_font)));

    for (int row = 0; row < m_numRows; ++row) {
        for (int col = 0; col < m_numCols; ++col) {
            float x = startX + col * tileSize;
            float y = startY + row * tileSize;
            m_grid[row][col] = Tile(false, { tileSize, tileSize }, { x, y }, this->m_font);
        }
    }

    placeMines();
    calculateAdjacency();
}

void Board::placeMines() {
    int placedMines = 0;

    // set mines randomly accross board, no overlapping mines
    while (placedMines < m_numMines) {
        int row = rand() % m_numRows;
        int col = rand() % m_numCols;

        if (!m_grid[row][col].isMine()) {
            m_grid[row][col].setMine(true);
            placedMines++;
        }
    }
}

void Board::calculateAdjacency() {
    for (int row = 0; row < m_numRows; ++row) {
        for (int col = 0; col < m_numCols; ++col) {
            if (!m_grid[row][col].isMine()) {
                int adjacentMines = 0;

                // check 9x9 area for surrounding mines
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        int nRow = row + i;
                        int nCol = col + j;

                        if (nRow >= 0 && nRow < m_numRows && nCol >= 0 && nCol < m_numCols) {
                            if (m_grid[nRow][nCol].isMine()) {
                                adjacentMines++;
                            }
                        }
                    }
                }

                m_grid[row][col].setAdjacentMines(adjacentMines);
            }
        }
    }
}

void Board::revealTile(int t_posX, int t_posY, sf::RenderWindow& t_window) {
    if (t_posX >= 0 && t_posX < m_numRows && t_posY >= 0 && t_posY < m_numCols)
    {
        if (m_grid[t_posX][t_posY].isMine()) {
            // Handle Lose Game
            std::cout << "BOMB" << std::endl;
            return;
        }
        else {
            revealTileHelper(t_posX, t_posY, t_window);
        }
    }
}

void Board::revealTileHelper(int t_posX, int t_posY, sf::RenderWindow& t_window) {
    if (t_posX >= 0 && t_posX < m_numRows && t_posY >= 0 && t_posY < m_numCols) {
        if (!m_grid[t_posX][t_posY].isRevealed()) {
            m_grid[t_posX][t_posY].setRevealed(true);
            m_grid[t_posX][t_posY].render(t_window);

            if (m_grid[t_posX][t_posY].getAdjacentMines() == 0) {
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        revealTileHelper(t_posX + i, t_posY + j, t_window);
                    }
                }
            }
        }
    }
}

bool Board::checkWin() const {
    return this->m_isGameEnded;
}

void Board::render(sf::RenderWindow& window) {
    for (int row = 0; row < m_numRows; ++row) {
        for (int col = 0; col < m_numCols; ++col) {
            m_grid[row][col].render(window);
        }
    }
}