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
        if (idx_frame >= atlas->size())//是否循环播放,如果是则重新开始播放,否则停止播放
        {
            idx_frame = is_loop ? 0 : atlas->size() - 1;
            if (!is_loop && callback)
                callback();
        }
    }
    void set_callback(std::function<void()> callback)//设置动画结束回调,将传入的函数对象保存到成员变量callback中
    {
        this->callback = callback;
    }
    void reset()//重置动画
    {
        timer = 0;
        idx_frame = 0;
    }
    void set_atlas(Atlas* atlas)//设置动画所用的图集
    {
        reset();
        this->atlas = atlas;
    }

    void set_interval(int interval)//设置帧间隔
    {
        this->interval = interval;
    }
    void set_loop(bool loop)//设置是否循环播放
    {
        this->is_loop = loop;
    }
    int get_idx_frame()//获取当前帧索引
    {
        return idx_frame;
    }
    IMAGE* get_frame()//获取当前帧图片
    {
        return atlas->GetImage(idx_frame);
    }
    bool check_finished()//检查动画是否播放结束
    {
        if (is_loop) return false;
        return (idx_frame == atlas->size() - 1);
    }
private:
    int timer = 0;//计时器
    int interval = 0;//帧间隔
    int idx_frame = 0;//当前帧索引
    bool is_loop = true;//是否循环播放
    Atlas* atlas = nullptr;
    std::function<void()> callback = nullptr;
};
#endif