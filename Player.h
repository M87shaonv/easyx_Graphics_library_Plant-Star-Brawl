#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Camera.h"
#include "Animation.h"
#include "Platform.h"
#include "PlayerID.h"
#include "Bullet.h"
#include "Particle.h"
extern std::vector<Platform> platforms;
extern std::vector<Bullet*> bullets;//�ӵ�����
extern IMAGE img_1P_cursor;//1P���ͼƬ
extern IMAGE img_2P_cursor;//2P���ͼƬ
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

        timer_invulnerable.setWaitTime(500);//�����޵�ʱ��
        timer_invulnerable.setOneTimeTrigger(true);
        timer_invulnerable.setCallback(
            [&]() {
                is_invulnerable = false;
            });
        timer_showing_sketch_frame.setWaitTime(75);//����������ʾʱ��
        timer_showing_sketch_frame.setCallback(
            [&]() {
                is_showing_sketch_frame = !is_showing_sketch_frame;
            }
        );

        timer_run_effect_generator.setWaitTime(75);//�����ܶ���Ч������ʱ��
        timer_run_effect_generator.setCallback(
            [&]() {
                Vector2 pos;
                IMAGE* frame = atlas_run_effect.GetImage(0);
                pos.x = position.x + (size.x - frame->getwidth()) / 2;
                pos.y = position.y + size.y - frame->getheight();
                particle_list.emplace_back(pos, &atlas_run_effect, 45);
            });

        timer_die_effect_generator.setWaitTime(35);//����������Ч������ʱ��
        timer_die_effect_generator.setCallback(
            [&]() {
                Vector2 pos;
                IMAGE* frame = atlas_run_effect.GetImage(0);
                pos.x = position.x + (size.x - frame->getwidth()) / 2;
                pos.y = position.y + size.y - frame->getheight();
                particle_list.emplace_back(pos, &atlas_run_effect, 150);
            });

        animation_jump_effect.set_atlas(&atlas_jump_effect);//��Ծ��Ч����
        animation_jump_effect.set_interval(25);
        animation_jump_effect.set_loop(false);
        animation_jump_effect.set_callback(
            [&]() {
                is_jump_effect_visible = false;
            }
        );
        animation_land_effect.set_atlas(&atlas_land_effect);//��½��Ч����
        animation_land_effect.set_interval(50);
        animation_land_effect.set_loop(false);
        animation_land_effect.set_callback(
            [&]() {
                is_land_effect_visible = false;
            }
        );

        //timer_cursor_visible.setWaitTime(2500);//���ù����ʾʱ��
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
        timer_run_effect_generator.resume();//�ָ��ܶ���Ч������
    }
    virtual void Jump()
    {
        //if (velocity.y != 0 || is_attacking_ex) return;//����Ѿ�����Ծʱ�����ڳ�������ʱ,����Ҫ�ٴ���Ծ
        if (velocity.y != 0) return;
        velocity.y += jump_velocity;
        is_jump_effect_visible = true;
        animation_jump_effect.reset();

        IMAGE* effect_frame = animation_jump_effect.get_frame();//��ȡ��Ծ��Ч֡
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
            if (!is_attacking_ex)//���������ڳ������������ܸı䷽��
                facing_right = direction > 0;//��ҳ���
            current_animation = facing_right ? &animation_run_right : &animation_run_left;
            Run((float)direction * run_velocity * dt);
        }
        else
        {
            current_animation = facing_right ? &animation_idle_right : &animation_idle_left;
            timer_run_effect_generator.pause();//��ͣ�ܶ���Ч������
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

        //ʧ��ʱ����Ч������
        if (hp <= 0)
            timer_die_effect_generator.Update(dt);

        particle_list.erase(//�����Ч������
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
    void make_invulnerable() //�����޵�
    {
        is_invulnerable = true;
        timer_invulnerable.restart();
    }
    void debug_draw(const Camera& camera) const
    {
           // ��ȡ��ҵı߽�����������
        int left = (int)position.x;
        int right = (int)(position.x + size.x);
        int top = (int)position.y;
        int bottom = (int)(position.y + size.y);

        // ����������ɫΪ��ɫ
        setlinecolor(RGB(75, 148, 250));

        // ���ƾ��α߽�
        Line(camera, left, top, right, top); // �ϱ�
        Line(camera, right, top, right, bottom); // �ұ�
        Line(camera, right, bottom, left, bottom); // �±�
        Line(camera, left, bottom, left, top); // ���
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

                                if (!can_attack)  break;//�����ǰ���ܹ�����ֱ������

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
        float last_velocity_y = velocity.y;//��¼��һ֡����ֱ�ٶ�

        velocity.y += gravity * dt;//�������ٶ�
        position += velocity * (float)dt;//�ƶ�

        if (hp <= 0) return;//�������ʱ,����Ҫ����ƽ̨����ײ
        if (velocity.y <= 0) return;//���û���½�ʱ,����Ҫ����ƽ̨����ײ

        for (Platform& platform : platforms)
        {
            const Platform::CollisionShape& shape = platform.collisionShape;//��ȡƽ̨����ײ��״
            //TODO ���
            /*ƽ̨��ײ������һ����,����Ǿ���,�ж��Ƿ���ˮƽ�����Ϸ����غ�,ֻ��ȡ�������ұ߽��ֵ
            �Ͷ�������߽�ֵ��������,�����ֵС�ڶ��߿��֮��,��֤������ͼ����ˮƽ�����Ϸ����غ�*/
            bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left)
                <= size.x + (shape.right - shape.left));//����Ƿ���ײ,��������õ���������������ˮƽ�����ϵ��ص�����

            bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);//����Ƿ���ײ,���ε�y��������ҵ�y���귶Χ��

            //if (is_collide_x && is_collide_y)
            //{
            //    float delta_pos_y = velocity.y * dt;//����������ײʱ,���������y���ƶ��ľ���
            //    float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;//������һ֡��λ��
            //    if (last_tick_foot_pos_y <= shape.y)//�����һ֡��λ����ƽ̨��y���귶Χ��,��֤�������ƽ̨��
            //    {
            //        position.y = shape.y - size.y;//����ҵ�λ�õ�����ƽ̨�Ķ���
            //        velocity.y = 0;//����ҵ��ٶ�����Ϊ0
            //        break;//�˳�ѭ��,�����ظ���ײ
            //    }
            //}
            if (!is_collide_x || !is_collide_y)
                continue;//�������ײ,������
            float delta_pos_y = velocity.y * dt;//����������ײʱ,���������y���ƶ��ľ���
            float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;//������һ֡��λ��

            if (last_tick_foot_pos_y > shape.y)
                continue;//�����һ֡��λ����ƽ̨��y���귶Χ��,��֤�������ƽ̨��,����

            position.y = shape.y - size.y;//����ҵ�λ�õ�����ƽ̨�Ķ���
            velocity.y = 0;//����ҵ��ٶ�����Ϊ0
            //�жϵ�ǰ֡��ɫ�Ƿ��ڵ�ǰ֡�䵽ƽ̨��,��ɫǰһ֡����ֱ�ٶȲ�Ϊ0�͵�ǰ֡����ֱ�ٶ�Ϊ0,��֤����ɫ��ƽ̨��
            if (last_velocity_y != 0)
                Land();

            break;//�˳�ѭ��,�����ظ���ײ
        }

        if (!is_invulnerable)
        {
            for (Bullet* bullet : bullets)
            {
                if (!bullet->get_valid() || bullet->get_collide_target() != id)
                    continue;//����ӵ���Ч���ӵ���Ŀ�겻�����,������

                if (!bullet->check_collision(position, size))
                    continue;//����ӵ�û����ײ�����,������

                make_invulnerable();//�����޵�
                bullet->on_collide();
                bullet->set_valid(false);//�����ӵ���Ч
                hp -= bullet->get_damage();//����ܵ��ӵ��˺�
                last_die_direction = bullet->get_position() - position;//��¼���һ�����˷���
                if (hp <= 0)
                {
                    velocity.x = last_die_direction.x < 0 ? 0.35f : -0.35f;
                    velocity.y = -1.0f;
                }
            }
        }
    }

