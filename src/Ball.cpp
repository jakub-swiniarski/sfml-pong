#include <algorithm>

#include "Ball.hpp"

#include "config.hpp"

Ball::Ball(float x, float y) {
    setRadius(cfg::ball::radius);
    setFillColor(cfg::ball::color);
    setPosition(x, y);

    speed_x = cfg::ball::speed_x;
    speed_y = cfg::ball::speed_y;
}

bool Ball::border_check(void) {
    if (getPosition().y <= 0.f
    || getPosition().y >= cfg::window::height - getRadius()) {
        setPosition(getPosition().x, std::clamp(getPosition().y, 0.f, (float)cfg::window::height - getRadius()));
        bounce_y();
        return 1;
    }
    return 0;
}

void Ball::bounce_x(void) {
    speed_x *= -1;
    speed_x += (speed_x > 0) ? cfg::ball::speed_boost : -cfg::ball::speed_boost;
}

void Ball::bounce_y(void) {
    speed_y *= -1;
}

void Ball::reset(void) {
    setPosition(cfg::window::width / 2.f - getRadius(), cfg::window::height / 2.f - getRadius());
    speed_x = cfg::ball::speed_x;
    speed_y = cfg::ball::speed_y;
}

void Ball::update(float mod) {
    move(speed_x * mod, speed_y * mod);
}
