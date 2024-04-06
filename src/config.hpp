#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics/Color.hpp>

/* resolution */
static unsigned int SCREEN_WIDTH = 1280;
static unsigned int SCREEN_HEIGHT = 720;

/* framerate limit */
static unsigned int FPS = 60;

/* appearance */
static const sf::Color BALL_COLOR = sf::Color::Green;

/* gameplay */
static const float BALL_START_SPEED_X = 240.f;
static const float BALL_START_SPEED_Y = 240.f;
static const float ENEMY_SPEED_Y = 200.f;
static const float PLAYER_SPEED_Y = 200.f;
static const float BALL_RADIUS = 10.f;
static const float PADDLE_WIDTH = 20.f;
static const float PADDLE_HEIGHT = 100.f;
static const unsigned int FONT_SIZE = 120;

#endif /* CONFIG_HPP */
