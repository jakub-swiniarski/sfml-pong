#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

class EventHandler {
    sf::Event event;
    sf::Window *window;

public:
    EventHandler(sf::Window *w);
    void update(void);
};

#endif /* EVENTHANDLER_H */
