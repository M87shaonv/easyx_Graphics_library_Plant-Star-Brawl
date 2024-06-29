#ifndef __PARTICLE_H__
#define __PARTICLE_H__
#include "Vector2.h"
#include "Atlas.h"
#include "util.h"
class Particle
{
public:
    Particle() = default;
    Particle(const Vector2& pos, Atlas* atlas, int life_span) :pos(pos), atlas(atlas), lifespan(life_span) {};

    ~Particle() = default;

    void set_atlas(Atlas* atlas)
    {
        this->atlas = atlas;
    }
    void set_pos(const Vector2& pos)
    {
        this->pos = pos;
    }
    void set_lifespan(int lifespan)
    {
        this->lifespan = lifespan;
    }
    bool check_valid() const
    {
        return valid;
    }
    void on_update(int dt)
    {
        timer += dt;
        if (timer >= lifespan)
        {
            timer = 0;
            ++idx_frame;
            if (idx_frame < atlas->size())
                return;//还没有播放完, 继续播放

            idx_frame = atlas->size() - 1;
            valid = false;
        }
    }
    void on_draw(const Camera& camera) const
    {
        putimage_alpha(camera, (int)pos.x, (int)pos.y, atlas->GetImage(idx_frame));
    }
private:
    int timer = 0;//计时器
    int lifespan = 0;//存活时间
    int idx_frame = 0;//当前帧索引
    Vector2 pos; //世界坐标位置
    bool valid = true;//是否有效
    Atlas* atlas = nullptr;//图集
};
#endif // __PARTICLE_H__