#include "Player.h"
#include "Constants.h"
#include "Ball.h"

#include <iostream>

Player::Player() {
    body.setOrigin(playerSize / 2.f);
    body.setSize(playerSize);
    body.setPosition(screenX / 2.f, screenY - playerSize.y / 2);
}
void Player::move(int dir, float time) {
    body.move(sf::Vector2f(dir * speed * time, 0));
    float position = body.getPosition().x;
    if (position - playerSize.x / 2 < 0)
        body.setPosition(sf::Vector2f(playerSize.x / 2, screenY - playerSize.y / 2));
    if (position + playerSize.x / 2 > screenX)
        body.setPosition(sf::Vector2f(screenX - playerSize.x / 2, screenY - playerSize.y / 2));
}
void Player::move_AI(Ball ball, float time) {
    float ball_x = ball.body.getPosition().x;
    float player_x = body.getPosition().x;
    if (abs(player_x - ball_x) <= speed * time) {
        body.setPosition(sf::Vector2f(ball_x, screenY - playerSize.y / 2));
    }
    else if (player_x < ball_x) {
        move(1, time);
    }
    else {
        move(-1, time);
    }
}
void Player::changeSpeed(float delta) {
    std::cout << "Player speed changed from " << speed;
    speed += delta;
    std::cout << " to " << speed << "\n";
}
void Player::draw(sf::RenderWindow& window) {
    window.draw(body);
}