#include <algorithm>
#include <string>

#include "Ball.hpp"
#include "Paddle.hpp"

#include "config.hpp"

Paddle::Paddle(float x, float y, sf::Color p_col, sf::Color t_col) {
    setSize(sf::Vector2f(paddle_width, paddle_height));
    setFillColor(p_col);
    setPosition(x, y);

    score = 0;

    counter.setString("0");
    counter.setCharacterSize(font_size);
    counter.setFillColor(t_col);
    counter.setPosition(0.f, 0.f);
}

bool Paddle::ball_collision_check(Ball *b) {
    if (!getGlobalBounds().intersects(b->getGlobalBounds()))
        return 0;

    if (getGlobalBounds().contains(b->getPosition().x, b->getPosition().y + b->getRadius())) { /* left side of the ball */
        b->setPosition(getPosition().x + getSize().x, b->getPosition().y); /* we move the ball to prevent it from getting stuck */
        b->bounce_x();
    } else if (getGlobalBounds().contains(b->getPosition().x + 2.f * b->getRadius(), b->getPosition().y + b->getRadius())) { /* right side of the ball */
        b->setPosition(getPosition().x - 2.f * b->getRadius(), b->getPosition().y);
        b->bounce_x();
    } else if (getGlobalBounds().contains(b->getPosition().x + b->getRadius(), b->getPosition().y)) { /* top of the ball */
        b->setPosition(b->getPosition().x, getPosition().y + getSize().y);
        b->bounce_y();
    } else if (getGlobalBounds().contains(b->getPosition().x + b->getRadius(), b->getPosition().y + 2.f * b->getRadius())) { /* bottom of the ball */
        b->setPosition(b->getPosition().x, getPosition().y - 2.f * b->getRadius());
        b->bounce_y();
    }
    return 1;
}

void Paddle::border_check(void) {
    setPosition(getPosition().x, std::clamp(getPosition().y, 0.f, (float)screen_height - getSize().y));
}

void Paddle::update_counter(void) {
    score++;
    counter.setString(std::to_string(score));
}
