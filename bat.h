//
// Created by veilbreaker on 2/9/21.
//

#ifndef SFMLPONG_BAT_H
#define SFMLPONG_BAT_H


#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
private:
    Vector2f position;
    RectangleShape batShape;

    float batSpeed = 0.3f;
public:
    Bat(float startX, float startY);

    FloatRect getPosition();
    RectangleShape getShape();

    void moveLeft();
    void moveRight();
    void update();
};


#endif //SFMLPONG_BAT_H
