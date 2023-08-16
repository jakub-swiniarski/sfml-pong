#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong");
    
    //ball
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(1280.f/2.f-5.f,720.f/2.f+5.f);

    //enemy
    sf::RectangleShape enemy(sf::Vector2f(20.f, 100.f));
    enemy.setFillColor(sf::Color::White);
    enemy.setPosition(0.f,0.f);

    //player
    sf::RectangleShape player(sf::Vector2f(20.f, 100.f));
    player.setFillColor(sf::Color::White);
    player.setPosition(1280.f-20.f,0.f); 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        window.draw(ball);
        window.draw(enemy);
        window.draw(player);
        
        window.display();
    }

    return 0;
}
