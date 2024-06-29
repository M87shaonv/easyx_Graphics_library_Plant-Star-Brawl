#ifndef _Animation_h_
#define _Animation_h_
#include "Atlas.h"
#include "Camera.h"
#include <functional>
#include "util.h"
class Animation
{
public:
    Animation() = default;
    ~Animation() = default;

    inline void on_draw(const Camera& camera, int x, int y) const
    {
        putimage_alpha(camera, x, y, atlas->GetImage(idx_frame));
    }
    void on_update(int delta)
    {
        timer += delta;
        if (timer < interval) return;

        timer = 0;
        ++idx_frame;
        if (idx_frame >= atlas->size())//�Ƿ�ѭ������,����������¿�ʼ����,����ֹͣ����
        {
            idx_frame = is_loop ? 0 : atlas->size() - 1;
            if (!is_loop && callback)
                callback();
        }
    }
    void set_callback(std::function<void()> callback)//���ö��������ص�,������ĺ������󱣴浽��Ա����callback��
    {
        this->callback = callback;
    }
    void reset()//���ö���
    {
        timer = 0;
        idx_frame = 0;
    }
    void set_atlas(Atlas* atlas)//���ö������õ�ͼ��
    {
        reset();
        this->atlas = atlas;
    }

    void set_interval(int interval)//����֡���
    {
        this->interval = interval;
    }
    void set_loop(bool loop)//�����Ƿ�ѭ������
    {
        this->is_loop = loop;
    }
    int get_idx_frame()//��ȡ��ǰ֡����
    {
        return idx_frame;
    }
    IMAGE* get_frame()//��ȡ��ǰ֡ͼƬ
    {
        return atlas->GetImage(idx_frame);
    }
    bool check_finished()//��鶯���Ƿ񲥷Ž���
    {
        if (is_loop) return false;
        return (idx_frame == atlas->size() - 1);
    }
private:
    int timer = 0;//��ʱ��
    int interval = 0;//֡���
    int idx_frame = 0;//��ǰ֡����
    bool is_loop = true;//�Ƿ�ѭ������
    Atlas* atlas = nullptr;
    std::function<void()> callback = nullptr;
};
#endif