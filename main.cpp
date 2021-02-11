#include "bat.h"
#include "ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

// Game entry point
int main() {
    int windowWidth = 600;
    int windowHeight = 500;
    int score = 0;
    int lives = 3;

    // Render 1024x768 window
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Veil's Big Fat Pong");
    // Create the bat
    Bat bat(windowWidth / 2, windowHeight - 20);
    // Create a ball
    Ball ball(windowWidth / 2, 1);

    // Create a text object with for the HUD
    Text hud;
    Font font;

    font.loadFromFile("arcade.ttf");
    hud.setFont(font);
    hud.setCharacterSize(25);
    hud.setFillColor(Color::White);

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

        std::stringstream ss;

        ss << "Score:" << score << "           Lives:" << lives;
        hud.setString(ss.str());

        // Draw the frames
        // ***************
        // Clear everything from last frame
        window.clear(Color(26, 128, 182, 255));
        // Draw bat and ball
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        // Draw HUD
        window.draw(hud);
        // Display it all
        window.display();
    }

    return 0;
}
