#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Ball;
class Paddle;

class Observer {
    Paddle *player, *enemy;
    Ball *ball;

public:
    Observer(void);
    void set_player(Paddle *p);
    void set_enemy(Paddle *e);
    void set_ball(Ball *b);
    void update(void);
};

#endif /* OBSERVER_HPP */
