#include "Ball.hpp"
#include "Observer.hpp"
#include "Paddle.hpp"

#include "config.hpp"

Observer::Observer(Ball *b, Paddle *e, Paddle *p) {
    ball = b;
    enemy = e;
    player = p;
}

void Observer::update(void) const {
    if (ball->getPosition().x <= 0.f) {
        player->update_counter();
        ball->reset();
    } else if (ball->getPosition().x >= screen_width - ball->getRadius()) {
        enemy->update_counter();
        ball->reset();
    }
}
