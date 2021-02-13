//
// Created by veilbreaker on 2/9/21.
//
#include "bat.h"

// Constructor
Bat::Bat(float startX, float startY) {
    position.x = startX;
    position.y = startY;

    batShape.setSize(Vector2f(50, 5));
    batShape.setPosition(position);
}

FloatRect Bat::getPosition() { return batShape.getGlobalBounds(); }
RectangleShape Bat::getShape() { return batShape; }
void Bat::collisionLeftSide() { position.x -= position.x; }
void Bat::collisionRightSide() { position.x -= 0.5f; }
void Bat::moveLeft() { position.x -= batSpeed; }
void Bat::moveRight() { position.x += batSpeed; }
void Bat::update() { batShape.setPosition(position); }
