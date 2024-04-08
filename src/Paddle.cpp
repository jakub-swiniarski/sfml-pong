#include <string>

#include "Ball.hpp"
#include "Paddle.hpp"

#include "config.hpp"

Paddle::Paddle(float x, float y, sf::Color p_col) {
    setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    setFillColor(p_col);
    setPosition(x, y);

    score = 0;

    counter.setString("0");
    counter.setCharacterSize(FONT_SIZE);
    counter.setFillColor(sf::Color::White);
    counter.setPosition(0.f, 0.f);
}

bool Paddle::ball_collision_check(Ball *b) {
    if (b->getPosition().y <= getPosition().y + getSize().y
    && b->getPosition().y + b->getRadius() >= getPosition().y)
        if (b->getPosition().x + b->getRadius() >= getPosition().x
        && b->getPosition().x <= getPosition().x + getSize().x)
            return 1;
    return 0;
}

void Paddle::border_check(void) {
    if (getPosition().y <= 0.f)
        setPosition(getPosition().x, 0.f);
    else if (getPosition().y + getSize().y >= SCREEN_HEIGHT)
        setPosition(getPosition().x, SCREEN_HEIGHT - getSize().y);
}

void Paddle::update_counter(void) {
    score++;
    counter.setString(std::to_string(score));
}
