#include "SFML/Graphics/CircleShape.hpp"

#include "Ball.hpp"

#include "config.hpp"

Ball::Ball(float x, float y) {
    setRadius(10.f); /* TODO: make this configurable */
    setFillColor(BALL_COLOR);
    setPosition(x, y);

    speed_x = BALL_START_SPEED_X;
    speed_y = BALL_START_SPEED_Y;
}

bool Ball::border_check(void) {
    if (getPosition().y <= 0.f
    || getPosition().y >= SCREEN_HEIGHT - getRadius()) {
        speed_y *= -1.f;
        return 1;
    }
    return 0;
}

void Ball::reset_speed(void) {
    speed_x = BALL_START_SPEED_X;
    speed_y = BALL_START_SPEED_Y;
}

void Ball::update(float mod) {
    move(speed_x * mod, speed_y * mod);
}
