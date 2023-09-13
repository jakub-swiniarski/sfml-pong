#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <SFML/System/Time.hpp>

#include <string>

short speedX=240;
short speedY=240;

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
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong", sf::Style::Fullscreen, settings);

    std::string filepath="assets_pong/";

    //font
    sf::Font digital;
    if(!digital.loadFromFile(filepath+"digital.ttf")){ 
        window.close();
    }

    //sound
    sf::SoundBuffer popBuffer;
    if(!popBuffer.loadFromFile(filepath+"pop.wav")){ 
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
    u_int8_t enemyPoints=0;
    sf::Text enemyCounter;
    enemyCounter.setFont(digital);
    enemyCounter.setString("0");
    enemyCounter.setCharacterSize(120);
    enemyCounter.setFillColor(sf::Color::White);
    enemyCounter.setPosition(300.f,0.f);

    //player
    sf::RectangleShape player(sf::Vector2f(20.f, 100.f));
    player.setFillColor(sf::Color::White);
    player.setPosition(1280.f-player.getSize().x-100.f,720.f/2.f-player.getSize().y/2); 
    u_int8_t playerPoints=0;
    sf::Text playerCounter;
    playerCounter.setFont(digital);
    playerCounter.setString("0");
    playerCounter.setCharacterSize(120);
    playerCounter.setFillColor(sf::Color::White);
    playerCounter.setPosition(1280.f-300.f-120.f,0.f);

    sf::Clock dtClock;
    sf::Time dt;
    
    //fps counter - turn this into a class
    sf::Text fpsCounter;
    fpsCounter.setFont(digital);
    fpsCounter.setString("0");
    fpsCounter.setCharacterSize(36);
    fpsCounter.setFillColor(sf::Color::White);
    fpsCounter.setPosition(5.f,-5.f);
    unsigned short fps=0;
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
                }
            }
        }
 
        //player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player.move(0.f,-192.f*dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player.move(0.f,192.f*dt.asSeconds());
        }

        //border check for player
        if(player.getPosition().y>=720.f-player.getSize().y){
            player.setPosition(player.getPosition().x,720.f-player.getSize().y);
        }
        else if(player.getPosition().y<=0.f){
            player.setPosition(player.getPosition().x,0.f);
        }
        
        //ball border check
        if(ball.getPosition().x<=0.f){
            //player wins
            playerPoints++;
            ball.setPosition(1280.f/2.f-ball.getRadius(),720.f/2.f-ball.getRadius());

            //update score
            playerCounter.setString(std::to_string(playerPoints));
        }
        else if(ball.getPosition().x>=1280.f-ball.getRadius()){
            //enemy wins
            enemyPoints++;
            ball.setPosition(1280.f/2.f-ball.getRadius(),720.f/2.f-ball.getRadius());

            //update score
            enemyCounter.setString(std::to_string(enemyPoints));
        }
        if(ball.getPosition().y<=0.f){
            popSound.play();
            speedY*=-1.f;
        }
        else if(ball.getPosition().y>=720.f-ball.getRadius()){
            popSound.play(); 
            speedY*=-1.f;
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
        if(enemy.getPosition().y+enemy.getSize().y/2.f>ball.getPosition().y+ball.getRadius()/2.f){
            enemy.move(0.f,-192.f*dt.asSeconds());
        }
        else{
            enemy.move(0.f,192.f*dt.asSeconds());
        }
        
        //border check for enemy
        if(enemy.getPosition().y<=0.f){
            enemy.setPosition(enemy.getPosition().x,0.f);
        }
        else if(enemy.getPosition().y+enemy.getSize().y>=720.f){
            enemy.setPosition(enemy.getPosition().x,720.f-enemy.getSize().y);
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
        if(fpsVisible){
            window.draw(fpsCounter); 
        } 
        
        window.display();
    }

    return 0;
}
