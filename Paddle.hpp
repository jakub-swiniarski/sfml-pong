#pragma once

class Paddle {
public: /* TODO: THIS IS A TEMPORARY SOLUTION */
    sf::RectangleShape shape;
    int score;
    sf::Text score_counter;

    Paddle(float x, float y, sf::Font font);
};
