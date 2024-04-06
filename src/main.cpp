#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "Ball.hpp"
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
static const std::string FILEPATH = "res/";

/* function implementations */
void draw(void) {
    window.clear();
    
    window.draw(ball);
    window.draw(enemy);
    window.draw(player);

    window.draw(enemy.score_counter);
    window.draw(player.score_counter);
    
    window.display();
}

void run(void) {
    sf::Clock dt_clock;
    InputProcessor input_processor(&player);
    Observer observer(&ball, &player, &enemy); /* TODO: move other vars here (if possible) */

    while (window.isOpen()) {
        float dt = dt_clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::EventType::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
        }
 
        input_processor.update(dt);
        player.border_check();

        if (ball.border_check())
            pop_sound.play();
        
        //ball movement
        ball.update(dt);

        //ball collisions with entities
        if ((enemy.ball_collision_check(&ball))
        || player.ball_collision_check(&ball))
            pop_sound.play();

        //enemy movement
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
    enemy.score_counter.setFont(font);
    player.score_counter.setFont(font);

    if (!pop_buffer.loadFromFile(FILEPATH + "pop.wav"))
        window.close(); 
    pop_sound.setBuffer(pop_buffer);
}

int main(void) {
    setup();    
    run();

    return 0;
}
