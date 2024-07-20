#include <SFML/Window/Keyboard.hpp>

#include "InputProcessor.hpp"
#include "Paddle.hpp"

#include "config.hpp"

InputProcessor::InputProcessor(Paddle* paddle)
    : paddle(paddle) {}

void InputProcessor::update(float mod) const {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        paddle->move(0.f, -cfg::player::speed_y * mod);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        paddle->move(0.f, cfg::player::speed_y * mod);
}
