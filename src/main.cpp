
#include "Bat.hpp"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main() {
    // Create a video mode object
    VideoMode vm = VideoMode::getDesktopMode();

    float screenWidth = vm.width;
    float screenHeight = vm.height;

    // Create and open a window for the game
    RenderWindow window(vm, "Pong", Style::Fullscreen);

    int score = 0;
    int lives = 3;

    // Create the bat at the bottom center of the screen
    Bat bat(screenWidth / 2, screenHeight - 20);

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
            bat.moveLeft();
        }
        else {
            bat.stopLeft();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            bat.moveRight();
        }
        else {
            bat.stopRight();
        }

        // Update the bat, the ball and the hud

        // Update the Delta Time
        Time dt = clock.restart();
        bat.update(dt);

        // Update the hud text
        std::stringstream ss;
        ss << "Score:" << score << " Lives:" << lives;
        hud.setString(ss.str());

        // Draw the bat, the ball and the hud
        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.display();
    }

    return 0;
}