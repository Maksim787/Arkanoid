#pragma once
#include <SFML/Graphics.hpp>

class Ball;

class Player {
public:
    Player();
    void move(int dir, float time);
    void move_AI(Ball ball, float time);
    void changeSpeed(float delta);
    void draw(sf::RenderWindow& window);
public:
    sf::RectangleShape body;
    float speed = 800;
    sf::Vector2f playerSize = sf::Vector2f(200, 10);
};