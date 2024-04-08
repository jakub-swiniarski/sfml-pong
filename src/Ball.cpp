#include "Ball.hpp"

#include "config.hpp"

Ball::Ball(float x, float y) {
    setRadius(BALL_RADIUS);
    setFillColor(BALL_COLOR);
    setPosition(x, y);

    speed_x = BALL_START_SPEED_X;
    speed_y = BALL_START_SPEED_Y;
}

bool Ball::border_check(void) {
    if (getPosition().y <= 0.f
    || getPosition().y >= SCREEN_HEIGHT - getRadius()) {
        bounce_y();
        return 1;
    }
    return 0;
}

void Ball::bounce_x(void) {
    speed_x *= -1;
    speed_x += (speed_x > 0) ? 50 : -50;
}

void Ball::bounce_y(void) {
    speed_y *= -1;
}

void Ball::reset(void) {
    setPosition(SCREEN_WIDTH / 2.f - getRadius(), SCREEN_HEIGHT / 2.f - getRadius());
    speed_x = BALL_START_SPEED_X;
    speed_y = BALL_START_SPEED_Y;
}

void Ball::update(float mod) {
    move(speed_x * mod, speed_y * mod);
}
