#ifndef _TIMER_H_
#define _TIMER_H_
#include <functional>
class Timer
{
private:
    int passTime = 0;//�Ѿ���ȥ��ʱ��
    int waitTime = 0;//�ȴ�ʱ��
    bool paused = false;//�Ƿ���ͣ
    bool tiggered = false;//�Ƿ񴥷�
    bool oneTimeTrigger = false;//�Ƿ񵥴δ���
    std::function<void()> callback = nullptr;//�ص�����
public:
    Timer() = default;
    ~Timer() = default;

    void restart()//���ö�ʱ��
    {
        passTime = 0;
        tiggered = false;
    }
    void setWaitTime(int waitTime)//���õȴ�ʱ��
    {
        this->waitTime = waitTime;
    }
    void setOneTimeTrigger(bool oneTimeTrigger)//���õ��δ���
    {
        this->oneTimeTrigger = oneTimeTrigger;
    }
    void setCallback(std::function<void()> callback)
    {
        this->callback = callback;
    }
    void pause()//��ͣ��ʱ��
    {
        paused = true;
    }
    void resume()//�ָ���ʱ��
    {
        paused = false;
    }
    void Update(int dt)
    {
        if (paused) return;

        passTime += dt;
        if (passTime < waitTime) return; //��û��ʱ��
         //�����ʱ�����ǵ��δ���,�򵥴δ�����û�д�����,�����лص�����,�򴥷��ص�����
        if ((!oneTimeTrigger || (oneTimeTrigger && !tiggered)) && callback)
            callback();
        tiggered = true;
        passTime = 0;
    }
};
#endif