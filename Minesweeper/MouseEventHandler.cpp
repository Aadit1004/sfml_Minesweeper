#include "MouseEventHandler.h"

MouseEventHandler::MouseEventHandler(sf::RenderWindow& t_window, GameState& currState, GraphicsManager* t_graphicsRender) {
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
		this->handleInGame();
		break;
	case GameLose:
		this->handleLoseGame();
		break;
	case GameWin:
		this->handleWinGame();
		break;
	}
}

void MouseEventHandler::handleMainMenu(sf::Vector2i mousePos) {
	// gets main menu global bounds for buttons
	std::vector<sf::FloatRect> MMGB = this->m_graphicsRender->getMMGB();

	if (MMGB[0].contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		std::cout << "Easy button selected" << std::endl; 
		*this->m_currState = InGame;
		this->m_graphicsRender->HideUI();
		// To-do: generate board with easy mode
		auto* gameBoard = new Board(9, 9, 10);
		gameBoard->generateBoard(this->m_windowRef);
		gameBoard->render(*this->m_windowRef);
	}

	if (MMGB[1].contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		std::cout << "Medium button selected" << std::endl;
		*this->m_currState = InGame;
		this->m_graphicsRender->HideUI();
		// To-do: generate board with medium mode
		auto* gameBoard = new Board(16, 16, 40);
		gameBoard->generateBoard(this->m_windowRef);
		gameBoard->render(*this->m_windowRef);
	}

	if (MMGB[2].contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		std::cout << "Hard button selected" << std::endl;
		*this->m_currState = InGame;
		this->m_graphicsRender->HideUI();
		// To-do: generate board with hard mode
		auto* gameBoard = new Board(22, 22, 99);
		gameBoard->generateBoard(this->m_windowRef);
		gameBoard->render(*this->m_windowRef);
	}
}

void MouseEventHandler::handleInGame() {
	// check if hit on grid

}
  
void MouseEventHandler::handleLoseGame() {
	// check if hit backToMainMenu button
}

void MouseEventHandler::handleWinGame() {
	// check if hit backToMainMenu button
}