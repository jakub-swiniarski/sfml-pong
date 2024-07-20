#include "AIController.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

#include "config.hpp"

AIController::AIController(Ball* ball, Paddle* paddle)
    : ball(ball),
      paddle(paddle) {}

void AIController::update(float mod) const {
    if (paddle->getPosition().y + paddle->getSize().y / 2.f > ball->getPosition().y + ball->getRadius() / 2.f)
        paddle->move(0.f, -cfg::enemy::speed_y * mod);
    else
        paddle->move(0.f, cfg::enemy::speed_y * mod);
    
}
