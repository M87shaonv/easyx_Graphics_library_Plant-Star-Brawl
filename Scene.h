#ifndef _SCENE_H_
#define _SCENE_H_
#include <graphics.h>

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    virtual void on_enter()//进入场景初始化
    {}

    virtual void on_exit()//退出场景时卸载逻辑
    {}

    virtual void on_update()//处理数据时调用
    {}
    virtual void on_draw()//渲染视图时调用
    {}
    virtual void on_input(const ExMessage& msg)//场景处理玩家输入时调用
    {}
private:
};
#endif