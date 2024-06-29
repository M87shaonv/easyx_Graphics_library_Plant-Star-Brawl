#ifndef __BULLET_H__
#define __BULLET_H__
#include "Vector2.h"
#include <functional>
#include "Camera.h"
#include "Timer.h"
#include "Animation.h"
#include "PlayerID.h"

class Bullet
{
public:
    Bullet()
    {
        timer.setOneTimeTrigger(true);
        timer.setWaitTime(6000);//n秒后销毁
        timer.setCallback(
            [&]() {
                can_remove = true;
            }
        );
    }
    ~Bullet() = default;
    void set_damage(int damage) { this->damage = damage; }
    int get_damage() const { return damage; }
    void set_position(float x, float y) { position.x = x; position.y = y; }
    const Vector2& get_position() const { return position; }
    const Vector2& get_size() const { return size; }
    void set_velocity(float x, float y) { velocity.x = x; velocity.y = y; }
    void set_collide_target(PlayerID target) { target_id = target; }
    PlayerID get_collide_target() const { return target_id; }
    void set_callback(std::function<void()> func) { callback = func; }
    void set_valid(bool valid) { this->valid = valid; }
    bool get_valid() const { return valid; }
    bool check_can_remove() const { return can_remove; }

    virtual void on_collide() ///碰撞时调用该函数
    {
        if (callback) callback();
    }
    virtual bool check_collision(const Vector2& pos, const Vector2& size)//子弹中心是否和指定玩家位置和尺寸的目标发生碰撞
    {
        return this->position.x + this->size.x / 2 >= pos.x
            && this->position.x + this->size.x / 2 <= pos.x + size.x
            && this->position.y + this->size.y / 2 >= pos.y
            && this->position.y + this->size.y / 2 <= pos.y + size.y;
    }
    virtual void on_update(int dt)
    {}
    virtual void on_draw(const Camera& camera) const
    {}
    virtual void debug_draw(const Camera& camera) const
    {
  // 获取子弹的边界框的世界坐标
        int left = (int)(position.x);
        int right = (int)(position.x + size.x);
        int top = (int)(position.y);
        int bottom = (int)(position.y + size.y);
        setlinecolor(RGB(94, 250, 141));
        // 绘制矩形边界
        Line(camera, left, top, right, top); // 上边
        Line(camera, right, top, right, bottom); // 右边
        Line(camera, right, bottom, left, bottom); // 下边
        Line(camera, left, bottom, left, top); // 左边
    }

protected:
    Timer timer;//销毁计时器
    Vector2 size;
    Vector2 position;
    Vector2 velocity;
    int damage = 10;//伤害值
    bool valid = true;//是否有效
    bool can_remove = false;//是否可以移除
    std::function<void()> callback = nullptr;//回调函数
    PlayerID target_id = PlayerID::P1;//目标玩家id
};
#endif