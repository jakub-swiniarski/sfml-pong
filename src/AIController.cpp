#include "AIController.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

#include "config.hpp"

AIController::AIController(Ball *b, Paddle *p) {
    ball = b;
    paddle = p;
}

void AIController::update(float mod) {
    if (paddle->getPosition().y + paddle->getSize().y / 2.f > ball->getPosition().y + ball->getRadius() / 2.f)
        paddle->move(0.f, -enemy_speed_y * mod);
    else
        paddle->move(0.f, enemy_speed_y * mod);
    
}
