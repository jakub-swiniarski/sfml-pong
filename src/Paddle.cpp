#include <algorithm>
#include <string>

#include "Ball.hpp"
#include "Paddle.hpp"

#include "config.hpp"

Paddle::Paddle(float x, float y, sf::Color p_col, sf::Color t_col)
    : score(0) {
    setSize(sf::Vector2f(cfg::paddle::width, cfg::paddle::height));
    setFillColor(p_col);
    setPosition(x, y);

    counter.setString("0");
    counter.setCharacterSize(cfg::counter::font_size);
    counter.setFillColor(t_col);
    counter.setPosition(0.0f, 0.0f);
}

bool Paddle::ball_collision_check(Ball& ball) const {
    if (!getGlobalBounds().intersects(ball.getGlobalBounds()))
        return 0;

    if (getGlobalBounds().contains(ball.getPosition().x, ball.getPosition().y + ball.getRadius())) { // left side of the ball
        ball.setPosition(getPosition().x + getSize().x, ball.getPosition().y); // we move the ball to prevent it from getting stuck
        ball.bounce_x();
    } else if (getGlobalBounds().contains(ball.getPosition().x + 2.0f * ball.getRadius(), ball.getPosition().y + ball.getRadius())) { // right side of the ball
        ball.setPosition(getPosition().x - 2.0f * ball.getRadius(), ball.getPosition().y);
        ball.bounce_x();
    } else if (getGlobalBounds().contains(ball.getPosition().x + ball.getRadius(), ball.getPosition().y)) { // top of the ball
        ball.setPosition(ball.getPosition().x, getPosition().y + getSize().y);
        ball.bounce_y();
    } else if (getGlobalBounds().contains(ball.getPosition().x + ball.getRadius(), ball.getPosition().y + 2.0f * ball.getRadius())) { // bottom of the ball
        ball.setPosition(ball.getPosition().x, getPosition().y - 2.0f * ball.getRadius());
        ball.bounce_y();
    }

    return 1;
}

void Paddle::border_check(void) {
    setPosition(getPosition().x, std::clamp(getPosition().y, 0.0f, cfg::window::height - getSize().y));
}

sf::Text& Paddle::get_counter(void) {
    return counter;
}

void Paddle::update_counter(void) {
    score++;
    counter.setString(std::to_string(score));
}
