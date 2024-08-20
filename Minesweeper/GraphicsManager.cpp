#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(sf::RenderWindow& t_window) {
    this->m_windowRef = &t_window;
}

void GraphicsManager::RenderMainMenu() {
    sf::CircleShape circle;
    circle.setRadius(50);
        circle.setOutlineColor(sf::Color::Red);
        circle.setOutlineThickness(5);
        // Set the origin to the center of the circle
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        // Position the circle in the center of the window
        circle.setPosition(m_windowRef->getSize().x / 2, m_windowRef->getSize().y / 2);
        m_windowRef->draw(circle);
}