protected:
    const float jump_velocity = -0.85f;//��Ծ�ٶ�
    const float gravity = 1.6e-3f;//����
    const float run_velocity = 0.55f;//��ұ����ٶ�
    int mp = 0;//��ɫ����
    int hp = 100;//��ɫѪ��

    Vector2 size;//��ɫ�ߴ�
    Vector2 velocity;//����ٶ�
    Vector2 position;//���λ��

    Animation animation_idle_left;
    Animation animation_idle_right;
    Animation animation_run_left;
    Animation animation_run_right;
    Animation animation_attack_ex_left;
    Animation animation_attack_ex_right;
    Animation animation_die_left;
    Animation animation_die_right;
    Animation* current_animation = nullptr;//��ǰ����
    PlayerID id = PlayerID::P1;

    Animation  animation_jump_effect;
    Animation  animation_land_effect;
    bool is_jump_effect_visible = false;//�Ƿ���ʾ��Ծ����
    bool is_land_effect_visible = false;//�Ƿ���ʾ��½����
    Vector2 pos_jump_effect;//��Ծ����λ��
    Vector2 pos_land_effect;//��½����λ��
    bool left_key_down = false;
    bool right_key_down = false;
    bool facing_right = true;//��ҳ���

    IMAGE img_sketch;//��ӰͼƬ
    bool is_showing_sketch_frame = false;//��ǰ֡�Ƿ���ʾ��Ӱ
    Timer timer_invulnerable;//�޵м�ʱ��
    Timer timer_showing_sketch_frame;//��ʾ��Ӱ��ʱ��,���޵�״̬��˸��ʱ��

    bool can_attack = true;//����Ƿ������ͨ����
    bool is_attacking_ex = false;//����Ƿ����ڳ�������
    bool is_invulnerable = false;//����Ƿ��޵�
    int attack_cd = 300;//��ͨ������ȴʱ��
    Timer attack_timer_cd;//��ͨ������ʱ��

    Timer timer_run_effect_generator;//�ܶ���Ч���ӷ��䶨ʱ��
    Timer timer_die_effect_generator;//������Ч���ӷ��䶨ʱ��
    std::vector<Particle> particle_list;//���Ӽ���

    bool is_cursor_visible = true;//�Ƿ���ʾ���
    Timer timer_cursor_visible;//�����ʾ��ʱ��

    Vector2 last_die_direction;//���һ�����˷���
};
#endif