#include "bat.h"
#include "ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

RectangleShape ballShape;
RectangleShape batShape;
Texture ballTex;
Texture batTex;
Event event;
Font font;

const int windowWidth = 600;
const int windowHeight = 500;

enum Resource { BAT_RES, BALL_RES };

void runGameLoop();
void setResourceTexture(RectangleShape rectShape, Resource resourceId);

// Game entry point
int main() {
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Main Menu - VBFP");
    // Load resources
    font.loadFromFile("Fonts/arcade.ttf");
    batTex.loadFromFile("Textures/bat.png");
    ballTex.loadFromFile("Textures/ball.png");
    window.setFramerateLimit(60); // Limit framerate to not have unneeded stress

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                break;
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
                break;
            }

            window.clear(Color(128, 128, 128, 255));

            // Set up main menu
            Text title("Veil's Big Fat Pong", font, 25);
            title.setPosition(75, 40);

            // Draw main menu
            window.draw(title);
            window.display();
        }
    }

    //runGameLoop();

    return 0;
}

void runGameLoop() {
    int score = 0;
    int lives = 3;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Veil's Big Fat Pong");
    Bat bat(windowWidth / 2, windowHeight - 20);
    Ball ball(windowWidth / 2, 1);

    // Create a text object with for the HUD
    Text hudScore;
    Text hudLives;

    hudScore.setFont(font);
    hudScore.setCharacterSize(25);
    hudLives.setPosition(430, 0);
    hudLives.setFont(font);
    hudLives.setCharacterSize(25);

    while (window.isOpen()) {
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

        // Handle the ball/bat hitting the sides
        if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth) { ball.reboundSides(); }
        if (bat.getPosition().left < 0) { bat.collisionLeftSide(); }
        else if (bat.getPosition().left + 50 > windowWidth) { bat.collisionRightSide(); }
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
        setResourceTexture(bat.getShape(), BAT_RES);
        setResourceTexture(ball.getShape(), BALL_RES);
        window.draw(batShape);
        window.draw(ballShape);
        // Draw HUD
        window.draw(hudScore);
        window.draw(hudLives);
        // Display it all
        window.display();
    }
}

void setResourceTexture(RectangleShape rectShape, Resource resourceId) {
    // Set the textures of the game
    if (resourceId == BAT_RES) {
        batShape = rectShape;
        batShape.setTexture(&batTex);
    }
    else if (resourceId == BALL_RES) {
        ballShape = rectShape;
        ballShape.setTexture(&ballTex);
    }
}
