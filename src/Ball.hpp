#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Ball : public sf::CircleShape {
    sf::Vector2f speed;

public:
    Ball(float x, float y);

    bool border_check(void);
    void bounce_x(void);
    void bounce_y(void);
    void reset(void);
    void update(float mod);
};

#endif // BALL_HPP
