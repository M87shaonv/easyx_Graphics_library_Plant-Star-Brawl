#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Camera.h"
#include "Animation.h"
#include "Platform.h"
#include "PlayerID.h"
#include "Bullet.h"
#include "Particle.h"
extern std::vector<Platform> platforms;
extern std::vector<Bullet*> bullets;//子弹集合
extern IMAGE img_1P_cursor;//1P光标图片
extern IMAGE img_2P_cursor;//2P光标图片
extern bool ISDEBUGING;
class Player
{
public:
    Player(bool facing_right = true) :facing_right(facing_right)
    {
        current_animation = facing_right ? &animation_idle_right : &animation_idle_left;

        attack_timer_cd.setWaitTime(attack_cd);
        attack_timer_cd.setOneTimeTrigger(true);
        attack_timer_cd.setCallback(
            [&]() {
                can_attack = true;
            }
        );

        timer_invulnerable.setWaitTime(500);//设置无敌时间
        timer_invulnerable.setOneTimeTrigger(true);
        timer_invulnerable.setCallback(
            [&]() {
                is_invulnerable = false;
            });
        timer_showing_sketch_frame.setWaitTime(75);//设置闪白显示时间
        timer_showing_sketch_frame.setCallback(
            [&]() {
                is_showing_sketch_frame = !is_showing_sketch_frame;
            }
        );

        timer_run_effect_generator.setWaitTime(75);//设置跑动特效生成器时间
        timer_run_effect_generator.setCallback(
            [&]() {
                Vector2 pos;
                IMAGE* frame = atlas_run_effect.GetImage(0);
                pos.x = position.x + (size.x - frame->getwidth()) / 2;
                pos.y = position.y + size.y - frame->getheight();
                particle_list.emplace_back(pos, &atlas_run_effect, 45);
            });

        timer_die_effect_generator.setWaitTime(35);//设置死亡特效生成器时间
        timer_die_effect_generator.setCallback(
            [&]() {
                Vector2 pos;
                IMAGE* frame = atlas_run_effect.GetImage(0);
                pos.x = position.x + (size.x - frame->getwidth()) / 2;
                pos.y = position.y + size.y - frame->getheight();
                particle_list.emplace_back(pos, &atlas_run_effect, 150);
            });

        animation_jump_effect.set_atlas(&atlas_jump_effect);//跳跃特效动画
        animation_jump_effect.set_interval(25);
        animation_jump_effect.set_loop(false);
        animation_jump_effect.set_callback(
            [&]() {
                is_jump_effect_visible = false;
            }
        );
        animation_land_effect.set_atlas(&atlas_land_effect);//着陆特效动画
        animation_land_effect.set_interval(50);
        animation_land_effect.set_loop(false);
        animation_land_effect.set_callback(
            [&]() {
                is_land_effect_visible = false;
            }
        );

        //timer_cursor_visible.setWaitTime(2500);//设置光标显示时间
        //timer_cursor_visible.setOneTimeTrigger(true);
        //timer_cursor_visible.setCallback(
        //    [&]() {
        //        is_cursor_visible = false;
        //    });
    }
    ~Player() = default;

