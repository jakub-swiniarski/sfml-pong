#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics/CircleShape.hpp>

class Ball: public sf::CircleShape {
    float speed_x, speed_y;

public:
    Ball(float x, float y);
    bool border_check(void);
    void bounce_x(void);
    void bounce_y(void);
    void reset(void);
    void update(float mod);
};

#endif /* BALL_HPP */
