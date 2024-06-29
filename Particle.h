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
                return;//��û�в�����, ��������

            idx_frame = atlas->size() - 1;
            valid = false;
        }
    }
    void on_draw(const Camera& camera) const
    {
        putimage_alpha(camera, (int)pos.x, (int)pos.y, atlas->GetImage(idx_frame));
    }
private:
    int timer = 0;//��ʱ��
    int lifespan = 0;//���ʱ��
    int idx_frame = 0;//��ǰ֡����
    Vector2 pos; //��������λ��
    bool valid = true;//�Ƿ���Ч
    Atlas* atlas = nullptr;//ͼ��
};
#endif // __PARTICLE_H__