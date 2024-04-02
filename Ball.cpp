#include "SFML/Graphics/CircleShape.hpp"

#include "Ball.hpp"

#include "config.hpp"

Ball::Ball(float x, float y) {
    setRadius(10.f);
    setFillColor(BALL_COLOR);
    setPosition(x, y);

    speed_x = 0.f;
    speed_y = 0.f;
}
