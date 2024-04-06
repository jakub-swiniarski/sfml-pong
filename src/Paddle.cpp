#include <string>

#include "Ball.hpp"
#include "Paddle.hpp"

#include "config.hpp"

Paddle::Paddle(float x, float y) {
    setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    setFillColor(sf::Color::White);
    setPosition(x, y);

    score = 0;

    /* TODO: clean this mess up */
    score_counter.setString("0");
    score_counter.setCharacterSize(FONT_SIZE); /* TODO: put this in config.hpp */
    score_counter.setFillColor(PADDLE_COLOR);
    score_counter.setPosition(x, 0.f);
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
    score_counter.setString(std::to_string(score));
}
