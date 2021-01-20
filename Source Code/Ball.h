#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Player;
class Blocks;

class Ball {
public:
    Ball();
    void move(float time);
    bool checkWallCollision();
    bool checkPlayerCollision(const Player& player);
    bool checkBlocksCollision(Blocks& blocks);
    void changeSpeedAngle();
    void changeSpeed(float delta);
    void normAngle();
    void changeAngle(float delta);
    void draw(sf::RenderWindow& window);
public:
    sf::CircleShape body;
    const float ballRadius = 10;

    float angle;
    float angle_delta = PI / 50;
    float minAngle = PI / 6;
    float maxAngle = PI / 3;

    float speed = 500;
    float speed_delta = 30;
    float minSpeed = 300;
    float maxSpeed = 700;
};