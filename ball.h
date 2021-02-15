//
// Created by veilbreaker on 2/9/21.
//

#ifndef SFMLPONG_BALL_H
#define SFMLPONG_BALL_H


#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
    Vector2f position;
    RectangleShape ballShape;

    float xVelocity = 0.2f;
    float yVelocity = 0.2f;
    float ySpeed = 0;
    float xSpeed = 0;
public:
    Ball(float startX, float startY);

    FloatRect getPosition();
    RectangleShape getShape();

    void reboundSides();
    void reboundBatOrTop();
    void hitBottom();
    void update(int score);
};


#endif //SFMLPONG_BALL_H
