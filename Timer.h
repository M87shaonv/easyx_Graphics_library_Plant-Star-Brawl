#ifndef _TIMER_H_
#define _TIMER_H_
#include <functional>
class Timer
{
private:
    int passTime = 0;//已经过去的时间
    int waitTime = 0;//等待时间
    bool paused = false;//是否暂停
    bool tiggered = false;//是否触发
    bool oneTimeTrigger = false;//是否单次触发
    std::function<void()> callback = nullptr;//回调函数
public:
    Timer() = default;
    ~Timer() = default;

    void restart()//重置定时器
    {
        passTime = 0;
        tiggered = false;
    }
    void setWaitTime(int waitTime)//设置等待时间
    {
        this->waitTime = waitTime;
    }
    void setOneTimeTrigger(bool oneTimeTrigger)//设置单次触发
    {
        this->oneTimeTrigger = oneTimeTrigger;
    }
    void setCallback(std::function<void()> callback)
    {
        this->callback = callback;
    }
    void pause()//暂停定时器
    {
        paused = true;
    }
    void resume()//恢复定时器
    {
        paused = false;
    }
    void Update(int dt)
    {
        if (paused) return;

        passTime += dt;
        if (passTime < waitTime) return; //还没到时间
         //如果定时器不是单次触发,或单次触发且没有触发过,并且有回调函数,则触发回调函数
        if ((!oneTimeTrigger || (oneTimeTrigger && !tiggered)) && callback)
            callback();
        tiggered = true;
        passTime = 0;
    }
};
#endif