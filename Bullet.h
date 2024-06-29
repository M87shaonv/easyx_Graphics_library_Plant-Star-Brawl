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
        timer.setWaitTime(6000);//n�������
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

    virtual void on_collide() ///��ײʱ���øú���
    {
        if (callback) callback();
    }
    virtual bool check_collision(const Vector2& pos, const Vector2& size)//�ӵ������Ƿ��ָ�����λ�úͳߴ��Ŀ�귢����ײ
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
  // ��ȡ�ӵ��ı߽�����������
        int left = (int)(position.x);
        int right = (int)(position.x + size.x);
        int top = (int)(position.y);
        int bottom = (int)(position.y + size.y);
        setlinecolor(RGB(94, 250, 141));
        // ���ƾ��α߽�
        Line(camera, left, top, right, top); // �ϱ�
        Line(camera, right, top, right, bottom); // �ұ�
        Line(camera, right, bottom, left, bottom); // �±�
        Line(camera, left, bottom, left, top); // ���
    }

protected:
    Timer timer;//���ټ�ʱ��
    Vector2 size;
    Vector2 position;
    Vector2 velocity;
    int damage = 10;//�˺�ֵ
    bool valid = true;//�Ƿ���Ч
    bool can_remove = false;//�Ƿ�����Ƴ�
    std::function<void()> callback = nullptr;//�ص�����
    PlayerID target_id = PlayerID::P1;//Ŀ�����id
};
#endif