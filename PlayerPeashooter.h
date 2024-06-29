#ifndef _PLAYERPEASHOOTER_H_
#define _PLAYERPEASHOOTER_H_
#include "Player.h"
#include "PeaBullet.h"

extern Atlas atlas_peashooter_idle_left;//�㶹�����󶯻�ͼ��
extern Atlas atlas_peashooter_idle_right;//�㶹�����Ҷ���ͼ��
extern Atlas atlas_peashooter_run_left;//�㶹�������ܶ�����ͼ��
extern Atlas atlas_peashooter_run_right;//�㶹�������ܶ�����ͼ��
extern Atlas atlas_peashooter_attack_ex_left;//�㶹�����󹥻�����ͼ��
extern Atlas atlas_peashooter_attack_ex_right;//�㶹�����ҹ�������ͼ��
extern Atlas atlas_peashooter_die_left;//�㶹��������������ͼ��
extern Atlas atlas_peashooter_die_right;//�㶹��������������ͼ��

class PlayerPeashooter :public Player
{
public:
    PlayerPeashooter(bool facing_right = true) :Player(facing_right)
    {
        animation_idle_left.set_atlas(&atlas_peashooter_idle_left);
        animation_idle_right.set_atlas(&atlas_peashooter_idle_right);
        animation_run_left.set_atlas(&atlas_peashooter_run_left);
        animation_run_right.set_atlas(&atlas_peashooter_run_right);
        animation_attack_ex_left.set_atlas(&atlas_peashooter_attack_ex_left);
        animation_attack_ex_right.set_atlas(&atlas_peashooter_attack_ex_right);
        animation_die_left.set_atlas(&atlas_peashooter_die_left);
        animation_die_right.set_atlas(&atlas_peashooter_die_right);

        animation_idle_left.set_interval(75);
        animation_idle_right.set_interval(75);
        animation_run_left.set_interval(75);
        animation_run_right.set_interval(75);
        animation_attack_ex_left.set_interval(75);
        animation_attack_ex_right.set_interval(75);
        animation_die_left.set_interval(150);
        animation_die_right.set_interval(150);
        animation_die_left.set_loop(false);
        animation_die_right.set_loop(false);

        size.x = 80, size.y = 80;

        //��ʼ������״̬��ʱ��
        timer_attack_ex.setWaitTime(attack_ex_duration);
        timer_attack_ex.setOneTimeTrigger(true);
        timer_attack_ex.setCallback(
            [&]() {
                is_attacking_ex = false;//��������״̬�˳�
            }

        );
        //��ʼ������������ʱ��
        timer_spwan_pea_ex.setWaitTime(100);
        timer_spwan_pea_ex.setCallback(
            [&]() {
                spawn_pea_bullet(speed_pea_ex);
            }
        );

        attack_cd = 200;//������ȴʱ��
    }
    ~PlayerPeashooter() = default;

    void on_update(int dt) override
    {
        Player::on_update(dt);
        if (!is_attacking_ex) return;//����Ϊ��������״̬ʱ

        camera.jitter(2, 100);
        timer_attack_ex.Update(dt);
        timer_spwan_pea_ex.Update(dt);
    }
    void on_attack() override
    {
        spawn_pea_bullet(speed_pea);
        rand() % 2 == 0 ? mciSendString(_T("play pea_shoot_1 from 0"), NULL, 0, NULL)
            : mciSendString(_T("play pea_shoot_2 from 0"), NULL, 0, NULL);
    }
    void on_attack_ex() override
    {
        is_attacking_ex = true;
        timer_attack_ex.restart();

        facing_right ? animation_run_right.reset() : animation_run_left.reset();
        mciSendString(_T("play pea_shoot_ex from 0"), NULL, 0, NULL);
    }
private:
    void spawn_pea_bullet(float speed)
    {
        Bullet* bullet = new PeaBullet();
        Vector2 bullet_position, bullet_velocity;
        const Vector2& bullet_size = bullet->get_size();

        bullet_position.x = facing_right//���ݳ������ӵ�����λ��ʼ�ս�����ɫ�泯��Ե��
            ? position.x + size.x - bullet_size.x / 2 : position.x - bullet_size.x / 2;
        bullet_position.y = position.y;
        bullet_velocity.x = facing_right ? speed : -speed;
        bullet_velocity.y = 0;
        bullet->set_position(bullet_position.x, bullet_position.y);
        bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);
        bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);//�ӵ����ö���Ϊ����
        bullet->set_callback([&]() {mp += 25; });//�ӵ����е���ʱ���ӷ���
        bullets.push_back(bullet);
    }
private:
    const float speed_pea = 0.75f;
    const float speed_pea_ex = 1.5f;
    const int attack_ex_duration = 2000;//������������ʱ��

    Timer timer_attack_ex;//����������ʱ��,���Ƴ�������״̬���˳�
    Timer timer_spwan_pea_ex;//����������ʱ��,���Ƴ����㶹�ӵ�������
};
#endif