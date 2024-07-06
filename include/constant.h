#ifndef CONSTANT_H
#define CONSTANT_H

enum Buttons
{
    PaddleOneUp = 0,
    PaddleOneDown,
    PaddleTwoUp,
    PaddleTwoDown,
};

enum class CollisionType{
    None,
    Top,
    Middle,
    Bottom,
    Left,
    Right
};

struct Contact{
    CollisionType type;
    float penetration;
};

const float BALL_SPEED = 0.5f;

const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 100;
const float PADDLE_SPEED = 1.0f;

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int WINDOW_WIDTH_USER = 1920;
const int WINDOW_HEIGHT_USER = 1080;

#endif