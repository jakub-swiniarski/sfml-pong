#pragma once

class Ball: public sf::CircleShape {
public:
    float speed_x, speed_y;

public:
    Ball(float x, float y);
    void update(float mod);
};
