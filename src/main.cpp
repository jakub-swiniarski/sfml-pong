#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "Ball.hpp"
#include "Observer.hpp"
#include "Paddle.hpp"

#include "config.hpp"

/* function declarations */
static void draw(void);
static void input(void);
static void run(void);
static void setup(void);

/* variables */
static Ball ball(SCREEN_WIDTH / 2.f - 10.f, SCREEN_HEIGHT / 2.f - 10.f); /* TODO: don't hardcode -10.f (radius) */
static sf::Time dt; /* TODO: this should be a float + simplify dt mechanism */
static sf::Clock dt_clock;
static Paddle enemy(100.f, SCREEN_HEIGHT / 2.f - enemy.getSize().y / 2);
static sf::Event event;
static sf::Font font;
static Paddle player(SCREEN_WIDTH - player.getSize().x - 100.f, SCREEN_HEIGHT / 2.f - player.getSize().y / 2); /* TODO: don't use player in initialization */
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

void input(void) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        player.move(0.f, -PLAYER_SPEED_Y * dt.asSeconds());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        player.move(0.f, PLAYER_SPEED_Y * dt.asSeconds());
}

void run(void) {
    Observer observer(&ball, &player, &enemy); /* TODO: move other vars here (if possible) */

    while (window.isOpen()) {
        dt = dt_clock.restart();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //keyboard input
            if (event.type == sf::Event::EventType::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
        }
 
        input();
        player.border_check();
        
        //ball border check
        if (ball.getPosition().x <= 0.f) { /* TODO: this has to be done by the observer */
            /* TODO: this could be turned into a method (update_counter?) */
            player.score++;
            player.score_counter.setString(std::to_string(player.score));

            ball.setPosition(SCREEN_WIDTH / 2.f - ball.getRadius(), SCREEN_HEIGHT / 2.f - ball.getRadius());
            ball.reset_speed();
        } else if (ball.getPosition().x >= SCREEN_WIDTH - ball.getRadius()) {
            enemy.score++;
            enemy.score_counter.setString(std::to_string(enemy.score));

            ball.setPosition(SCREEN_WIDTH / 2.f - ball.getRadius(), SCREEN_HEIGHT / 2.f - ball.getRadius());
            ball.reset_speed();
        }
        if (ball.border_check())
            pop_sound.play();

        //ball movement
        ball.update(dt.asSeconds());

        //ball collisions with entities
        if ((enemy.ball_collision_check(&ball))
        || player.ball_collision_check(&ball))
            pop_sound.play();

        //enemy movement
        if (enemy.getPosition().y + enemy.getSize().y / 2.f > ball.getPosition().y + ball.getRadius() / 2.f)
            enemy.move(0.f, -ENEMY_SPEED_Y * dt.asSeconds());
        else
            enemy.move(0.f, ENEMY_SPEED_Y * dt.asSeconds());

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
