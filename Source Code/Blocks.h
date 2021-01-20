#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Block {
public:
    Block(float x, float y);
    void draw(sf::RenderWindow& window);
public:
    sf::RectangleShape body;
    static const sf::Vector2f blockSize;
};

class Blocks {
public:
    Blocks();
    void draw(sf::RenderWindow& window);
public:
    std::vector<Block> blocks;
    const float leftInterval = 50;
    const float rightInterval = 50;
    const float upInterval = 50;
    const float downInterval = 500;
};