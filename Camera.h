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

    const Vector2& GetPosition() const { return position; } //��ȡ�����λ��

    void ResetPosition()//���������λ��
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
    Vector2 position;//�����λ��
    Timer jitterTimer;//������ʱ��
    bool jittering = false;//�Ƿ����ڶ���
    float jitterStrength = 0;//����ǿ��
};
#endif