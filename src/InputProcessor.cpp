#include <SFML/Window/Keyboard.hpp>

#include "InputProcessor.hpp"
#include "Paddle.hpp"

#include "config.hpp"

InputProcessor::InputProcessor(Paddle *p) {
    player = p;
}

void InputProcessor::update(float mod) const {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        player->move(0.f, -cfg::player::speed_y * mod);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        player->move(0.f, cfg::player::speed_y * mod);
}