    virtual void on_attack()
    {}
    virtual void on_attack_ex()
    {}
    virtual void Run(float distance)
    {
        //if (is_attacking_ex) return;

        position.x += distance;
        timer_run_effect_generator.resume();//恢复跑动特效生成器
    }
    virtual void Jump()
    {
        //if (velocity.y != 0 || is_attacking_ex) return;//玩家已经在跳跃时或正在超级攻击时,不需要再次跳跃
        if (velocity.y != 0) return;
        velocity.y += jump_velocity;
        is_jump_effect_visible = true;
        animation_jump_effect.reset();

        IMAGE* effect_frame = animation_jump_effect.get_frame();//获取跳跃特效帧
        pos_jump_effect.x = position.x + (size.x - effect_frame->getwidth()) / 2;
        pos_jump_effect.y = position.y + size.y - effect_frame->getheight();
    }
    virtual void Land()
    {
        is_land_effect_visible = true;
        animation_land_effect.reset();

        IMAGE* effect_frame = animation_land_effect.get_frame();
        pos_land_effect.x = position.x + (size.x - effect_frame->getwidth()) / 2;
        pos_land_effect.y = position.y + size.y - effect_frame->getheight();
    }
    virtual void on_update(int dt)
    {
        int direction = right_key_down - left_key_down;
        if (direction != 0)
        {
            if (!is_attacking_ex)//如果玩家正在超级攻击，则不能改变方向
                facing_right = direction > 0;//玩家朝向
            current_animation = facing_right ? &animation_run_right : &animation_run_left;
            Run((float)direction * run_velocity * dt);
        }
        else
        {
            current_animation = facing_right ? &animation_idle_right : &animation_idle_left;
            timer_run_effect_generator.pause();//暂停跑动特效生成器
        }

        if (is_attacking_ex)
            current_animation = facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;

        if (hp <= 0)
            current_animation = last_die_direction.x > 0 ? &animation_die_right : &animation_die_right;

        current_animation->on_update(dt);
        animation_jump_effect.on_update(dt);
        animation_land_effect.on_update(dt);

        attack_timer_cd.Update(dt);
        timer_invulnerable.Update(dt);
        timer_showing_sketch_frame.Update(dt);
        timer_run_effect_generator.Update(dt);
        timer_cursor_visible.Update(dt);

        //失败时的特效生成器
        if (hp <= 0)
            timer_die_effect_generator.Update(dt);

        particle_list.erase(//清除无效的粒子
            std::remove_if(
                particle_list.begin(),
                particle_list.end(),
                [](const Particle& p) {
                    return !p.check_valid();
                }
            ),
            particle_list.end()
        );

        for (Particle& p : particle_list)
            p.on_update(dt);

        if (is_showing_sketch_frame)
            sketch_image(current_animation->get_frame(), &img_sketch);

        move_and_collide(dt);
    }
    virtual void on_draw(const Camera& camera)
    {
        if (is_jump_effect_visible)
            animation_jump_effect.on_draw(camera, (int)pos_jump_effect.x, (int)pos_jump_effect.y);
        if (is_land_effect_visible)
            animation_land_effect.on_draw(camera, (int)pos_land_effect.x, (int)pos_land_effect.y);

        for (const Particle& p : particle_list)
            p.on_draw(camera);

        if (hp > 0 && is_invulnerable && is_showing_sketch_frame)
            putimage_alpha(camera, (int)position.x, (int)position.y, &img_sketch);
        else
            current_animation->on_draw(camera, (int)position.x, (int)position.y);

        if (is_cursor_visible)
        {
            switch (id)
            {
                case PlayerID::P1:
                    putimage_alpha(camera, (int)(position.x + (size.x - img_1P_cursor.getwidth()) / 2),
                        (int)(position.y - img_1P_cursor.getheight()), &img_1P_cursor);
                    break;
                case PlayerID::P2:
                    putimage_alpha(camera, (int)(position.x + (size.x - img_2P_cursor.getwidth()) / 2),
                        (int)(position.y - img_2P_cursor.getheight()), &img_2P_cursor);
                    break;
            }
        }
    }
    void make_invulnerable() //设置无敌
    {
        is_invulnerable = true;
        timer_invulnerable.restart();
    }
    void debug_draw(const Camera& camera) const
    {
           // 获取玩家的边界框的世界坐标
        int left = (int)position.x;
        int right = (int)(position.x + size.x);
        int top = (int)position.y;
        int bottom = (int)(position.y + size.y);

        // 设置线条颜色为蓝色
        setlinecolor(RGB(75, 148, 250));

        // 绘制矩形边界
        Line(camera, left, top, right, top); // 上边
        Line(camera, right, top, right, bottom); // 右边
        Line(camera, right, bottom, left, bottom); // 下边
        Line(camera, left, bottom, left, top); // 左边
    }
    virtual void Input(const ExMessage& msg)
    {
        switch (msg.message)
        {
            case WM_KEYDOWN:
                switch (id)
                {
                    case PlayerID::P1:
                        switch (msg.vkcode)
                        {
                            case 0x41://A
                                left_key_down = true;
                                break;
                            case 0x44://D
                                right_key_down = true;
                                break;
                            case 0x57://W
                                Jump();
                                break;
                            case 0x46://F

                                if (!can_attack)  break;//如果当前不能攻击，直接跳出

                                on_attack();
                                can_attack = false;
                                attack_timer_cd.restart();
                                break;
                            case 0x47://G
                                if (mp < 100) break;

                                on_attack_ex();
                                mp = 0;
                                break;
                        }
                        break;
                    case PlayerID::P2:
                        switch (msg.vkcode)
                        {
                            case VK_LEFT:
                                left_key_down = true;
                                break;
                            case VK_RIGHT:
                                right_key_down = true;
                                break;
                            case VK_UP:
                                Jump();
                                break;
                            case VK_OEM_PERIOD://.
                                if (!can_attack)  break;

                                on_attack();
                                can_attack = false;
                                attack_timer_cd.restart();
                                break;
                            case VK_OEM_2:// '/'
                                if (mp < 100) break;

                                on_attack_ex();
                                mp = 0;
                                break;
                        }
                        break;
                }
                break;
            case WM_KEYUP:
                switch (id)
                {
                    case PlayerID::P1:
                        switch (msg.vkcode)
                        {
                            case 0x41:
                                left_key_down = false;
                                break;
                            case 0x44:
                                right_key_down = false;
                                break;
                        }
                        break;
                    case PlayerID::P2:
                        switch (msg.vkcode)
                        {
                            case VK_LEFT:
                                left_key_down = false;
                                break;
                            case VK_RIGHT:
                                right_key_down = false;
                                break;
                        }
                        break;
                }
                break;
        }
    }
    void set_playerid(PlayerID id) { this->id = id; }
    void set_position(const Vector2& pos) { position = pos; }
    const Vector2& get_position() const { return this->position; }
    const Vector2& get_size() const { return this->size; }
    int get_hp() const { return this->hp; }
    int get_mp() const { return this->mp; }
    void set_hp(int hp) { this->hp = hp; }
    void set_mp(int mp) { this->mp = mp; }

protected:
    void move_and_collide(int dt)
    {
        float last_velocity_y = velocity.y;//记录上一帧的竖直速度

        velocity.y += gravity * dt;//重力加速度
        position += velocity * (float)dt;//移动

        if (hp <= 0) return;//玩家死亡时,不需要检测和平台的碰撞
        if (velocity.y <= 0) return;//玩家没有下降时,不需要检测和平台的碰撞

        for (Platform& platform : platforms)
        {
            const Platform::CollisionShape& shape = platform.collisionShape;//获取平台的碰撞形状
            //TODO 天才
            /*平台碰撞外形是一条线,玩家是矩形,判断是否在水平方向上发生重合,只需取二者最右边界的值
            和二者最左边界值进行作差,如果差值小于二者宽度之和,则证明两个图形在水平方向上发生重合*/
            bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left)
                <= size.x + (shape.right - shape.left));//检测是否碰撞,两者相减得到的是两个矩形在水平方向上的重叠长度

            bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);//检测是否碰撞,矩形的y坐标在玩家的y坐标范围内

            //if (is_collide_x && is_collide_y)
            //{
            //    float delta_pos_y = velocity.y * dt;//当都发生碰撞时,计算玩家在y轴移动的距离
            //    float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;//计算上一帧的位置
            //    if (last_tick_foot_pos_y <= shape.y)//如果上一帧的位置在平台的y坐标范围内,则证明玩家在平台上
            //    {
            //        position.y = shape.y - size.y;//将玩家的位置调整到平台的顶部
            //        velocity.y = 0;//将玩家的速度设置为0
            //        break;//退出循环,避免重复碰撞
            //    }
            //}
            if (!is_collide_x || !is_collide_y)
                continue;//如果不碰撞,则跳过
            float delta_pos_y = velocity.y * dt;//当都发生碰撞时,计算玩家在y轴移动的距离
            float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;//计算上一帧的位置

            if (last_tick_foot_pos_y > shape.y)
                continue;//如果上一帧的位置在平台的y坐标范围内,则证明玩家在平台上,跳过

            position.y = shape.y - size.y;//将玩家的位置调整到平台的顶部
            velocity.y = 0;//将玩家的速度设置为0
            //判断当前帧角色是否在当前帧落到平台上,角色前一帧的竖直速度不为0和当前帧的竖直速度为0,则证明角色在平台上
            if (last_velocity_y != 0)
                Land();

            break;//退出循环,避免重复碰撞
        }

        if (!is_invulnerable)
        {
            for (Bullet* bullet : bullets)
            {
                if (!bullet->get_valid() || bullet->get_collide_target() != id)
                    continue;//如果子弹无效或子弹的目标不是玩家,则跳过

                if (!bullet->check_collision(position, size))
                    continue;//如果子弹没有碰撞到玩家,则跳过

                make_invulnerable();//设置无敌
                bullet->on_collide();
                bullet->set_valid(false);//设置子弹无效
                hp -= bullet->get_damage();//玩家受到子弹伤害
                last_die_direction = bullet->get_position() - position;//记录最后一次受伤方向
                if (hp <= 0)
                {
                    velocity.x = last_die_direction.x < 0 ? 0.35f : -0.35f;
                    velocity.y = -1.0f;
                }
            }
        }
    }

