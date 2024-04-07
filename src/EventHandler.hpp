#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SFML/Window/Event.hpp>

namespace sf {
    class Window;
}

class EventHandler {
    sf::Event event;
    sf::Window *window;

public:
    EventHandler(sf::Window *w);
    void update(void);
};

#endif /* EVENTHANDLER_H */
