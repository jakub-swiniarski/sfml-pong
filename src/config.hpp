#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics/Color.hpp>

/* resolution */
static const unsigned int screen_width = 1280;
static const unsigned int screen_height = 720;

/* framerate limit */
static const unsigned int fps = 60;

/* appearance */
static const sf::Color ball_color(255, 255, 255);
static const sf::Color enemy_color(255, 0, 0);
static const sf::Color enemy_counter_color(255, 170, 170);
static const sf::Color player_color(0, 255, 0);
static const sf::Color player_counter_color(170, 255, 170);

/* gameplay */
static const unsigned int font_size = 120;
static const float ball_radius = 10.f;
static const float ball_speed_boost = 50.f;
static const float ball_start_speed_x = 200.f;
static const float ball_start_speed_y = 220.f;
static const float counter_shift_x = 300.f;
static const float enemy_speed_y = 200.f;
static const float player_speed_y = 200.f;
static const float paddle_width = 20.f;
static const float paddle_height = 100.f;

#endif /* CONFIG_HPP */
