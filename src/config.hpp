#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics/Color.hpp>

/* resolution */
static const unsigned int SCREEN_WIDTH = 1280;
static const unsigned int SCREEN_HEIGHT = 720;

/* framerate limit */
static const unsigned int FPS = 60;

/* appearance */
static const sf::Color BALL_COLOR = sf::Color::Green;
static const sf::Color ENEMY_COLOR = sf::Color::Red;
static const sf::Color ENEMY_COUNTER_COLOR = sf::Color::Magenta;
static const sf::Color PLAYER_COLOR = sf::Color::Yellow;
static const sf::Color PLAYER_COUNTER_COLOR = sf::Color::Blue;

/* gameplay */
static const unsigned int FONT_SIZE = 120;
static const float BALL_RADIUS = 10.f;
static const float BALL_START_SPEED_X = 240.f;
static const float BALL_START_SPEED_Y = 240.f;
static const float COUNTER_SHIFT_X = 300.f;
static const float ENEMY_SPEED_Y = 200.f;
static const float PLAYER_SPEED_Y = 200.f;
static const float PADDLE_WIDTH = 20.f;
static const float PADDLE_HEIGHT = 100.f;

#endif /* CONFIG_HPP */
