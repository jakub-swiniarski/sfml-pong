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

/* function declarations */
static void draw(void);
static void run(void);
static void setup(void);

/* variables */
static Ball ball(screen_width / 2.f - ball_radius, screen_height / 2.f - ball_radius);
static Paddle enemy(100.f, screen_height / 2.f - paddle_height / 2, enemy_color, enemy_counter_color);
static sf::Font font;
static Paddle player(screen_width - paddle_width - 100.f, screen_height / 2.f - paddle_height / 2, player_color, player_counter_color);
static sf::Sound pop_sound;
static sf::SoundBuffer pop_buffer;
static sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Pong", sf::Style::None);

/* constants */
static const std::string filepath = "res/";

/* function implementations */
void draw(void) {
    window.clear();
    
    window.draw(ball);
    window.draw(enemy);
    window.draw(player);

    window.draw(enemy.counter);
    window.draw(player.counter);
    
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
    window.setFramerateLimit(fps);

    if (!font.loadFromFile(filepath + "font.ttf"))
        window.close();
    enemy.counter.setFont(font);
    player.counter.setFont(font);

    enemy.counter.setPosition(counter_shift_x, 0.f); 
    player.counter.setPosition(screen_width - counter_shift_x - player.counter.getGlobalBounds().width, 0.f);

    if (!pop_buffer.loadFromFile(filepath + "pop.wav"))
        window.close(); 
    pop_sound.setBuffer(pop_buffer);
}

int main(void) {
    setup();    
    run();

    return 0;
}
