#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

class Paddle;

class InputProcessor {
    Paddle *player;

public:
    InputProcessor(Paddle *p);
    void update(float mod);
};

#endif /* INPUTPROCESSOR_H */
