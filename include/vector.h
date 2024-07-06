#ifndef VECTOR_HPP
#define VECTOR_HPP

// class for 2-dimensional vector
class Vec2
{
public:
    // initialization
    Vec2() : x(0.0f), y(0.0f) {};
    Vec2(float x, float y) : x(x), y(y) {};

    // useful operation
    Vec2 operator+(Vec2 const &vector)
    {
        return Vec2(x + vector.x, y + vector.y);
    }

    Vec2 *operator+=(Vec2 const &vector)
    {
        x += vector.x;
        y += vector.y;

        return this;
    }

    Vec2 operator*(Vec2 const &vector)
    {
        return Vec2(x * vector.x, y * vector.y);
    }

    Vec2 operator*(float const &constant){
        return Vec2(x * constant, y * constant);
    }

    float x, y;
};

#endif