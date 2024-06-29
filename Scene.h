#ifndef _SCENE_H_
#define _SCENE_H_
#include <graphics.h>
#include "Camera.h"
//��������=��������-���������
class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    virtual void on_enter()//���볡����ʼ��
    {}

    virtual void on_exit()//�˳�����ʱж���߼�
    {}

    virtual void on_update(int dt)//��������ʱ����,dt��delta,��ʾʵ�ʹ�ȥʱ��
    {}
    virtual void on_draw(const Camera& camera)//��Ⱦ��ͼʱ����
    {}
    virtual void on_input(const ExMessage& msg)//���������������ʱ����
    {}
private:
};
#endif