#include <SFML/Graphics.hpp>

float speedX=0.5;
float speedY=0.5;

void ballRectangleCollision(sf::CircleShape ball, sf::RectangleShape rect){
    if(ball.getPosition().y<rect.getPosition().y+rect.getSize().y && ball.getPosition().y+ball.getRadius()>rect.getPosition().y){
        //check horizontal collisions
        if(ball.getPosition().x+ball.getRadius()>=rect.getPosition().x && ball.getPosition().x+ball.getRadius()<rect.getPosition().x+rect.getSize().x/2){
            speedX*=-1;
        }
        else if(ball.getPosition().x<=rect.getPosition().x+rect.getSize().x && ball.getPosition().x>rect.getPosition().x+rect.getSize().x/2){
            speedX*=-1;
        }

        //check vertical collisions!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
}


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong", sf::Style::Default, settings);

    sf::Font digital; //CHECK IF THE FILE IS PRESENT!!!!!!
    digital.loadFromFile("digital.ttf");

    //ball
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(1280.f/2.f-ball.getRadius(),720.f/2.f-ball.getRadius());    

    //enemy
    sf::RectangleShape enemy(sf::Vector2f(20.f, 100.f));
    enemy.setFillColor(sf::Color::White);
    enemy.setPosition(100.f,720.f/2.f-enemy.getSize().y/2);
    int enemyPoints=0;
    sf::Text enemyCounter;
    enemyCounter.setFont(digital);
    enemyCounter.setString("0");
    enemyCounter.setCharacterSize(120);
    enemyCounter.setFillColor(sf::Color::White);
    enemyCounter.setPosition(300,0);

    //player
    sf::RectangleShape player(sf::Vector2f(20.f, 100.f));
    player.setFillColor(sf::Color::White);
    player.setPosition(1280.f-player.getSize().x-100.f,720.f/2.f-player.getSize().y/2); 
    int playerPoints=0;
    sf::Text playerCounter;
    playerCounter.setFont(digital);
    playerCounter.setString("0");
    playerCounter.setCharacterSize(120);
    playerCounter.setFillColor(sf::Color::White);
    playerCounter.setPosition(1280-300-120,0);

    
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
            player.move(0.f,-0.4);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player.move(0.f,0.4);
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
            //update score
            playerCounter.setString(std::to_string(playerPoints));
        }
        else if(ball.getPosition().x>=1280-ball.getRadius()){
            //enemy wins
            enemyPoints++;
            ball.setPosition(1280.f/2.f-ball.getRadius(),720.f/2.f-ball.getRadius());
            //update score
            enemyCounter.setString(std::to_string(enemyPoints));
        }
        if(ball.getPosition().y<=0){
            speedY*=-1;
        }
        else if(ball.getPosition().y>=720-ball.getRadius()){
            speedY*=-1;
        }

        //ball collisions with entities
        ballRectangleCollision(ball,enemy);
        ballRectangleCollision(ball,player);

        //enemy movement
        if(enemy.getPosition().y+enemy.getSize().y/2>ball.getPosition().y+ball.getRadius()/2){
            enemy.move(0.f,-0.4);
        }
        else{
            enemy.move(0.f,0.4);
        }

        //border check for enemy
        if(enemy.getPosition().y<=0){
            enemy.setPosition(enemy.getPosition().x,0);
        }
        else if(enemy.getPosition().y+enemy.getSize().y>=720){
            enemy.setPosition(enemy.getPosition().x,720-enemy.getSize().y);
        }

        window.clear();
        
        window.draw(ball);
        window.draw(enemy);
        window.draw(player);

        //text
        window.draw(enemyCounter);
        window.draw(playerCounter);
        
        window.display();
    }

    return 0;
}
