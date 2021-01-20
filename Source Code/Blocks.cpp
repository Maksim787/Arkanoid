#include "Blocks.h"
#include "Constants.h"

Block::Block(float x, float y) {
    body.setOrigin(Block::blockSize / 2.f);
    body.setPosition(x, y);
    body.setSize(blockSize);
    body.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
    body.setOutlineThickness(1);
    body.setOutlineColor(sf::Color::Magenta);
}
void Block::draw(sf::RenderWindow& window) {
    window.draw(body);
}
const sf::Vector2f Block::blockSize = sf::Vector2f(50, 25);


Blocks::Blocks() {
    for (float y = upInterval + Block::blockSize.y / 2;
        y <= screenY - downInterval - Block::blockSize.y / 2 + EPS;
        y += Block::blockSize.y) {
        for (float x = leftInterval + Block::blockSize.x / 2;
            x <= screenX - rightInterval - Block::blockSize.x / 2 + EPS;
            x += Block::blockSize.x) {
            blocks.emplace_back(x, y);
        }
    }
}
void Blocks::draw(sf::RenderWindow& window) {
    for (Block& block : blocks) {
        block.draw(window);
    }
}