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
static Ball ball(SCREEN_WIDTH / 2.f - BALL_RADIUS, SCREEN_HEIGHT / 2.f - BALL_RADIUS);
static Paddle enemy(100.f, SCREEN_HEIGHT / 2.f - PADDLE_HEIGHT / 2, ENEMY_COLOR, ENEMY_COUNTER_COLOR);
static sf::Font font;
static Paddle player(SCREEN_WIDTH - PADDLE_WIDTH - 100.f, SCREEN_HEIGHT / 2.f - PADDLE_HEIGHT / 2, PLAYER_COLOR, PLAYER_COUNTER_COLOR);
static sf::Sound pop_sound;
static sf::SoundBuffer pop_buffer;
static sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong", sf::Style::None);

/* constants */
static const std::string FILEPATH = "res/";

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
    window.setFramerateLimit(FPS);

    if (!font.loadFromFile(FILEPATH + "font.ttf"))
        window.close();
    enemy.counter.setFont(font);
    player.counter.setFont(font);

    enemy.counter.setPosition(COUNTER_SHIFT_X, 0.f); 
    player.counter.setPosition(SCREEN_WIDTH - COUNTER_SHIFT_X - player.counter.getGlobalBounds().width, 0.f);

    if (!pop_buffer.loadFromFile(FILEPATH + "pop.wav"))
        window.close(); 
    pop_sound.setBuffer(pop_buffer);
}

int main(void) {
    setup();    
    run();

    return 0;
}
