#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <string>

#include "Ball.hpp"
#include "Paddle.hpp"

#include "config.hpp"

/* function declarations */
static void run(void);
static void setup(void);

/* variables */
static Ball ball(1280.f / 2.f - 10.f, 720.f / 2.f - 10.f); /* TODO: don't hardcode -10.f (radius) */
static sf::Time dt;
static sf::Clock dtClock;
static Paddle enemy(100.f, 720.f / 2.f - enemy.getSize().y / 2);
static sf::Event event;
static sf::Font font;
static Paddle player(1280.f - player.getSize().x - 100.f, 720.f / 2.f - player.getSize().y / 2); /* TODO: don't use play in initialization */
static sf::Sound popSound;
static sf::SoundBuffer popBuffer;
static sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong", sf::Style::None);

/* constants */
static const std::string FILEPATH = "res/";

/*function implementations */
void run(void) {
    while (window.isOpen()) {
        dt = dtClock.restart();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //keyboard input
            if (event.type == sf::Event::EventType::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }
 
        //player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0.f, -PLAYER_SPEED_Y * dt.asSeconds());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0.f, PLAYER_SPEED_Y * dt.asSeconds());

        //border check for player
        if (player.getPosition().y >= 720.f - player.getSize().y)
            player.setPosition(player.getPosition().x, 720.f - player.getSize().y);
        else if (player.getPosition().y <= 0.f)
            player.setPosition(player.getPosition().x, 0.f);
        
        //ball border check
        if (ball.getPosition().x <= 0.f) {
            player.score++;
            ball.setPosition(1280.f / 2.f - ball.getRadius(), 720.f / 2.f - ball.getRadius());
            player.score_counter.setString(std::to_string(player.score));
            ball.speed_x = BALL_START_SPEED_X;
        } else if (ball.getPosition().x >= 1280.f - ball.getRadius()) {
            enemy.score++;
            ball.setPosition(1280.f / 2.f - ball.getRadius(), 720.f / 2.f - ball.getRadius());
            enemy.score_counter.setString(std::to_string(enemy.score));
            ball.speed_x = BALL_START_SPEED_X;
        }
        if (ball.getPosition().y <= 0.f) {
            popSound.play();
            ball.speed_y *= -1.f;
        } else if (ball.getPosition().y >= 720.f - ball.getRadius()) {
            popSound.play(); 
            ball.speed_y *= -1.f;
        } 

        //ball movement
        ball.move(ball.speed_x * dt.asSeconds(), ball.speed_y * dt.asSeconds()); 

        //ball collisions with entities
        if (enemy.ball_collision_check(ball))
            popSound.play();
        else if (player.ball_collision_check(ball))
            popSound.play();

        //enemy movement
        if (enemy.getPosition().y + enemy.getSize().y / 2.f > ball.getPosition().y + ball.getRadius() / 2.f)
            enemy.move(0.f, -ENEMY_SPEED_Y * dt.asSeconds());
        else
            enemy.move(0.f, ENEMY_SPEED_Y * dt.asSeconds());
        
        //border check for enemy
        if (enemy.getPosition().y <= 0.f)
            enemy.setPosition(enemy.getPosition().x, 0.f);
        else if (enemy.getPosition().y + enemy.getSize().y >= 720.f)
            enemy.setPosition(enemy.getPosition().x, 720.f - enemy.getSize().y);

        window.clear();
        
        window.draw(ball);
        window.draw(enemy);
        window.draw(player);

        window.draw(enemy.score_counter);
        window.draw(player.score_counter);
        
        window.display();
    }
}

void setup(void) {
    if (!font.loadFromFile(FILEPATH + "font.ttf"))
        window.close();

    if (!popBuffer.loadFromFile(FILEPATH + "pop.wav"))
        window.close(); 
    popSound.setBuffer(popBuffer);

    enemy.score_counter.setFont(font);
    player.score_counter.setFont(font);
}

int main(void) {
    setup();    
    run();

    return 0;
}