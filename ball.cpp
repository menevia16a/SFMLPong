//
// Created by veilbreaker on 2/9/21.
//

#include "ball.h"

// Constructor
Ball::Ball(float startX, float startY) {
    position.x = startX;
    position.y = startY;

    ballShape.setSize(sf::Vector2f(10, 10));
    ballShape.setPosition(position);
}

FloatRect Ball::getPosition() { return ballShape.getGlobalBounds(); }
RectangleShape Ball::getShape() { return ballShape; }
void Ball::reboundSides() { xVelocity = -xVelocity; }

void Ball::reboundBatOrTop() {
    position.y -= (yVelocity * 40);
    yVelocity = -yVelocity;
}

void Ball::hitBottom() {
    position.y = 1;
    position.x = 500;
}

void Ball::update(int score) {
    // Update the ball position variables
    if (yVelocity < 0)
        ySpeed = -ySpeed;
    else if (yVelocity > 0 && ySpeed < 0)
        ySpeed *= -1;

    if (xVelocity < 0)
        xSpeed = -xSpeed;
    else if (xVelocity > 0 && xSpeed < 0)
        xSpeed *= -1;

    position.y += yVelocity + ySpeed;
    position.x += xVelocity + xSpeed;
    ySpeed = 0;
    xSpeed = 0;

    // Update ball speed based on score
    for (int i = 0; i < (score / 5); i++) {
        ySpeed += 0.1f;
        xSpeed += 0.1f;
    }

    // Move the ball and the bat
    ballShape.setPosition(position);
}
