#include "Board.h"

Board::Board(int t_numRows, int t_numCols, int t_numMines, sf::Font& t_font) : m_numRows(t_numRows), m_numCols(t_numCols), m_numMines(t_numMines), m_font(t_font) {
    this->backToMMglobalBounds = sf::FloatRect();
}

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
    srand(static_cast<unsigned int>(time(0)));
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

void Board::revealTile(int t_posX, int t_posY, sf::RenderWindow& t_window, GameState& currState) {
    if (currState == GameWin || currState == GameLose) {
        return;
    }
    if (t_posX >= 0 && t_posX < m_numRows && t_posY >= 0 && t_posY < m_numCols)
    {
        if (m_grid[t_posX][t_posY].isMine()) {
            // Handle Lose Game
            std::cout << "BOMB" << std::endl;
            currState = GameLose;
            createEndGameScreen(t_window, "GAME LOSE");
        }
        else {
            revealTileHelper(t_posX, t_posY, t_window, currState);
            for (int i = 0; i < 100; i++) { continue; }
            if (checkWin()) {
                currState = GameWin;
                std::cout << "GAME WIN" << std::endl; 
                createEndGameScreen(t_window, "GAME WIN");
            }
        }
    }
}

void Board::createEndGameScreen(sf::RenderWindow& t_window, std::string t_text) {
    sf::Text endText;
    endText.setFont(this->m_font);
    endText.setString(t_text);
    endText.setCharacterSize(30);
    endText.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = endText.getLocalBounds();
    endText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    endText.setPosition(sf::Vector2f(400.0f, 300.0f - 100.0f));
    
    t_window.clear(sf::Color::White);
    t_window.draw(endText);

    float buttonWidth = 300.0f;
    float buttonHeight = 75.0f;
    sf::RectangleShape buttonShape;
    buttonShape.setFillColor(sf::Color::Black);
    buttonShape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    buttonShape.setOrigin(buttonWidth / 2, buttonHeight / 2);
    buttonShape.setPosition(sf::Vector2f(400.0f, 300.0f + 100.0f));

    sf::Text ButtonText;
    ButtonText.setFont(this->m_font);
    ButtonText.setString("Back to main menu");
    ButtonText.setCharacterSize(17);
    ButtonText.setFillColor(sf::Color::White);
    sf::FloatRect textRectTwo = ButtonText.getLocalBounds();
    ButtonText.setOrigin(textRectTwo.left + textRectTwo.width / 2.0f, textRectTwo.top + textRectTwo.height / 2.0f);
    ButtonText.setPosition(sf::Vector2f(400.0f, 300.0f + 100.0f));

    this->backToMMglobalBounds = buttonShape.getGlobalBounds();
    t_window.draw(buttonShape);
    t_window.draw(ButtonText);
}

void Board::revealTileHelper(int t_posX, int t_posY, sf::RenderWindow& t_window, GameState& currState) {
    if (t_posX >= 0 && t_posX < m_numRows && t_posY >= 0 && t_posY < m_numCols) {
        if (!m_grid[t_posX][t_posY].isRevealed()) {
            m_grid[t_posX][t_posY].setRevealed(true);
            m_grid[t_posX][t_posY].render(t_window, currState);

            if (m_grid[t_posX][t_posY].getAdjacentMines() == 0) {
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        revealTileHelper(t_posX + i, t_posY + j, t_window, currState);
                    }
                }
            }
        }
    }
}

bool Board::checkWin() const {
    int revealedCount = 0;
    int nonMineTiles = m_numRows * m_numCols - m_numMines;

    for (int row = 0; row < m_numRows; ++row) {
        for (int col = 0; col < m_numCols; ++col) {
            if (m_grid[row][col].isRevealed() && !m_grid[row][col].isMine()) {
                revealedCount++;
            }
        }
    }
    return (revealedCount == nonMineTiles);
}

void Board::render(sf::RenderWindow& window, GameState& currState) {
    if (currState == GameWin || currState == GameLose) {
        return;
    }

    for (int row = 0; row < m_numRows; ++row) {
        for (int col = 0; col < m_numCols; ++col) {
            m_grid[row][col].render(window, currState);
        }
    }
}