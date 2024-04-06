#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Ball;

class Paddle: public sf::RectangleShape {
    int score;

public:
    sf::Text score_counter;

    Paddle(float x, float y);
    bool ball_collision_check(Ball *b);
    void border_check(void);
    void update_counter(void);
};

#endif /* PADDLE_H */
