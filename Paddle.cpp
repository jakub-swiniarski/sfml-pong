#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

#include "Paddle.hpp"

Paddle::Paddle(float x, float y, sf::Font font) {
    shape.setSize(sf::Vector2f(20.f, 100.f));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y); /* TODO: config.hpp screenwidth and screenheight */

    score = 0;

    //score_counter.setFont(font);
    score_counter.setString("0");
    score_counter.setCharacterSize(120); /* TODO: put this in config.hpp */
    score_counter.setFillColor(sf::Color::White);
    score_counter.setPosition(300.f, 0.f);
}
