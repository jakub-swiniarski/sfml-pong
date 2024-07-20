#ifndef APP_HPP
#define APP_HPP

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "AIController.hpp"
#include "Ball.hpp"
#include "InputProcessor.hpp"
#include "Observer.hpp"
#include "Paddle.hpp"

class App {
    //-----CORE-----//
    sf::RenderWindow window;

    //-----ACTORS-----//
    Ball   ball;
    Paddle enemy;
    Paddle player;
    
    //-----RESOURCES-----//
    const std::string res_path =
#ifdef DEBUG
    "res/"
#else
    "/usr/local/share/pong/"
#endif // DEBUG
    ;
    sf::Font        font;
    sf::SoundBuffer pop_buffer;
    sf::Sound       pop_sound;

    void setup(void);
    void run(void);
    void draw(void);

public:
    App(void);
};

#endif // APP_HPP
