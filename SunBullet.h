#ifndef _SUNBULLET_H_
#define _SUNBULLET_H_
#include "Bullet.h"
extern Camera camera;
extern Atlas atlas_sun;//̫������ͼ��
extern Atlas atlas_sun_explode;//̫����ը����ͼ��
class SunBullet : public Bullet
{
public:
    SunBullet()
    {
        Bullet::Bullet();

        size.x = 96, size.y = 96;
        damage = 20;

        animation_idle.set_atlas(&atlas_sun);
        animation_idle.set_interval(50);
        animation_explode.set_atlas(&atlas_sun_explode);
        animation_explode.set_interval(50);
        animation_explode.set_loop(false);
        animation_explode.set_callback(
            [&]() {can_remove = true; }
        );
        IMAGE* frame_idle = animation_idle.get_frame(); //��ȡ������һ֡
        IMAGE* frame_explode = animation_explode.get_frame();//��ȡ��ը������һ֡
        explode_draw_offset.x = (frame_idle->getwidth() - frame_explode->getwidth()) / 2.0f;//���㱬ը��������ƫ����
        explode_draw_offset.y = (frame_idle->getheight() - frame_explode->getheight()) / 2.0f;
    }
    ~SunBullet() = default;
    void on_collide() override
    {
        Bullet::on_collide();
        camera.jitter(5, 240);
        mciSendString(_T("play sun_explode from 0"), NULL, 0, NULL);
    }
    void on_update(int dt) override
    {
        timer.Update(dt);
        //if (valid)
        //{
        //    velocity.y += gravity * dt;
        //    position += velocity * (float)dt;
        //}
        //if (!valid)
        //    animation_explode.on_update(dt);
        //else
        //    animation_idle.on_update(dt);
        if (!valid)
            animation_explode.on_update(dt);
        else
        {
            animation_idle.on_update(dt);
            velocity.y += gravity * dt;
            position += velocity * (float)dt;
        }
    }
    void on_draw(const Camera& camera) const override
    {
        if (valid)
            animation_idle.on_draw(camera, (int)position.x, (int)position.y);
        else
            animation_explode.on_draw(camera,
                (int)(position.x + explode_draw_offset.x),
                (int)(position.y + explode_draw_offset.y));
    }
private:
    const float gravity = 1e-3f;//ը������
    Animation animation_idle;
    Animation animation_explode;
    Vector2 explode_draw_offset;//��ը��������ƫ����
};
#endif