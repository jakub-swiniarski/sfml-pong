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
#include <string>

#include "Ball.hpp"
#include "Paddle.hpp"

#include "config.hpp"

int main(void) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong", sf::Style::None, settings);

    std::string filepath = "res/";

    sf::Font font;
    if (!font.loadFromFile(filepath + "font.ttf"))
        window.close();

    sf::SoundBuffer popBuffer;
    if (!popBuffer.loadFromFile(filepath + "pop.wav"))
        window.close(); 
    sf::Sound popSound;
    popSound.setBuffer(popBuffer);

    Ball ball(1280.f / 2.f - 10.f, 720.f / 2.f - 10.f); /* TODO: don't hardcode -10.f (radius) */

    Paddle enemy(100.f, 720.f / 2.f - enemy.getSize().y / 2);
    enemy.score_counter.setFont(font);
    Paddle player(1280.f - player.getSize().x - 100.f, 720.f / 2.f - player.getSize().y / 2); /* TODO: don't use play in initialization */
    player.score_counter.setFont(font);

    sf::Clock dtClock;
    sf::Time dt;
    
    sf::Text fpsCounter;
    fpsCounter.setFont(font);
    fpsCounter.setString("0");
    fpsCounter.setCharacterSize(36);
    fpsCounter.setFillColor(sf::Color::White);
    fpsCounter.setPosition(5.f, -5.f);
    int fps = 0;
    bool fpsVisible = 0;
    
    while (window.isOpen()) {
        dt = dtClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //keyboard input
            if (event.type == sf::Event::EventType::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                else if (event.key.code == sf::Keyboard::F1)
                    fpsVisible = !fpsVisible;
            }
        }
 
        //player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0.f, -192.f * dt.asSeconds());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0.f, 192.f * dt.asSeconds());

        //border check for player
        if (player.getPosition().y >= 720.f - player.getSize().y)
            player.setPosition(player.getPosition().x, 720.f - player.getSize().y);
        else if (player.getPosition().y <= 0.f)
            player.setPosition(player.getPosition().x, 0.f);
        
        //ball border check
        if (ball.getPosition().x <= 0.f) {
            //player wins
            player.score++;
            ball.setPosition(1280.f / 2.f - ball.getRadius(), 720.f / 2.f - ball.getRadius());

            //update score
            player.score_counter.setString(std::to_string(player.score));
        }
        else if (ball.getPosition().x >= 1280.f - ball.getRadius()) {
            //enemy wins
            enemy.score++;
            ball.setPosition(1280.f / 2.f - ball.getRadius(), 720.f / 2.f - ball.getRadius());

            //update score
            enemy.score_counter.setString(std::to_string(enemy.score));
        }
        if (ball.getPosition().y <= 0.f) {
            popSound.play();
            ball.speed_y *= -1.f;
        }
        else if (ball.getPosition().y >= 720.f - ball.getRadius()) {
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
            enemy.move(0.f, -192.f * dt.asSeconds());
        else
            enemy.move(0.f, 192.f * dt.asSeconds());
        
        //border check for enemy
        if (enemy.getPosition().y <= 0.f)
            enemy.setPosition(enemy.getPosition().x, 0.f);
        else if (enemy.getPosition().y + enemy.getSize().y >= 720.f)
            enemy.setPosition(enemy.getPosition().x, 720.f - enemy.getSize().y);

        fps = 1 / dt.asSeconds();
        fpsCounter.setString(std::to_string(fps) + " FPS");

        window.clear();
        
        window.draw(ball);
        window.draw(enemy);
        window.draw(player);

        //text
        window.draw(enemy.score_counter);
        window.draw(player.score_counter);
        if(fpsVisible)
            window.draw(fpsCounter); 
        
        window.display();
    }

    return 0;
}
