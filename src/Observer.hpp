#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Ball;
class Paddle;

class Observer {
    //-----ACTORS-----//
    Paddle& player;
    Paddle& enemy;
    Ball&   ball;

    //-----OTHER-----//
    sf::Sound sound_pop;

public:
    Observer(Ball& ball, Paddle& enemy, Paddle& player, sf::SoundBuffer& sound_buffer);
    
    void update(void);
};

#endif // OBSERVER_HPP
