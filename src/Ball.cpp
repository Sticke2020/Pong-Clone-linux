
#include "Ball.hpp"

enum class BallColor {WHITE, YELLOW, RED};

BallColor ballColor = BallColor::WHITE;

// This is the constructor function
Ball::Ball(float startX, float startY) : m_Position(startX, startY) {
    m_Shape.setSize(sf::Vector2f(10, 10));
    m_Shape.setPosition(m_Position);

    m_Shape.setFillColor(sf::Color::White);
}

FloatRect Ball::getPosition() {
    return m_Shape.getGlobalBounds();
}

RectangleShape Ball::getShape() {
    return m_Shape;
}

float Ball::getXVelocity() {
    return m_DirectionX;
}

void Ball::reboundSides() {
    m_DirectionX = -m_DirectionX;
}

void Ball::reboundBatOrTop() {
    m_DirectionY = -m_DirectionY;
}

void Ball::reboundBottom() {
    m_Position.y = 0;
    m_Position.x = 500;
    m_DirectionY = -m_DirectionY;
}

void Ball::update(Time dt) {
    // Update the balls position
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();

    // Move the ball
    m_Shape.setPosition(m_Position);
}

void Ball::changeColor() {
    // Change the color of the ball
    switch (ballColor) {
        case BallColor::WHITE:
            m_Shape.setFillColor(sf::Color::Yellow);
            ballColor = BallColor::YELLOW;
            break;

        case BallColor::YELLOW:
            m_Shape.setFillColor(sf::Color::Red);
            ballColor = BallColor::RED;
            break;

        case BallColor::RED:
            m_Shape.setFillColor(sf::Color::White);
            ballColor = BallColor::WHITE;
            break;

        default:
            m_Shape.setFillColor(sf::Color::White);
            ballColor = BallColor::WHITE;
            break;
    }
}