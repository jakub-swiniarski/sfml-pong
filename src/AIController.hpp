#ifndef AICONTROLLER_HPP
#define AICONTROLLER_HPP

class Ball;
class Paddle;

class AIController {
    const Ball&   ball;
    Paddle&       paddle;

public:
    AIController(Ball& ball, Paddle& paddle);
    void update(float mod) const;
};

#endif // AICONTROLLER_HPP
