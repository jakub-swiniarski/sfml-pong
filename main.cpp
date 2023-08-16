#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong");
    
    //ball
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(1280.f/2.f-ball.getRadius(),720.f/2.f-ball.getRadius());

    //enemy
    sf::RectangleShape enemy(sf::Vector2f(20.f, 100.f));
    enemy.setFillColor(sf::Color::White);
    enemy.setPosition(100.f,720.f/2.f-enemy.getSize().y/2);

    //player
    sf::RectangleShape player(sf::Vector2f(20.f, 100.f));
    player.setFillColor(sf::Color::White);
    player.setPosition(1280.f-player.getSize().x-100.f,720.f/2.f-player.getSize().y/2); 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }
        //GET DELTATIME!!!
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player.move(0.f,-1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player.move(0.f,1.f);
        }

        //border check for player
        if(player.getPosition().y>=720.f-player.getSize().y){
            player.setPosition(player.getPosition().x,720.f-player.getSize().y);
        }
        if(player.getPosition().y<=0){
            player.setPosition(player.getPosition().x,0);
        }
 

        window.clear();
        
        window.draw(ball);
        window.draw(enemy);
        window.draw(player);
        
        window.display();
    }

    return 0;
}
