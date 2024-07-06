#ifndef BALL_HPP
#define BALL_HPP

#include <vector.h>
#include <SDL2/SDL.h>
#include <constant.h>



class Ball {
    public:
    Ball(Vec2 pos, Vec2 vel): position(pos), velocity(vel){
        rect.x = static_cast<int> (position.x);
        rect.y = static_cast<int> (position.y);
        rect.w = BALL_WIDTH;
        rect.h = BALL_HEIGHT;
    }

    void Update(float dt){
        position += velocity * dt;
    }

    void CollideWithPaddle (Contact const& contact){
        position.x += contact.penetration;
        velocity.x = -velocity.x;

        if (contact.type == CollisionType::Top){
            velocity.y = -0.75 * BALL_SPEED;
        }
        else if (contact.type == CollisionType::Bottom){
            velocity.y = 0.75 * BALL_SPEED;
        }
    }

    void CollideWithWall(Contact const &contact)
    {
        if (contact.type == CollisionType::Top || contact.type == CollisionType::Bottom)
        {
            position.y += contact.penetration;
            velocity.y = -velocity.y;
        }
        else if (contact.type == CollisionType::Left)
        {
            position.x = WINDOW_WIDTH / 2.0f;
            position.y = WINDOW_HEIGHT / 2.0f;
            velocity.x = BALL_SPEED;
            velocity.y = 0.75f * BALL_SPEED;
        }
        else if (contact.type == CollisionType::Right)
        {
            position.x = WINDOW_WIDTH / 2.0f;
            position.y = WINDOW_HEIGHT / 2.0f;
            velocity.x = -BALL_SPEED;
            velocity.y = 0.75f * BALL_SPEED;
        }
    }

    void Draw(SDL_Renderer* renderer){
        rect.x = static_cast<int> (position.x);
        rect.y = static_cast<int> (position.y);
        SDL_RenderFillRect(renderer, &rect);
    }



    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect{};
};



#endif
