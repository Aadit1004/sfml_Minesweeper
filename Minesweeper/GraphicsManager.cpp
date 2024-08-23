#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(sf::RenderWindow& t_window, sf::Font& t_font) {
    this->m_windowRef = &t_window;
    this->m_font = t_font;
}

void GraphicsManager::createButton(const std::string& t_text, const sf::Vector2f& t_position, float buttonWidth, float buttonHeight, sf::RectangleShape& buttonShape, sf::Text& buttonText) {
    buttonShape.setFillColor(sf::Color::Black);
    buttonShape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    buttonShape.setOrigin(buttonWidth / 2, buttonHeight / 2);
    buttonShape.setPosition(t_position);

    buttonText.setFont(this->m_font);
    buttonText.setString(t_text);
    buttonText.setCharacterSize(22);
    buttonText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(t_position);
}

void GraphicsManager::RenderMainMenu() {
    const float buttonWidth = 150.0f;
    const float buttonHeight = 75.0f;

    // Title
    sf::Text TitleTxt;
    TitleTxt.setFont(this->m_font);
    TitleTxt.setString("Minesweeper");
    TitleTxt.setCharacterSize(40);
    TitleTxt.setFillColor(sf::Color::Black);
    sf::FloatRect textRectTitle = TitleTxt.getLocalBounds();
    TitleTxt.setOrigin(textRectTitle.left + textRectTitle.width / 2.0f, textRectTitle.top + textRectTitle.height / 2.0f);
    TitleTxt.setPosition(m_windowRef->getSize().x / 2, 100);

    // Button labels and positions
    std::vector<std::pair<std::string, sf::Vector2f>> buttonInfo = {
        {"Easy", sf::Vector2f(m_windowRef->getSize().x / 2, m_windowRef->getSize().y / 2 - 50)},
        {"Medium", sf::Vector2f(m_windowRef->getSize().x / 2, m_windowRef->getSize().y / 2 + 50)},
        {"Hard", sf::Vector2f(m_windowRef->getSize().x / 2, m_windowRef->getSize().y / 2 + 150)}
    };

    std::vector<sf::RectangleShape> buttons(buttonInfo.size());
    std::vector<sf::Text> buttonTexts(buttonInfo.size());

    for (size_t i = 0; i < buttonInfo.size(); ++i) {
        createButton(buttonInfo[i].first, buttonInfo[i].second, buttonWidth, buttonHeight, buttons[i], buttonTexts[i]);
    }

    m_windowRef->draw(TitleTxt);

    if (!this->m_MainMenuButtonGlobalBounds.empty()) {
        this->m_MainMenuButtonGlobalBounds.clear();
    }
    for (size_t i = 0; i < buttons.size(); ++i) {
        m_windowRef->draw(buttons[i]);
        m_windowRef->draw(buttonTexts[i]);
        
        this->m_MainMenuButtonGlobalBounds.push_back(buttons[i].getGlobalBounds());
    }
}

void GraphicsManager::HideUI() {
    this->m_windowRef->clear(sf::Color::White);
    this->m_windowRef->display();
}
void GraphicsManager::RenderGameScene(Board& board, GameState& currState) {
    // generate board
    board.render(*m_windowRef, currState);
}