protected:
    const float jump_velocity = -0.85f;//跳跃速度
    const float gravity = 1.6e-3f;//重力
    const float run_velocity = 0.55f;//玩家奔跑速度
    int mp = 0;//角色能量
    int hp = 100;//角色血量

    Vector2 size;//角色尺寸
    Vector2 velocity;//玩家速度
    Vector2 position;//玩家位置

    Animation animation_idle_left;
    Animation animation_idle_right;
    Animation animation_run_left;
    Animation animation_run_right;
    Animation animation_attack_ex_left;
    Animation animation_attack_ex_right;
    Animation animation_die_left;
    Animation animation_die_right;
    Animation* current_animation = nullptr;//当前动画
    PlayerID id = PlayerID::P1;

    Animation  animation_jump_effect;
    Animation  animation_land_effect;
    bool is_jump_effect_visible = false;//是否显示跳跃动画
    bool is_land_effect_visible = false;//是否显示着陆动画
    Vector2 pos_jump_effect;//跳跃动画位置
    Vector2 pos_land_effect;//着陆动画位置
    bool left_key_down = false;
    bool right_key_down = false;
    bool facing_right = true;//玩家朝向

    IMAGE img_sketch;//剪影图片
    bool is_showing_sketch_frame = false;//当前帧是否显示剪影
    Timer timer_invulnerable;//无敌计时器
    Timer timer_showing_sketch_frame;//显示剪影计时器,即无敌状态闪烁定时器

    bool can_attack = true;//玩家是否可以普通攻击
    bool is_attacking_ex = false;//玩家是否正在超级攻击
    bool is_invulnerable = false;//玩家是否无敌
    int attack_cd = 300;//普通攻击冷却时间
    Timer attack_timer_cd;//普通攻击计时器

    Timer timer_run_effect_generator;//跑动特效粒子发射定时器
    Timer timer_die_effect_generator;//死亡特效粒子发射定时器
    std::vector<Particle> particle_list;//粒子集合

    bool is_cursor_visible = true;//是否显示光标
    Timer timer_cursor_visible;//光标显示计时器

    Vector2 last_die_direction;//最后一次受伤方向
};
#endif