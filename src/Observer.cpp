#include <cstdlib>

#include "Ball.hpp"
#include "Observer.hpp"
#include "Paddle.hpp"

#include "config.hpp"

Observer::Observer(Ball *b, Paddle *p, Paddle *e) {
    ball = b;
    player = p;
    enemy = e;
}

void Observer::update(void) {
    if (player->ball_collision_check(ball)
    || enemy->ball_collision_check(ball))
        ball->bounce_paddle();

    if (ball->getPosition().x <= 0.f) {
        player->update_counter();
        ball->reset();
    } else if (ball->getPosition().x >= SCREEN_WIDTH - ball->getRadius()) {
        enemy->update_counter();
        ball->reset();
    }
}
