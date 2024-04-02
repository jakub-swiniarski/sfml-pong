#include "SFML/Graphics/CircleShape.hpp"

#include "Ball.hpp"

#include "config.hpp"

Ball::Ball(float x, float y) {
    setRadius(10.f);
    setFillColor(BALL_COLOR);
    setPosition(x, y);

    speed_x = BALL_START_SPEED_X;
    speed_y = BALL_START_SPEED_Y;
}
