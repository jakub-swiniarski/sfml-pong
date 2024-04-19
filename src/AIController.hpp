#ifndef AICONTROLLER_HPP
#define AICONTROLLER_HPP

class Ball;
class Paddle;

class AIController {
    Ball *ball;
    Paddle *paddle;

public:
    AIController(Ball *b, Paddle *p);
    void update(float mod) const;
};

#endif /* AICONTROLLER_HPP */
