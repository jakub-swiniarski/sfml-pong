#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

#include "Ball.hpp"
#include "Paddle.hpp"

#include "config.hpp"

Paddle::Paddle(float x, float y) {
    setSize(sf::Vector2f(20.f, 100.f));
    setFillColor(sf::Color::White);
    setPosition(x, y); /* TODO: config.hpp screenwidth and screenheight */

    score = 0;

    /* TODO: clean this mess up */
    score_counter.setString("0");
    score_counter.setCharacterSize(120); /* TODO: put this in config.hpp */
    score_counter.setFillColor(sf::Color::White);
    score_counter.setPosition(x, 0.f); /* TODO: both in the same place? interesting... */
}

bool Paddle::ball_collision_check(Ball &ball) {
    if (ball.getPosition().y <= getPosition().y + getSize().y && ball.getPosition().y + ball.getRadius() >= getPosition().y) {
        if (ball.getPosition().x + ball.getRadius() >= getPosition().x
        && ball.getPosition().x <= getPosition().x + getSize().x) {
            //ball.speed_x *= -1;
            //ball.speed_x += (ball.speed_x > 0) ? 50 : -50;
            return 1;
        }
    }
    return 0;
}

void Paddle::border_check(void) {
    if (getPosition().y <= 0.f)
        setPosition(getPosition().x, 0.f);
    else if (getPosition().y + getSize().y >= SCREEN_HEIGHT)
        setPosition(getPosition().x, SCREEN_HEIGHT - getSize().y);
}
