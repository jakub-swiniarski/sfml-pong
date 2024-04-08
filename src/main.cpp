#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

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
static Paddle enemy(100.f, SCREEN_HEIGHT / 2.f - PADDLE_HEIGHT / 2);
static sf::Font font;
static Paddle player(SCREEN_WIDTH - PADDLE_WIDTH - 100.f, SCREEN_HEIGHT / 2.f - PADDLE_HEIGHT / 2);
static sf::Sound pop_sound;
static sf::SoundBuffer pop_buffer;
static sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong", sf::Style::None); /* TODO: fullscreen */

/* constants */
static const std::string FILEPATH = "res/"; /* TODO: reset this before merging */

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
    sf::Clock dt_clock;
    EventHandler event_handler(&window);
    InputProcessor input_processor(&player);
    Observer observer(&ball, &enemy, &player);

    while (window.isOpen()) {
        float dt = dt_clock.restart().asSeconds();

        event_handler.update();

        input_processor.update(dt);
        player.border_check();

        if (ball.border_check())
            pop_sound.play();
        ball.update(dt);

        if ((enemy.ball_collision_check(&ball)) /* TODO: this is already calculated in Observer.cpp */
        || player.ball_collision_check(&ball))
            pop_sound.play();

        if (enemy.getPosition().y + enemy.getSize().y / 2.f > ball.getPosition().y + ball.getRadius() / 2.f)
            enemy.move(0.f, -ENEMY_SPEED_Y * dt);
        else
            enemy.move(0.f, ENEMY_SPEED_Y * dt);

        enemy.border_check();

        observer.update();
        
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
