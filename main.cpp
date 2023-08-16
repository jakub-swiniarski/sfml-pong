#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong");
    
    //ball
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(1280.f/2.f-ball.getRadius(),720.f/2.f-ball.getRadius());
    float speedX=0.5;
    float speedY=0.5;

    //enemy
    sf::RectangleShape enemy(sf::Vector2f(20.f, 100.f));
    enemy.setFillColor(sf::Color::White);
    enemy.setPosition(100.f,720.f/2.f-enemy.getSize().y/2);
    int enemyPoints=0;

    //player
    sf::RectangleShape player(sf::Vector2f(20.f, 100.f));
    player.setFillColor(sf::Color::White);
    player.setPosition(1280.f-player.getSize().x-100.f,720.f/2.f-player.getSize().y/2); 
    int playerPoints=0;

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
        else if(player.getPosition().y<=0){
            player.setPosition(player.getPosition().x,0);
        }

        //ball movement
        ball.move(speedX,speedY);

        //ball border check
        if(ball.getPosition().x<=0){
            //player wins
            playerPoints++;
            ball.setPosition(1280.f/2.f-ball.getRadius(),720.f/2.f-ball.getRadius()); 
        }
        else if(ball.getPosition().x>=1280-ball.getRadius()){
            //enemy wins
            enemyPoints++;
            ball.setPosition(1280.f/2.f-ball.getRadius(),720.f/2.f-ball.getRadius());
        }
        if(ball.getPosition().y<=0){
            speedY*=-1;
        }
        else if(ball.getPosition().y>=720-ball.getRadius()){
            speedY*=-1;
        }

        window.clear();
        
        window.draw(ball);
        window.draw(enemy);
        window.draw(player);
        
        window.display();
    }

    return 0;
}
