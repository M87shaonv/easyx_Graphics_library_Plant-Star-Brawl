#ifndef _PLAYER_SUNFLOWER_H_
#define _PLAYER_SUNFLOWER_H_
#include "Player.h"
#include "SunBullet.h"
#include "SunBulletEX.h"
extern Atlas atlas_sunflower_idle_left;//向日葵左动画图集
extern Atlas atlas_sunflower_idle_right;//向日葵右动画图集
extern Atlas atlas_sunflower_run_left;//向日葵左跑动动画图集
extern Atlas atlas_sunflower_run_right;//向日葵右跑动动画图集
extern Atlas atlas_sunflower_attack_ex_left;//向日葵左攻击动画图集
extern Atlas atlas_sunflower_attack_ex_right;//向日葵右攻击动画图集
extern Atlas atlas_sun_text;//日文本动画图集
extern Atlas atlas_sunflower_die_left;//向日葵左死亡动画图集
extern Atlas atlas_sunflower_die_right;//向日葵右死亡动画图集

extern Player* player1;
extern Player* player2;
class PlayerSunflower :public Player
{
public:
    PlayerSunflower(bool facing_right = true) :Player(facing_right)
    {
        animation_idle_left.set_atlas(&atlas_sunflower_idle_left);
        animation_idle_right.set_atlas(&atlas_sunflower_idle_right);
        animation_run_left.set_atlas(&atlas_sunflower_run_left);
        animation_run_right.set_atlas(&atlas_sunflower_run_right);
        animation_attack_ex_left.set_atlas(&atlas_sunflower_attack_ex_left);
        animation_attack_ex_right.set_atlas(&atlas_sunflower_attack_ex_right);
        animation_sun_text.set_atlas(&atlas_sun_text);
        animation_die_left.set_atlas(&atlas_sunflower_die_left);
        animation_die_right.set_atlas(&atlas_sunflower_die_right);

        animation_idle_left.set_interval(75);
        animation_idle_right.set_interval(75);
        animation_run_left.set_interval(75);
        animation_run_right.set_interval(75);
        animation_attack_ex_left.set_interval(100);
        animation_attack_ex_right.set_interval(100);
        animation_sun_text.set_interval(100);
        animation_die_left.set_interval(150);
        animation_die_right.set_interval(150);

        animation_attack_ex_left.set_loop(false);
        animation_attack_ex_right.set_loop(false);
        animation_sun_text.set_loop(false);
        animation_die_left.set_loop(false);
        animation_die_right.set_loop(false);

        size.x = 80, size.y = 80;

        animation_attack_ex_left.set_callback([&]()
            {
                is_attacking_ex = false;
                can_sun_text_visible = false;
            });
        animation_attack_ex_right.set_callback([&]()
            {
                is_attacking_ex = false;
                can_sun_text_visible = false;
            });

        attack_cd = 300;
    }
    ~PlayerSunflower() = default;

    void on_update(int dt) override
    {
        Player::on_update(dt);
        if (can_sun_text_visible) animation_sun_text.on_update(dt);
    }
    void on_draw(const Camera& camera) override
    {
        Player::on_draw(camera);

        if (!can_sun_text_visible) return;//如果不能显示日文本，则直接返回

        Vector2 text_pos;
        IMAGE* frame = animation_sun_text.get_frame();
        text_pos.x = position.x - (size.x - frame->getwidth()) / 2;
        text_pos.y = position.y - frame->getheight();
        animation_sun_text.on_draw(camera, (int)text_pos.x, (int)text_pos.y);
    }
    void on_attack() override
    {
        Bullet* bullet = new SunBullet();

        Vector2 bullet_pos;
        const Vector2& bullet_size = bullet->get_size();
        bullet_pos.x = position.x + (size.x - bullet_size.x) / 2;
        bullet_pos.y = position.y;

        bullet->set_position(bullet_pos.x, bullet_pos.y);
        bullet->set_velocity(facing_right ? veloctity_sun.x : -veloctity_sun.x, veloctity_sun.y);
        bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);
        bullet->set_callback([&]() {mp += 35; });
        bullets.push_back(bullet);
    }
    void on_attack_ex() override
    {
        is_attacking_ex = true;
        can_sun_text_visible = true;
        animation_sun_text.reset();
        facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();

        Bullet* bullet = new SunBulletEX();
        Player* target_player = (id == PlayerID::P1 ? player2 : player1);

        Vector2 bullet_pos, bullet_vel;//子弹位置和速度来存储计算过程的中间值
        const Vector2& bullet_size = bullet->get_size();
        const Vector2& target_size = target_player->get_size();
        const Vector2& target_pos = target_player->get_position();
        bullet_pos.x = target_pos.x + (target_size.x - bullet_size.x) / 2;
        bullet_pos.y = -size.y;
        bullet_vel.x = 0;
        bullet_vel.y = speed_sun_ex;

        bullet->set_position(bullet_pos.x, bullet_pos.y);
        bullet->set_velocity(bullet_vel.x, bullet_vel.y);
        bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);
        bullet->set_callback([&]() {mp += 50; });
        bullets.push_back(bullet);
        mciSendStringA("play sun_text from 0", NULL, 0, NULL);
    }

private:
    const float speed_sun_ex = 0.15f;
    const Vector2 veloctity_sun = { 0.25f,-0.5f };
    Animation animation_sun_text;//日文本动画
    bool can_sun_text_visible = false;//是否可以显示日文本
};
#endif