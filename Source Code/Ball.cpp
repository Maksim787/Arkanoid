#include "Ball.h"
#include "Blocks.h"
#include "Constants.h"
#include "Player.h"

#include <iostream>

extern bool gameOver;

Ball::Ball() {
    body.setRadius(ballRadius);
    body.setPosition(screenX / 2.f, screenY / 2.f);
    angle = PI / 6 + static_cast<float>(rand() % 1000) / 1000 * PI / 6;
    if (rand() % 2)
        angle = PI - angle;
    std::cout << "Ball angle " << angle * 180 / PI << "\n";
}
void Ball::move(float time) {
    sf::Vector2f ballDirection = sf::Vector2f(cos(angle), sin(angle));
    body.move(ballDirection * speed * time);
}
bool Ball::checkWallCollision() {
    sf::Vector2f ballPos = body.getPosition();
    if (ballPos.x - ballRadius < 0) {
        ballPos.x = ballRadius;
        angle = PI - angle;
        std::cout << "Wall Collistion at left\n";
    }
    else if (ballPos.x + ballRadius > screenX) {
        ballPos.x = screenX - ballRadius;
        angle = PI - angle;
        std::cout << "Wall Collistion at right\n";
    }
    else if (ballPos.y - ballRadius < 0) {
        ballPos.y = ballRadius;
        angle = -angle;
        std::cout << "Wall Collistion at up\n";
    }
    else if (ballPos.y > screenY) {
        gameOver = true;
        //ballPos.y = screenY;
        //angle = -angle;
        std::cout << "Wall Collistion at down\n";
    }
    else {
        return false;
    }
    body.setPosition(ballPos);
    return true;
}
bool Ball::checkPlayerCollision(const Player& player) {
    sf::Vector2f ballPos = body.getPosition();
    sf::Vector2f playerPos = player.body.getPosition();
    sf::Vector2f playerSize = player.body.getSize();
    if (ballPos.y + ballRadius > playerPos.y - playerSize.y / 2 &&
        ballPos.x + ballRadius > playerPos.x - playerSize.x / 2 &&
        ballPos.x - ballRadius < playerPos.x + playerSize.x / 2) {
        gameOver = false;
        ballPos.y = screenY - playerSize.y - ballRadius;
        angle = -angle;
        std::cout << "Player Collision\n";
        body.setPosition(ballPos);
        return true;
    }
    return false;
}
bool Ball::checkBlocksCollision(Blocks& blocks) {
    if (blocks.blocks.empty())
        return false;
    sf::Vector2f ballPos = body.getPosition();
    sf::Vector2f blockSize = blocks.blocks[0].body.getSize();
    float lengthX = blockSize.x / 2 + ballRadius;
    float lengthY = blockSize.y / 2 + ballRadius;
    for (size_t i = 0; i < blocks.blocks.size(); ++i) {
        sf::Vector2f blockPos = blocks.blocks[i].body.getPosition();
        float dx = abs(ballPos.x - blockPos.x);
        float dy = abs(ballPos.y - blockPos.y);
        if (dx < lengthX && dy < lengthY) {
            std::cout << "Block Collision at ";
            if (abs(dx - lengthX) < abs(dy - lengthY)) {
                angle = PI - angle;
                if (ballPos.x > blockPos.x) {
                    ballPos.x = blockPos.x + blockSize.x / 2 + ballRadius;
                    std::cout << "right\n";
                }
                else {
                    ballPos.x = blockPos.x - blockSize.x / 2 - ballRadius;
                    std::cout << "left\n";
                }
            }
            else {
                if (ballPos.y > blockPos.y) {
                    ballPos.y = blockPos.y + blockSize.y / 2 + ballRadius;
                    std::cout << "down\n";
                }
                else {
                    ballPos.y = blockPos.y - blockSize.y / 2 - ballRadius;
                    std::cout << "up\n";
                }
                angle = -angle;
            }
            blocks.blocks[i] = blocks.blocks.back();
            blocks.blocks.pop_back();
            body.setPosition(ballPos);
            return true;
        }
    }
    return false;
}
void Ball::changeSpeedAngle() {
    int sign = 2 * (rand() % 2) - 1;
    changeSpeed(speed_delta * sign);
    sign = 2 * (rand() % 2) - 1;
    changeAngle(angle_delta * sign);
}
void Ball::changeSpeed(float delta) {
    speed += delta;
    if (speed < minSpeed)
        speed = minSpeed;
    else if (speed > maxSpeed)
        speed = maxSpeed;
}
void Ball::normAngle() {
    if (angle < 0) {
        angle += 2 * PI;
    }
    else if (angle > 2 * PI) {
        angle -= 2 * PI;
    }
}
void Ball::changeAngle(float delta) {
    angle += delta;
    normAngle();
    float back_change = 0;
    if (angle > 3 * PI / 2) {
        back_change = 3 * PI / 2;
    }
    else if (angle > PI) {
        back_change = PI;
    }
    else if (angle > PI / 2) {
        back_change = PI / 2;
    }
    angle -= back_change;
    if (angle < minAngle) {
        angle = minAngle;
    }
    else if (angle > maxAngle) {
        angle = maxAngle;
    }
    angle += back_change;
}
void Ball::draw(sf::RenderWindow& window) {
    window.draw(body);
}