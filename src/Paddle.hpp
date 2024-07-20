#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Ball;

class Paddle : public sf::RectangleShape {
    int      score;
    sf::Text counter;

public:
    Paddle(float x, float y, sf::Color p_col, sf::Color t_col);

    bool      ball_collision_check(Ball& ball) const;
    void      border_check(void);
    sf::Text& get_counter(void);
    void      update_counter(void);
};

#endif // PADDLE_HPP
