#include <iostream>
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Blocks.h"
#include "Player.h"
#include "Ball.h"

bool gameOver;
bool gamePause;
bool ai_mode;

void Restart() {
    gameOver = false;
    gamePause = true;
    ai_mode = false;
}

void printVector(sf::Vector2f v) {
    std::cout << v.x << " " << v.y << "\n";
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(screenX), static_cast<unsigned int>(screenY)), "Arkanoid");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        Player player;
        Ball ball;
        Blocks blocks;
        sf::Clock clock;
        window.clear();
        window.display();
        Restart();
        while (!gameOver && window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::LostFocus:
                    gamePause = true;
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::R:
                        gameOver = true;
                        break;
                    case sf::Keyboard::P:
                    case sf::Keyboard::Space:
                        gamePause = !gamePause;
                        break;
                    case sf::Keyboard::A:
                        ai_mode = !ai_mode;
                        break;
                    }
                }
            }
            float time = clock.restart().asSeconds();
            if (gamePause)
                continue;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
                ball.changeSpeed(10.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
                ball.changeSpeed(-10.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period)) {
                player.changeSpeed(10.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)) {
                player.changeSpeed(-10.f);
            }


            if (ai_mode) {
                player.move_AI(ball, time);
            }
            else {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    player.move(-1, time);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    player.move(1, time);
                }
            }
            ball.move(time);
            if (ball.checkWallCollision() ||
                ball.checkPlayerCollision(player) ||
                ball.checkBlocksCollision(blocks)) {
                ball.normAngle();
                float prev_speed = ball.speed;
                float prev_angle = ball.angle;
                ball.changeSpeedAngle();
                std::cout << "Ball speed: " << prev_speed << " -> " << ball.speed << "\n";
                std::cout << "Ball angle: " << prev_angle * 180 / PI << " -> " << ball.angle * 180 / PI << "\n";
            }

            window.clear();
            blocks.draw(window);
            player.draw(window);
            ball.draw(window);
            window.display();
        }
    }
    return 0;
}
