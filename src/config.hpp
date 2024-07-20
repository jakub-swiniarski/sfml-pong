#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics/Color.hpp>

namespace cfg {
    namespace window {
        inline constexpr unsigned int width  = 1280;
        inline constexpr unsigned int height = 720;
        inline constexpr unsigned int fps    = 60;
    }

    namespace counter {
        inline constexpr unsigned int font_size = 120;
        inline constexpr float        shift_x   = 300.0f;
    }

    namespace ball {
        inline const sf::Color color(255, 255, 255);
        inline constexpr float radius      = 10.0f;
        inline constexpr float speed_boost = 50.0f;
        inline constexpr float speed_x     = 200.0f;
        inline constexpr float speed_y     = 220.0f;
    }

    namespace paddle {
        inline constexpr float width  = 20.0f;
        inline constexpr float height = 100.0f;
    }

    namespace enemy {
        inline const sf::Color color(255, 0, 0);
        inline const sf::Color counter_color(255, 170, 170);
        inline constexpr float speed_y = 200.0f;
    }

    namespace player {
        inline const sf::Color color(0, 255, 0);
        inline const sf::Color counter_color(170, 255, 170);
        inline constexpr float speed_y = 200.0f;
    }
}

#endif // CONFIG_HPP
