class Observer {
    Paddle *player, *enemy;
    Ball *ball;

public:
    Observer(void);
    void set_player(Paddle *p);
    void set_enemy(Paddle *e);
    void set_ball(Ball *b);
    void update(void);
}
