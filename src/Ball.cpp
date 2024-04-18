#include <algorithm>

#include "Ball.hpp"

#include "config.hpp"

Ball::Ball(float x, float y) {
    setRadius(ball_radius);
    setFillColor(ball_color);
    setPosition(x, y);

    speed_x = ball_start_speed_x;
    speed_y = ball_start_speed_y;
}

bool Ball::border_check(void) {
    if (getPosition().y <= 0.f
    || getPosition().y >= screen_height - getRadius()) {
        setPosition(getPosition().x, std::clamp(getPosition().y, 0.f, (float)screen_height - getRadius()));
        bounce_y();
        return 1;
    }
    return 0;
}

void Ball::bounce_x(void) {
    speed_x *= -1;
    speed_x += (speed_x > 0) ? ball_speed_boost : -ball_speed_boost;
}

void Ball::bounce_y(void) {
    speed_y *= -1;
}

void Ball::reset(void) {
    setPosition(screen_width / 2.f - getRadius(), screen_height / 2.f - getRadius());
    speed_x = ball_start_speed_x;
    speed_y = ball_start_speed_y;
}

void Ball::update(float mod) {
    move(speed_x * mod, speed_y * mod);
}
