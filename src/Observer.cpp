#include <cstdlib>

#include "Ball.hpp"
#include "Observer.hpp"
#include "Paddle.hpp"

Observer::Observer(Ball *b, Paddle *p, Paddle *e) {
    ball = b;
    player = p;
    enemy = e;
}

void Observer::update(void) {
    if (player->ball_collision_check(ball)
    || enemy->ball_collision_check(ball)) {
        ball->bounce_paddle();
    }
}
