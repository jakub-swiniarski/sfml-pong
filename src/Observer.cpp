#include "Ball.hpp"
#include "Observer.hpp"
#include "Paddle.hpp"

#include "config.hpp"

Observer::Observer(Ball* ball, Paddle* enemy, Paddle* player)
    : ball(ball),
      enemy(enemy),
      player(player) {}

void Observer::update(void) const {
    if (ball->getPosition().x <= 0.0f) {
        player->update_counter();
        ball->reset();
    } else if (ball->getPosition().x >= cfg::window::width - ball->getRadius()) {
        enemy->update_counter();
        ball->reset();
    }
}
