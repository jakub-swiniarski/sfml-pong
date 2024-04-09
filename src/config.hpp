#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics/Color.hpp>

/* resolution */
static const unsigned int SCREEN_WIDTH = 1280;
static const unsigned int SCREEN_HEIGHT = 720;

/* framerate limit */
static const unsigned int FPS = 60;

/* appearance */
static const sf::Color BALL_COLOR(255, 255, 255); /* R, G, B */
static const sf::Color ENEMY_COLOR(255, 0, 0);
static const sf::Color ENEMY_COUNTER_COLOR(255, 170, 170);
static const sf::Color PLAYER_COLOR(0, 255, 0);
static const sf::Color PLAYER_COUNTER_COLOR(170, 255, 170);

/* gameplay */
static const unsigned int FONT_SIZE = 120;
static const float BALL_RADIUS = 10.f;
static const float BALL_SPEED_BOOST = 50.f;
static const float BALL_START_SPEED_X = 240.f;
static const float BALL_START_SPEED_Y = 240.f;
static const float COUNTER_SHIFT_X = 300.f;
static const float ENEMY_SPEED_Y = 200.f;
static const float PLAYER_SPEED_Y = 200.f;
static const float PADDLE_WIDTH = 10.f;
static const float PADDLE_HEIGHT = 100.f;

#endif /* CONFIG_HPP */
