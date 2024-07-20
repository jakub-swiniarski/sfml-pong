#ifndef INPUTPROCESSOR_HPP
#define INPUTPROCESSOR_HPP

class Paddle;

class InputProcessor {
    Paddle& paddle;

public:
    InputProcessor(Paddle& paddle);

    void update(float mod) const;
};

#endif // INPUTPROCESSOR_HPP
