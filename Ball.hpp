#pragma once

class Ball: public sf::CircleShape {
public:
    float speed_x, speed_y;

    Ball(float x, float y);
};
