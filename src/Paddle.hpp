#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Ball;

class Paddle : public sf::RectangleShape {
    int score;

public:
    sf::Text counter;

    Paddle(float x, float y, sf::Color p_col, sf::Color t_col);
    bool ball_collision_check(Ball *b);
    void border_check(void);
    void update_counter(void);
};

#endif /* PADDLE_HPP */
