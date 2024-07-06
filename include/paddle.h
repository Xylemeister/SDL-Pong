#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <vector.h>
#include <SDL2/SDL.h>
#include <constant.h>


class Paddle
{
public:
    Paddle(Vec2 pos, Vec2 vel) : position(pos), velocity(vel)
    {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        rect.w = PADDLE_WIDTH;
        rect.h = PADDLE_HEIGHT;
    }

    void Draw(SDL_Renderer* renderer){
        rect.y = static_cast<int>(position.y);
        SDL_RenderFillRect(renderer, &rect);
    }

    void Up(){
        velocity.y = -PADDLE_SPEED;
    }

    void Down(){
        velocity.y = PADDLE_SPEED;
    }

    void Stop(){
        velocity.y = 0.0f;
    }

    void Update (float dt){
        position += velocity * dt;
        
        if (position.y < 0){
            position.y = 0;
        }
        else if (position.y > (WINDOW_HEIGHT - PADDLE_HEIGHT)){
            position.y = WINDOW_HEIGHT - PADDLE_HEIGHT;
        }
    }

    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect{};
};

#endif