
#include "Bat.hpp"
#include "Ball.hpp"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main() {
    // Create a video mode object
    VideoMode vm = VideoMode::getDesktopMode();

    float screenWidth = vm.width;
    float screenHeight = vm.height;

    // Create and open a window for the game
    RenderWindow window(vm, "Pong", Style::Default);

    int score = 0;
    int lives = 3;

    // Create the bat at the bottom center of the screen
    Bat bat(screenWidth / 2, screenHeight - 40);

    // Create a ball
    Ball ball(screenWidth / 2, 0);

    // Create a text object called hud
    Text hud;

    // A cool font
    Font font;
    font.loadFromFile("assets/font/terminal-vision.regular.otf");

    // Set the font
    hud.setFont(font);

    // Set the font size, color and position
    hud.setCharacterSize(75);
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);

    // Create the clock for timing everything 
    Clock clock;

    while (window.isOpen()) {
        // Handle the player input
        Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                // Quit the game when the window is closed
                window.close();
            }
        }

        // Handle the player quiting
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        // Handle the pressing and releasing of the arrow keys
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            // Check if the bat has touched the left edge of screen
            if (bat.getPosition().left < 0) {
                bat.stopLeft();
            }
            else {
                bat.moveLeft();
            }
        }
        else {
            bat.stopLeft();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            // Check if the bat has touched the right edge of the screen
            if (bat.getPosition().left + 50 > window.getSize().x) {
                bat.stopRight();
            }
            else {
                bat.moveRight();
            }
        }
        else {
            bat.stopRight();
        }

        // Update the bat, the ball and the hud

        // Update the Delta Time
        Time dt = clock.restart();
        bat.update(dt);
        ball.update(dt);

        // Update the hud text
        std::stringstream ss;
        ss << "Score:" << score << " Lives:" << lives;
        hud.setString(ss.str());

        // Handle the ball hitting the bottom
        if (ball.getPosition().top > window.getSize().y) {
            // Reverse the ball direction
            ball.reboundBottom();

            // Remove a life
            lives --;

            // Remove a point from score since a point is added when the ball resets
            score --;

            // Check for zero lives
            if (lives < 1) {
                // Reset the score
                score = -1;

                // Reset the lives
                lives = 3;
            }
        }

        // Handle the ball hitting the top
        if (ball.getPosition().top < 0) {
            // Force the ball out of the ceiling boundary to prevent this from looping and increasing score by more than 1
            ball.setPosition(ball.getPosition().left, 0.0f);

            // Reverse the ball direction when it hits the top boundary
            ball.reboundBatOrTop();

            // Increase the player score
            score ++;

            // Change the ball color
            ball.changeColor();
        }

        // Handle the ball hitting the sides
        if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x) {
            ball.reboundSides();
        }

        // Has the ball hit the bat?
        if (ball.getPosition().intersects(bat.getPosition())) {
            // Hit detected so reverse the ball and score a point
            ball.reboundBatOrTop();
        }

        // Draw the bat, the ball and the hud
        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();
    }

    return 0;
}