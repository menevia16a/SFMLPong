#include "bat.h"
#include "ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

Texture batTex;
Texture ballTex;
RectangleShape batShape;
RectangleShape ballShape;

const int BAT_RESOURCE = 1;
const int BALL_RESOURCE = 2;

void runGameLoop();
void setResourceTexture(RectangleShape rectShape, int resourceId);

// Game entry point
int main() {
    runGameLoop();
    return 0;
}

void runGameLoop() {
    int windowWidth = 600;
    int windowHeight = 500;
    int score = 0;
    int lives = 3;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Veil's Big Fat Pong");
    Bat bat(windowWidth / 2, windowHeight - 20);
    Ball ball(windowWidth / 2, 1);

    // Create a text object with for the HUD
    Text hudScore;
    Text hudLives;
    Font font;

    font.loadFromFile("Fonts/arcade.ttf");
    hudScore.setFont(font);
    hudScore.setCharacterSize(25);
    hudScore.setFillColor(Color::White);
    hudLives.setPosition(430, 0);
    hudLives.setFont(font);
    hudLives.setCharacterSize(25);
    hudLives.setFillColor(Color::White);

    // Player input
    Event event;

    while (true) {
        window.pollEvent(event);

        if (event.type == Event::Closed) {
            window.close();
            break;
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) { bat.moveLeft(); }
        else if (Keyboard::isKeyPressed(Keyboard::Right)) { bat.moveRight(); }
        else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
            break;
        }

        // Update frames
        // *************
        // Handle the ball hitting the bottom
        if (ball.getPosition().top > windowHeight) {
            // Reverse ball direction
            ball.hitBottom();
            // Subtract life
            lives--;

            // Reset game if 0 lives
            if (lives < 1) {
                score = 0;
                lives = 3;
            }
        }

        // Handle the ball hitting the top
        if (ball.getPosition().top < 0) {
            ball.reboundBatOrTop();
            score++;
        }

        // Handle the ball hitting the sides
        if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth) { ball.reboundSides(); }
        // Check if ball hit bat
        if (ball.getPosition().intersects(bat.getPosition())) { ball.reboundBatOrTop(); }

        // Call updates and set HUD
        ball.update();
        bat.update();

        std::stringstream ssScore;
        std::stringstream ssLives;

        ssScore << "Score:" << score;
        ssLives << "Lives:" << lives;
        hudScore.setString(ssScore.str());
        hudLives.setString(ssLives.str());

        // Draw the frames
        // ***************
        // Clear everything from last frame
        window.clear(Color(0, 128, 255, 255));
        // Draw bat and ball
        setResourceTexture(bat.getShape(), BAT_RESOURCE);
        setResourceTexture(ball.getShape(), BALL_RESOURCE);
        window.draw(batShape);
        window.draw(ballShape);
        // Draw HUD
        window.draw(hudScore);
        window.draw(hudLives);
        // Display it all
        window.display();
    }
}

void setResourceTexture(RectangleShape rectShape, int resourceId) {
    // Set the textures of the game
    if (resourceId == 1) {
        batShape = rectShape;
        batTex.loadFromFile("Textures/bat.png");
        batShape.setTexture(&batTex);
    }
    else if (resourceId == 2) {
        ballShape = rectShape;
        ballTex.loadFromFile("Textures/ball.png");
        ballShape.setTexture(&ballTex);
    }
}
