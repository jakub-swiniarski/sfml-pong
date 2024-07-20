#include "SFML/Window/Window.hpp"

#include "EventHandler.hpp"

EventHandler::EventHandler(sf::Window& window)
    : window(window) {}

void EventHandler::update(void) {
    while(window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::EventType::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }
    }
}
