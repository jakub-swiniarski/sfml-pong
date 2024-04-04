#pragma once

class Ball: public sf::CircleShape {
    float speed_x, speed_y;

public:
    Ball(float x, float y);
    bool border_check(void);
    void reset_speed(void);
    void update(float mod);
};
