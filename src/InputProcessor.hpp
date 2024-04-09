#ifndef INPUTPROCESSOR_HPP
#define INPUTPROCESSOR_HPP

class Paddle;

class InputProcessor {
    Paddle *player;

public:
    InputProcessor(Paddle *p);
    void update(float mod);
};

#endif /* INPUTPROCESSOR_HPP */
