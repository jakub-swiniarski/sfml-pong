#include "Ball.hpp"
#include "Observer.hpp"
#include "Paddle.hpp"

#include "config.hpp"

Observer::Observer(Ball* ball, Paddle* enemy, Paddle* player, sf::SoundBuffer& sound_buffer)
    : ball(ball),
      enemy(enemy),
      player(player) {
    sound_pop.setBuffer(sound_buffer);
}

void Observer::update(void) {
    if (ball->getPosition().x <= 0.0f) {
        player->update_counter();
        ball->reset();
    } else if (ball->getPosition().x >= cfg::window::width - ball->getRadius()) {
        enemy->update_counter();
        ball->reset();
    }

    if (ball->border_check() ||
        enemy->ball_collision_check(*ball) ||
        player->ball_collision_check(*ball))
        sound_pop.play();
}
