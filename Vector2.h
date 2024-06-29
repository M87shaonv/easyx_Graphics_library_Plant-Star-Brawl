#ifndef _VECTOR2_H_
#define _VECTOR2_H_
#include <cmath>

class Vector2
{
public:
    float x = 0;
    float y = 0;
public:
    Vector2() = default;
    ~Vector2() = default;
    Vector2(float x, float y) : x(x), y(y) {}
public:
    const float Length() const// ������������
    {
        return sqrt(x * x + y * y);
    }
    const Vector2 normalized() const//��������׼��
    {
        float len = Length();
        if (len == 0)
            return Vector2(0, 0);

        return Vector2(x / len, y / len);
    }
public:// ���������
    Vector2 operator+(const Vector2& vec) const
    {
        return Vector2(x + vec.x, y + vec.y);
    }

    Vector2 operator-(const Vector2& vec) const
    {
        return Vector2(x - vec.x, y - vec.y);
    }

    float operator*(const Vector2& vec) const
    {
        return x * vec.x + y * vec.y;
    }

    Vector2 operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }

    Vector2& operator+=(const Vector2& vec)
    {
        x += vec.x;
        y += vec.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& vec)
    {
        x -= vec.x;
        y -= vec.y;
        return *this;
    }
     //���Ӧ�÷�������������Ӧ�����˻�֮����Ϊ�������
    Vector2& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }
};
#endif