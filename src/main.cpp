#include <SDL2/SDL.h>
#include <stdio.h>
#include <ball.h>
#include <paddle.h>
#include <constant.h>
#include <chrono>

Contact CheckPaddleCollision(Ball const &ball, Paddle const &paddle)
{
    float ballLeft = ball.position.x;
    float ballRight = ball.position.x + BALL_WIDTH;
    float ballTop = ball.position.y;
    float ballBottom = ball.position.y + BALL_HEIGHT;

    float paddleLeft = paddle.position.x;
    float paddleRight = paddle.position.x + PADDLE_WIDTH;
    float paddleTop = paddle.position.y;
    float paddleBottom = paddle.position.y + PADDLE_HEIGHT;

    Contact contact{};

    if (ballLeft >= paddleRight)
    {
        return contact;
    }

    if (ballRight <= paddleLeft)
    {
        return contact;
    }

    if (ballTop >= paddleBottom)
    {
        return contact;
    }

    if (ballBottom <= paddleTop)
    {
        return contact;
    }

    float paddleRangeUpper = paddleBottom - (2.0f * PADDLE_HEIGHT / 3.0f);
    float paddleRangeMiddle = paddleBottom - (PADDLE_HEIGHT / 3.0f);

    if (ball.velocity.x < 0)
    {
        // Left paddle
        contact.penetration = paddleRight - ballLeft;
    }
    else if (ball.velocity.x > 0)
    {
        // Right paddle
        contact.penetration = paddleLeft - ballRight;
    }

    if ((ballBottom > paddleTop) && (ballBottom < paddleRangeUpper))
    {
        contact.type = CollisionType::Top;
    }
    else if ((ballBottom > paddleRangeUpper) && (ballBottom < paddleRangeMiddle))
    {
        contact.type = CollisionType::Middle;
    }
    else
    {
        contact.type = CollisionType::Bottom;
    }

    return contact;
}

Contact CheckWallCollision(Ball const& ball){
    float ballLeft = ball.position.x;
    float ballRight = ball.position.x + BALL_WIDTH;
    float ballTop = ball.position.y;
    float ballBottom = ball.position.y + BALL_HEIGHT;

    Contact contact {};

    if (ballLeft < 0.0f){
        contact.type = CollisionType::Left;
    }
    else if (ballRight > WINDOW_WIDTH){
        contact.type = CollisionType::Right;
    }

    else if (ballTop < 0.0f){
        contact.type = CollisionType::Top;
        contact.penetration = -ballTop;
    }
    else if (ballBottom > WINDOW_HEIGHT){
        contact.type = CollisionType::Bottom;
        contact.penetration = WINDOW_HEIGHT - ballBottom;
    }

    return contact;
}

int main()
{
    // initialize SDL components
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Ball ball (Vec2((WINDOW_WIDTH / 2.0f) - (BALL_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f)- (BALL_HEIGHT / 2.0f)), Vec2(BALL_SPEED, 0));
    Paddle paddleOne (Vec2(50.0f, (WINDOW_HEIGHT / 2.0f) - PADDLE_HEIGHT/2), Vec2(0.0f , 0.0f));
    Paddle paddleTwo (Vec2(WINDOW_WIDTH - 50.0f, (WINDOW_HEIGHT / 2.0f) - PADDLE_HEIGHT/2), Vec2(0.0f, 0.0f));

    {
        bool running = true;
        bool buttons[4] = {};

        float dt = 0.0f;

        while (running)
        {
            auto startTime = std::chrono ::high_resolution_clock ::now();
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN)
                {

                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    case SDLK_w:
                        buttons[Buttons::PaddleOneUp] = true;
                        break;
                    case SDLK_s:
                        buttons[Buttons::PaddleOneDown] = true;
                        break;
                    case SDLK_i:
                        buttons[Buttons::PaddleTwoUp] = true;
                        break;
                    case SDLK_k:
                        buttons[Buttons::PaddleTwoDown] = true;
                        break;
                    }
                }
                else if (event.type == SDL_KEYUP)
                {

                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    case SDLK_w:
                        buttons[Buttons::PaddleOneUp] = false;
                        break;
                    case SDLK_s:
                        buttons[Buttons::PaddleOneDown] = false;
                        break;
                    case SDLK_i:
                        buttons[Buttons::PaddleTwoUp] = false;
                        break;
                    case SDLK_k:
                        buttons[Buttons::PaddleTwoDown] = false;
                        break;
                    }
                }
            }

            if (buttons[Buttons:: PaddleOneUp]){
                paddleOne.Up();
            }
            else if (buttons[Buttons:: PaddleOneDown]){
                paddleOne.Down();
            }
            else {
                paddleOne.Stop();
            }

            if (buttons[Buttons::PaddleTwoUp]){
                paddleTwo.Up();
            }
            else if (buttons[Buttons::PaddleTwoDown]){
                paddleTwo.Down();
            }
            else{
                paddleTwo.Stop();
            }

            paddleOne.Update(dt);
            paddleTwo.Update(dt);
            ball.Update(dt);

            // if (CheckPaddleCollision(ball, paddleOne) || CheckPaddleCollision(ball, paddleTwo)){
            //     ball.velocity.x = - ball.velocity.x;
            // }
            Contact contact1 = CheckPaddleCollision(ball, paddleOne);
            Contact contact2 = CheckPaddleCollision(ball, paddleTwo);

            if (contact1.type != CollisionType::None){
                ball.CollideWithPaddle(contact1);
            }
            else if (contact2.type != CollisionType::None){
                ball.CollideWithPaddle(contact2);
            }

            Contact contact = CheckWallCollision(ball);

            if (contact.type != CollisionType::None){
                ball.CollideWithWall(contact);
            }
          

            SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
            SDL_RenderClear(renderer);
            
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            for (int y = 0; y < WINDOW_HEIGHT; y++){
                
                if (y % 5){
                    SDL_RenderDrawPoint(renderer, WINDOW_WIDTH >> 1, y);
                }
            }

            ball.Draw(renderer);
            paddleOne.Draw(renderer);
            paddleTwo.Draw(renderer);

            SDL_RenderPresent(renderer);
            auto stopTime = std:: chrono :: high_resolution_clock :: now();
            dt = std:: chrono :: duration <float, std:: chrono :: milliseconds :: period >(stopTime - startTime).count();
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}