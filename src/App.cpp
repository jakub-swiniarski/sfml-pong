#include <stdexcept>

#include "App.hpp"
#include "EventHandler.hpp"

#include "config.hpp"

void App::setup(void) {
    window.setFramerateLimit(cfg::window::fps);

    if (!font_digital.loadFromFile(res_path + "digital.ttf"))
        throw std::runtime_error("Failed to load font.");

    enemy.get_counter().setFont(font_digital);
    player.get_counter().setFont(font_digital);

    enemy.get_counter().setPosition(cfg::counter::offset_x, 0.0f); 
    player.get_counter().setPosition(cfg::window::width - cfg::counter::offset_x - player.get_counter().getGlobalBounds().width, 0.0f);

    if (!sound_buffer_pop.loadFromFile(res_path + "pop.wav"))
        throw std::runtime_error("Failed to load sound.");
}

void App::run(void) {
    sf::Clock      dt_clock;
    AIController   ai_controller(ball, enemy);
    EventHandler   event_handler(window);
    InputProcessor input_processor(player);
    Observer       observer(ball, enemy, player, sound_buffer_pop);

    while (window.isOpen()) {
        float dt = dt_clock.restart().asSeconds();

        ai_controller.update(dt);
        ball.update(dt);
        event_handler.update();
        input_processor.update(dt);
        observer.update();

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
      enemy(cfg::paddle::offset_x, cfg::window::height / 2.0f - cfg::paddle::height / 2.0f, cfg::enemy::color, cfg::enemy::counter_color),
      player(cfg::window::width - cfg::paddle::width - cfg::paddle::offset_x, cfg::window::height / 2.0f - cfg::paddle::height / 2.0f, cfg::player::color, cfg::player::counter_color) {
    setup();
    run();
}
