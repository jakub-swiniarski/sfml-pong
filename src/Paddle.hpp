#pragma once

class Paddle: public sf::RectangleShape {
public: /* TODO: THIS IS A TEMPORARY SOLUTION */
    int score;
    sf::Text score_counter;

    Paddle(float x, float y);
    bool ball_collision_check(Ball &ball);
};
