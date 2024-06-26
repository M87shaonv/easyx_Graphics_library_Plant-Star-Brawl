#ifndef _SCENE_H_
#define _SCENE_H_
#include <graphics.h>

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    virtual void on_enter()//���볡����ʼ��
    {}

    virtual void on_exit()//�˳�����ʱж���߼�
    {}

    virtual void on_update()//��������ʱ����
    {}
    virtual void on_draw()//��Ⱦ��ͼʱ����
    {}
    virtual void on_input(const ExMessage& msg)//���������������ʱ����
    {}
private:
};
#endif