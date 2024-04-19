#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Ball;
class Paddle;

class Observer {
    Paddle *player, *enemy;
    Ball *ball;

public:
    Observer(Ball *b, Paddle *e, Paddle *p);
    void update(void) const;
};

#endif /* OBSERVER_HPP */
