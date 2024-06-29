#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Timer.h"
#include "Vector2.h"

class Camera
{
public:
    Camera()
    {
        jitterTimer.setOneTimeTrigger(true);
        jitterTimer.setCallback(
            [&]() {
                jittering = false;
                ResetPosition();
            }
        );
    }
    ~Camera() = default;

    const Vector2& GetPosition() const { return position; } //获取摄像机位置

    void ResetPosition()//重置摄像机位置
    {
        position.x = 0;
        position.y = 0;
    }
    void Update(int dt)
    {
        jitterTimer.Update(dt);
        if (jittering)
        {
            position.x += (-50 + rand() % 100) / 50.0f * jitterStrength;
            position.y += (-50 + rand() % 100) / 50.0f * jitterStrength;
        }
    }
    void jitter(float strength, float duration)
    {
        jittering = true;
        jitterStrength = strength;
        jitterTimer.setWaitTime(duration);
        jitterTimer.restart();
    }
private:
    Vector2 position;//摄像机位置
    Timer jitterTimer;//抖动定时器
    bool jittering = false;//是否正在抖动
    float jitterStrength = 0;//抖动强度
};
#endif