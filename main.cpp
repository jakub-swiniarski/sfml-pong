#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <cmath>

float speedX=240;
float speedY=240;

bool ballRectangleCollision(sf::CircleShape ball, sf::RectangleShape rect){
    if(ball.getPosition().y<=rect.getPosition().y+rect.getSize().y && ball.getPosition().y+ball.getRadius()>=rect.getPosition().y){
        //check horizontal collisions
        if(ball.getPosition().x+ball.getRadius()>=rect.getPosition().x && ball.getPosition().x+ball.getRadius()<rect.getPosition().x+rect.getSize().x/2){
            speedX*=-1;
            return 1;
        }
        else if(ball.getPosition().x<=rect.getPosition().x+rect.getSize().x && ball.getPosition().x>rect.getPosition().x+rect.getSize().x/2){
            speedX*=-1;
            return 1;
        }    
    }
    /*if(ball.getPosition().x+ball.getRadius()>rect.getPosition().x && ball.getPosition().x<rect.getPosition().x+rect.getSize().x){
        //check vertical collisions
        if(ball.getPosition().y<=rect.getPosition().y+rect.getSize().y && ball.getPosition().y>rect.getPosition().y+rect.getSize().y/2){
            speedY*=-1;
        }
        else if(ball.getPosition().y-ball.getRadius()<=rect.getPosition().y+rect.getSize().y && ball.getPosition().y-ball.getRadius()>rect.getPosition().y-rect.getSize().y){
            speedY*=-1;
        }
    }*/
    return 0;
}

int main()
{
    sf::ContextSettings *settings;
    settings=new sf::ContextSettings;
    settings->antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong", sf::Style::Default, *settings);
    
    delete settings;

    //font
    sf::Font digital;
    if(!digital.loadFromFile("digital.ttf")){
        window.close();
    }

    //sound
    sf::SoundBuffer popBuffer;
    if(!popBuffer.loadFromFile("assets/pop.wav")){
        window.close();
    }
    sf::Sound popSound;
    popSound.setBuffer(popBuffer);

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

    sf::Clock dtClock;
    sf::Time dt;
    
    //fps counter - turn this into a class
    sf::Text fpsCounter;
    fpsCounter.setFont(digital);
    fpsCounter.setString("0");
    fpsCounter.setCharacterSize(0);
    fpsCounter.setFillColor(sf::Color::White);
    fpsCounter.setPosition(5,-5);
    int fps=0;
    bool fpsVisible = 0;
    
    while (window.isOpen())
    {
        dt=dtClock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //keyboard input - single keypress
            if(event.type==sf::Event::EventType::KeyPressed){
                if(event.key.code==sf::Keyboard::Escape){
                    window.close();
                }    
                else if(event.key.code==sf::Keyboard::F1){
                    fpsVisible=!fpsVisible;
                    if(fpsVisible){
                        fpsCounter.setCharacterSize(36);
                    }
                    else{
                        fpsCounter.setCharacterSize(0);
                    } 
                }
            }
        }
 
        //player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player.move(0.f,-192*dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player.move(0.f,192*dt.asSeconds());
        }

        //border check for player
        if(player.getPosition().y>=720.f-player.getSize().y){
            player.setPosition(player.getPosition().x,720.f-player.getSize().y);
        }
        else if(player.getPosition().y<=0){
            player.setPosition(player.getPosition().x,0);
        }
        
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
            popSound.play();
            speedY*=-1;
        }
        else if(ball.getPosition().y>=720-ball.getRadius()){
            popSound.play(); 
            speedY*=-1;
        } 

        //ball movement
        ball.move(speedX*dt.asSeconds(),speedY*dt.asSeconds()); 

        //ball collisions with entities
        if(ballRectangleCollision(ball,enemy)){
            popSound.play();
        }
        else if(ballRectangleCollision(ball,player)){
            popSound.play();
        }

        //enemy movement
        if(enemy.getPosition().y+enemy.getSize().y/2>ball.getPosition().y+ball.getRadius()/2){
            enemy.move(0.f,-192*dt.asSeconds());
        }
        else{
            enemy.move(0.f,192*dt.asSeconds());
        }
        
        //border check for enemy
        if(enemy.getPosition().y<=0){
            enemy.setPosition(enemy.getPosition().x,0);
        }
        else if(enemy.getPosition().y+enemy.getSize().y>=720){
            enemy.setPosition(enemy.getPosition().x,720-enemy.getSize().y);
        }

        fps=1/dt.asSeconds();
        fpsCounter.setString(std::to_string(fps)+" FPS");

        window.clear();
        
        window.draw(ball);
        window.draw(enemy);
        window.draw(player);

        //text
        window.draw(enemyCounter);
        window.draw(playerCounter);
        window.draw(fpsCounter);
        
        window.display();
    }

    return 0;
}
