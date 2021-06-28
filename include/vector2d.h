#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>


class Vector2D
{
public:
    Vector2D(float x, float y);

    float x() const;
    float y() const;

    void setX(float x);
    void setY(float y);

    float length();

    Vector2D operator+ (const Vector2D& v2) const
    {
        return Vector2D(x_ + v2.x_, y_ + v2.y_);
    }

    friend Vector2D& operator+=(Vector2D& v1, Vector2D& v2)
    {
        v1.x_ += v2.x_;
        v1.y_ += v2.y_;

        return v1;
    }

    Vector2D operator*(float scalar)
    {
        return Vector2D(x_ * scalar, y_ * scalar);
    }

    Vector2D& operator*=(float scalar)
    {
        x_ *= scalar;
        y_ *= scalar;
        return *this;
    }

    Vector2D operator-(const Vector2D& v2) const
    {
        return Vector2D(x_ - v2.x_, y_ - v2.y_);
    }

    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
    {
        v1.x_ -= v2.x_;
        v1.y_ -= v2.y_;
        return v1;
    }

    Vector2D operator/(float scalar)
    {
        return Vector2D(x_ / scalar, y_ / scalar);
    }

    Vector2D& operator/=(float scalar)
    {
        x_ /= scalar;
        y_ /= scalar;
        return *this;
    }

    void normalize()
    {
        float l = length();

        if (l > 0)
        {
            (*this) *= 1 / l;
        }
    }

private:
    float x_;
    float y_;
};

#endif // VECTOR2D_H
