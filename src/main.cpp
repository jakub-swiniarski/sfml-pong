#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "AIController.hpp"
#include "Ball.hpp"
#include "EventHandler.hpp"
#include "InputProcessor.hpp"
#include "Observer.hpp"
#include "Paddle.hpp"

#include "config.hpp"

//a
/* function declarations */
static void draw(void);
static void run(void);
static void setup(void);

/* variables */
static Ball ball(cfg::window::width / 2.f - cfg::ball::radius, cfg::window::height / 2.f - cfg::ball::radius);
static Paddle enemy(100.f, cfg::window::height / 2.f - cfg::paddle::height / 2, cfg::enemy::color, cfg::enemy::counter_color);
static sf::Font font;
static Paddle player(cfg::window::width - cfg::paddle::width - 100.f, cfg::window::height / 2.f - cfg::paddle::height / 2, cfg::player::color, cfg::player::counter_color);
static sf::Sound pop_sound;
static sf::SoundBuffer pop_buffer;
static sf::RenderWindow window(sf::VideoMode(cfg::window::width, cfg::window::height), "Pong", sf::Style::None);

/* constants */
static const std::string filepath = "/usr/local/share/pong/";

/* function implementations */
void draw(void) {
    window.clear();
    
    window.draw(ball);
    window.draw(enemy);
    window.draw(player);

    window.draw(enemy.get_counter());
    window.draw(player.get_counter());
    
    window.display();
}

void run(void) {
    AIController ai_controller(&ball, &enemy);
    sf::Clock dt_clock;
    EventHandler event_handler(&window);
    InputProcessor input_processor(&player);
    Observer observer(&ball, &enemy, &player);

    while (window.isOpen()) {
        float dt = dt_clock.restart().asSeconds();

        ai_controller.update(dt);
        ball.update(dt);
        event_handler.update();
        input_processor.update(dt);
        observer.update();
        
        enemy.border_check();
        player.border_check();

        if (ball.border_check()
        || enemy.ball_collision_check(&ball)
        || player.ball_collision_check(&ball))
            pop_sound.play();
        
        draw();
    }
}

void setup(void) {
    window.setFramerateLimit(cfg::window::fps);

    if (!font.loadFromFile(filepath + "font.ttf"))
        window.close();
    enemy.get_counter().setFont(font);
    player.get_counter().setFont(font);

    enemy.get_counter().setPosition(cfg::counter::shift_x, 0.f); 
    player.get_counter().setPosition(cfg::window::width - cfg::counter::shift_x - player.get_counter().getGlobalBounds().width, 0.f);

    if (!pop_buffer.loadFromFile(filepath + "pop.wav"))
        window.close(); 
    pop_sound.setBuffer(pop_buffer);
}

int main(void) {
    setup();    
    run();

    return 0;
}
