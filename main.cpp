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

#include "Paddle.hpp"

#include "config.hpp"

int speedX = 240;
int speedY = 240;

bool ballRectangleCollision(sf::CircleShape ball, sf::RectangleShape rect) {
    if (ball.getPosition().y <= rect.getPosition().y + rect.getSize().y && ball.getPosition().y + ball.getRadius() >= rect.getPosition().y) {
        if (ball.getPosition().x + ball.getRadius() >= rect.getPosition().x && ball.getPosition().x + ball.getRadius() < rect.getPosition().x + rect.getSize().x / 2) {
            speedX *= -1;
            return 1;
        } else if (ball.getPosition().x <= rect.getPosition().x + rect.getSize().x && ball.getPosition().x > rect.getPosition().x + rect.getSize().x / 2) {
            speedX *= -1;
            return 1;
        }    
    }
    return 0;
}

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

    sf::CircleShape ball(10.f);
    ball.setFillColor(BALL_COLOR);
    ball.setPosition(1280.f / 2.f - ball.getRadius(), 720.f / 2.f - ball.getRadius());    

    Paddle enemy(100.f, 720.f / 2.f - enemy.shape.getSize().y / 2);
    enemy.score_counter.setFont(font);
    Paddle player(1280.f - player.shape.getSize().x - 100.f, 720.f / 2.f - player.shape.getSize().y / 2);
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
            player.shape.move(0.f, -192.f * dt.asSeconds());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.shape.move(0.f, 192.f * dt.asSeconds());

        //border check for player
        if (player.shape.getPosition().y >= 720.f - player.shape.getSize().y)
            player.shape.setPosition(player.shape.getPosition().x, 720.f - player.shape.getSize().y);
        else if (player.shape.getPosition().y <= 0.f)
            player.shape.setPosition(player.shape.getPosition().x, 0.f);
        
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
            speedY *= -1.f;
        }
        else if (ball.getPosition().y >= 720.f - ball.getRadius()) {
            popSound.play(); 
            speedY *= -1.f;
        } 

        //ball movement
        ball.move(speedX * dt.asSeconds(), speedY * dt.asSeconds()); 

        //ball collisions with entities
        if (ballRectangleCollision(ball, enemy.shape))
            popSound.play();
        else if (ballRectangleCollision(ball, player.shape))
            popSound.play();

        //enemy movement
        if (enemy.shape.getPosition().y + enemy.shape.getSize().y / 2.f > ball.getPosition().y + ball.getRadius() / 2.f)
            enemy.shape.move(0.f, -192.f * dt.asSeconds());
        else
            enemy.shape.move(0.f, 192.f * dt.asSeconds());
        
        //border check for enemy
        if (enemy.shape.getPosition().y <= 0.f)
            enemy.shape.setPosition(enemy.shape.getPosition().x, 0.f);
        else if (enemy.shape.getPosition().y + enemy.shape.getSize().y >= 720.f)
            enemy.shape.setPosition(enemy.shape.getPosition().x, 720.f - enemy.shape.getSize().y);

        fps = 1 / dt.asSeconds();
        fpsCounter.setString(std::to_string(fps) + " FPS");

        window.clear();
        
        window.draw(ball);
        window.draw(enemy.shape);
        window.draw(player.shape);

        //text
        window.draw(enemy.score_counter);
        window.draw(player.score_counter);
        if(fpsVisible)
            window.draw(fpsCounter); 
        
        window.display();
    }

    return 0;
}
