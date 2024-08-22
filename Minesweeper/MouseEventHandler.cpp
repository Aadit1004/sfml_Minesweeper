#include "MouseEventHandler.h"

MouseEventHandler::MouseEventHandler(sf::RenderWindow& t_window, GameState& currState, GraphicsManager* t_graphicsRender, sf::Font& t_font) : m_gameBoard(nullptr), m_font(t_font) {
	this->m_windowRef = &t_window;
	this->m_currState = &currState;
	this->m_graphicsRender = t_graphicsRender;
}

void MouseEventHandler::MouseClicked(sf::Vector2i t_mousePos) {
	// std::cout << "Mouse clicked at: " << t_mousePos.x << ", " << t_mousePos.y << std::endl;
	switch (*this->m_currState) {
	case MainMenu:
		this->handleMainMenu(t_mousePos);
		break;
	case InGame:
		this->handleInGame(t_mousePos);
		break;
	case GameLose:
		this->handleLoseGame();
		break;
	case GameWin:
		this->handleWinGame();
		break;
	}
}

void MouseEventHandler::handleMainMenu(sf::Vector2i t_mousePos) {
	// gets main menu global bounds for buttons
	std::vector<sf::FloatRect> MMGB = this->m_graphicsRender->getMMGB();

	if (MMGB[0].contains(static_cast<float>(t_mousePos.x), static_cast<float>(t_mousePos.y))) {
		std::cout << "Easy button selected" << std::endl; 
		*this->m_currState = InGame;
		this->m_graphicsRender->HideUI();
		// To-do: generate board with easy mode
		this->m_gameBoard = new Board(9, 9, 10, this->m_font);
		this->m_gameBoard->generateBoard(this->m_windowRef);
		this->m_gameBoard->render(*this->m_windowRef);
	}

	if (MMGB[1].contains(static_cast<float>(t_mousePos.x), static_cast<float>(t_mousePos.y))) {
		std::cout << "Medium button selected" << std::endl;
		*this->m_currState = InGame;
		this->m_graphicsRender->HideUI();
		// To-do: generate board with medium mode
		this->m_gameBoard = new Board(16, 16, 40, this->m_font);
		this->m_gameBoard->generateBoard(this->m_windowRef);
		this->m_gameBoard->render(*this->m_windowRef);
	}

	if (MMGB[2].contains(static_cast<float>(t_mousePos.x), static_cast<float>(t_mousePos.y))) {
		std::cout << "Hard button selected" << std::endl;
		*this->m_currState = InGame;
		this->m_graphicsRender->HideUI();
		// To-do: generate board with hard mode
		this->m_gameBoard = new Board(22, 22, 99, this->m_font);
		this->m_gameBoard->generateBoard(this->m_windowRef);
		this->m_gameBoard->render(*this->m_windowRef);
	}
}

void MouseEventHandler::handleInGame(sf::Vector2i t_mousePos) {
	// check if hit on grid
	float tileSize;
	if (this->m_gameBoard->getNumMines() == 10) {
		tileSize = 50.0f;
	}
	else if (this->m_gameBoard->getNumMines() == 40) {
		tileSize = 35.0f;
	}
	else {
		tileSize = 26.0f;
	}
	float startX = (this->m_windowRef->getSize().x - this->m_gameBoard->getNumCols() * tileSize) / 2;
	float startY = (this->m_windowRef->getSize().y - this->m_gameBoard->getNumRows() * tileSize) / 2;

	// Check if the click is within the grid bounds
	if (t_mousePos.x >= startX && t_mousePos.x <= startX + this->m_gameBoard->getNumCols() * tileSize &&
		t_mousePos.y >= startY && t_mousePos.y <= startY + this->m_gameBoard->getNumRows() * tileSize) {

		// Calculate row and column of the clicked tile
		int col = (t_mousePos.x - startX) / tileSize;
		int row = (t_mousePos.y - startY) / tileSize;

		// std::cout << "Tile clicked at row: " << row << ", col: " << col << std::endl;

		if (row >= 0 && row < this->m_gameBoard->getNumRows() && col >= 0 && col < this->m_gameBoard->getNumCols()) {
			this->m_gameBoard->revealTile(row, col, *this->m_windowRef);
			this->m_gameBoard->getTile(row, col).render(*this->m_windowRef);
		}

		/*this->m_gameBoard->revealTile(row, col, *this->m_windowRef); 
		this->m_gameBoard->getTile(row, col).render(*this->m_windowRef);*/
	}
	
}
  
void MouseEventHandler::handleLoseGame() {
	// check if hit backToMainMenu button
	this->m_gameBoard = nullptr;
}

void MouseEventHandler::handleWinGame() {
	// check if hit backToMainMenu button
	this->m_gameBoard = nullptr;
}