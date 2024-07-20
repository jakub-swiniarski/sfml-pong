#include <algorithm>

#include "Ball.hpp"

#include "config.hpp"

Ball::Ball(float x, float y)
    : speed(cfg::ball::speed_x, cfg::ball::speed_y) {
    setRadius(cfg::ball::radius);
    setFillColor(cfg::ball::color);
    setPosition(x, y);
}

bool Ball::border_check(void) {
    if (getPosition().y <= 0.f ||
        getPosition().y >= cfg::window::height - getRadius()) {
        setPosition(getPosition().x, std::clamp(getPosition().y, 0.0f, cfg::window::height - getRadius()));
        bounce_y();
        return 1;
    }
    return 0;
}

void Ball::bounce_x(void) {
    speed.x *= -1.0f;
    speed.x += (speed.x > 0) ? cfg::ball::speed_boost : -cfg::ball::speed_boost;
}

void Ball::bounce_y(void) {
    speed.y *= -1.0f;
}

void Ball::reset(void) {
    setPosition(cfg::window::width / 2.0f - getRadius(), cfg::window::height / 2.0f - getRadius());
    speed.x = cfg::ball::speed_x;
    speed.y = cfg::ball::speed_y;
}

void Ball::update(float mod) {
    move(speed.x * mod, speed.y * mod);
}
