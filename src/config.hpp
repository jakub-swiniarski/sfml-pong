#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics/Color.hpp>

namespace cfg {
    namespace window {
        static constexpr unsigned int width = 1280;
        static constexpr unsigned int height = 720;
        static constexpr unsigned int fps = 60;
    }

    namespace counter {
        static constexpr unsigned int font_size = 120;
        static constexpr float shift_x = 300.f;
    }

    namespace ball {
        static const sf::Color color(255, 255, 255);
        static constexpr float radius = 10.f;
        static constexpr float speed_boost = 50.f;
        static constexpr float speed_x = 200.f;
        static constexpr float speed_y = 220.f;
    }

    namespace paddle {
        static constexpr float width = 20.f;
        static constexpr float height = 100.f;
    }

    namespace enemy {
        static const sf::Color color(255, 0, 0);
        static const sf::Color counter_color(255, 170, 170);
        static constexpr float speed_y = 200.f;
    }

    namespace player {
        static const sf::Color color(0, 255, 0);
        static const sf::Color counter_color(170, 255, 170);
        static constexpr float speed_y = 200.f;
    }
}

#endif // CONFIG_HPP
