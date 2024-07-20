#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Ball;
class Paddle;

class Observer {
    Paddle* player;
    Paddle* enemy;
    Ball* ball;

public:
    Observer(Ball* ball, Paddle* enemy, Paddle* player);
    
    void update(void) const;
};

#endif // OBSERVER_HPP
