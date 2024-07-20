#include "App.hpp"
#include "EventHandler.hpp"

#include "config.hpp"
#include <stdexcept>

void App::setup(void) {
    window.setFramerateLimit(cfg::window::fps);

    if (!font.loadFromFile(res_path + "font.ttf"))
        throw std::runtime_error("Failed to load font.");
    enemy.get_counter().setFont(font);
    player.get_counter().setFont(font);

    enemy.get_counter().setPosition(cfg::counter::shift_x, 0.0f); 
    player.get_counter().setPosition(cfg::window::width - cfg::counter::shift_x - player.get_counter().getGlobalBounds().width, 0.0f);

    if (!pop_buffer.loadFromFile(res_path + "pop.wav"))
        throw std::runtime_error("Failed to load sound.");
    pop_sound.setBuffer(pop_buffer);
}

void App::run(void) {
    AIController ai_controller(&ball, &enemy);
    sf::Clock dt_clock;
    EventHandler event_handler(&window);
    InputProcessor input_processor(&player);
    Observer observer(&ball, &enemy, &player);

    while (window.isOpen()) {
        float dt = dt_clock.restart().asSeconds();

        ai_controller.update(dt);
        ball.update(dt);
        event_handler.update();
        input_processor.update(dt);
        observer.update();
        
        enemy.border_check();
        player.border_check();

        if (ball.border_check() ||
            enemy.ball_collision_check(ball) ||
            player.ball_collision_check(ball))
            pop_sound.play();
        
        draw();
    }
}

void App::draw(void) {
    window.clear();
    
    window.draw(ball);
    window.draw(enemy);
    window.draw(player);

    window.draw(enemy.get_counter());
    window.draw(player.get_counter());
    
    window.display();
}

App::App(void) 
    : window(sf::VideoMode(cfg::window::width, cfg::window::height), "Pong", sf::Style::None),
      ball(cfg::window::width / 2.0f - cfg::ball::radius, cfg::window::height / 2.0f - cfg::ball::radius),
      enemy(100.0f, cfg::window::height / 2.0f - cfg::paddle::height / 2.0f, cfg::enemy::color, cfg::enemy::counter_color),
      player(cfg::window::width - cfg::paddle::width - 100.0f, cfg::window::height / 2.0f - cfg::paddle::height / 2.0f, cfg::player::color, cfg::player::counter_color) {
    setup();
    run();
}
