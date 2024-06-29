#ifndef _SUNBULLETEXT_H_
#define _SUNBULLETEXT_H_
#include "Bullet.h"
extern Camera camera;
extern Atlas atlas_sun_ex;//特殊太阳动画图集
extern Atlas atlas_sun_ex_explode;//特殊太阳爆炸动画图集
class SunBulletEX : public Bullet
{
public:
    SunBulletEX()
    {
        Bullet::Bullet();
        size.x = 288, size.y = 288;
        damage = 20;
        animation_idle.set_atlas(&atlas_sun_ex);
        animation_idle.set_interval(50);

        animation_explode.set_atlas(&atlas_sun_ex_explode);
        animation_explode.set_interval(50);
        animation_explode.set_loop(false);
        animation_explode.set_callback(
            [&]() { can_remove = true; }
        );
        IMAGE* frame_idle = animation_idle.get_frame(); //获取动画第一帧
        IMAGE* frame_explode = animation_explode.get_frame();//获取爆炸动画第一帧
        explode_draw_offset.x = (frame_idle->getwidth() / 2 - frame_explode->getwidth()) / 2.0f;//计算爆炸动画绘制偏移量
        explode_draw_offset.y = (frame_idle->getheight() / 2 - frame_explode->getheight()) / 2.0f;
    }
    ~SunBulletEX() = default;
    void on_collide() override
    {
        Bullet::on_collide();
        camera.jitter(20, 300);
        mciSendString(_T("play sun_explode_ex from 0"), NULL, 0, NULL);
    }
    bool check_collision(const Vector2& pos, const Vector2& size) override //使用矩形碰撞检测
    {
        bool is_collide_x = (max(this->position.x + this->size.x, pos.x + size.x)
            - min(this->position.x, pos.x) <= this->size.x + size.x);
        bool is_collide_y = (max(this->position.y + this->size.y, pos.y + size.y)
            - min(this->position.y, pos.y) <= this->size.y + size.y);
        return is_collide_x && is_collide_y;
    }
    void on_update(int dt) override
    {
        timer.Update(dt);
        if (!valid)
            animation_explode.on_update(dt);
        else
        {
            position += velocity * (float)dt;
            animation_idle.on_update(dt);
        }
    }
    void on_draw(const Camera& camera) const
    {
        if (valid)
            animation_idle.on_draw(camera, (int)position.x, (int)position.y);
        else
            animation_explode.on_draw(camera,
                (int)(position.x + explode_draw_offset.x),
                (int)(position.y + explode_draw_offset.y));
    }
private:
    Animation animation_idle;
    Animation animation_explode;
    Vector2 explode_draw_offset;
};
#endif