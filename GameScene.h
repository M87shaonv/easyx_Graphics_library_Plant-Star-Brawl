#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include "Scene.h"
#include "SceneManager.h"
#include "Platform.h"
#include "Player.h"
#include "Vector2.h"
#include "Animation.h"
#include "Status_Bar.h"
extern Player* player1;
extern Player* player2;
extern IMAGE* img_player1_avatar;
extern IMAGE* img_player2_avatar;
extern SceneManager scene_manager;
extern Camera camera;
extern std::vector<Platform> platforms;
extern std::vector<Bullet*> bullets;//�ӵ�����
extern IMAGE img_sky;//��ձ���ͼƬ
extern IMAGE img_hills;//ɽ�𱳾�ͼƬ
extern IMAGE img_1P_winner;//1Pʤ��ͼƬ
extern IMAGE img_2P_winner;//2Pʤ��ͼƬ
extern IMAGE img_winner_bar;//��ʤ����ı�����

class GameScene : public Scene
{
private:
    POINT pos_img_sky = { 0 };//��ձ���ͼƬλ��
    POINT pos_img_hills = { 0 };//ɽ�𱳾�ͼƬλ��
    Status_Bar status_bar_P1;//���1״̬��
    Status_Bar status_bar_P2;
    bool is_game_over = false;
    POINT pos_img_winner_bar = { 0 };//���㶯Ч����λ��
    POINT pos_img_winner_text = { 0 };//���㶯Ч�ı�λ��
    int pos_x_img_winner_bar_dst = 0;//���㶯Ч�����ƶ�Ŀ��λ��
    int pos_x_img_winner_text_dst = 0;//���㶯Ч�ı��ƶ�Ŀ��λ��
    Timer timer_winner_slide_in;//���㶯Ч�������ı��Ļ���ʱ��
    Timer timer_winner_slide_out;//���㶯Ч�������ı��Ļ���ʱ��
    bool is_slide_out_started = false;//�Ƿ�ʼ����
    const float speed_winner_bar = 3.0f;//���㶯Ч���������ٶ�
    const float speed_winner_text = 1.5f;//���㶯Ч�ı������ٶ�
public:
    GameScene() = default;
    ~GameScene() = default;

    void on_enter() override
    {
        is_game_over = false;
        is_slide_out_started = false;

        pos_img_winner_bar.x = -img_winner_bar.getwidth();
        pos_img_winner_bar.y = (getheight() - img_winner_bar.getheight()) / 2;
        pos_x_img_winner_bar_dst = (getwidth() - img_winner_bar.getwidth()) / 2;

        pos_img_winner_text.x = pos_img_winner_bar.x;
        pos_img_winner_text.y = (getheight() - img_1P_winner.getheight()) / 2;
        pos_x_img_winner_text_dst = (getwidth() - img_1P_winner.getwidth()) / 2;

        timer_winner_slide_in.restart();
        timer_winner_slide_in.setWaitTime(2000);//���û���ʱ��
        timer_winner_slide_in.setOneTimeTrigger(true);
        timer_winner_slide_in.setCallback([&]()
            {
                is_slide_out_started = true;
            });
        timer_winner_slide_out.restart();
        timer_winner_slide_out.setWaitTime(1000);
        timer_winner_slide_out.setOneTimeTrigger(true);
        timer_winner_slide_out.setCallback([&]()
            {
                scene_manager.changeScene(SceneManager::SceneType::Menu);//�л����˵�����
            });

        status_bar_P1.set_avatar(img_player1_avatar);
        status_bar_P2.set_avatar(img_player2_avatar);
        status_bar_P1.set_pos(Vector2(235, 625));
        status_bar_P2.set_pos(Vector2(675, 625));

        player1->set_position(Vector2(200, 95));
        player2->set_position(Vector2(975, 95));
        pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
        pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;

        pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2;
        pos_img_hills.y = (getheight() - img_hills.getheight()) / 2;
        platforms.resize(4);

        Platform& large_platform = platforms[0];
        large_platform.img = &img_platform_large;
        large_platform.draw_pos.x = 122;
        large_platform.draw_pos.y = 455; //ʵ����ײλ��С��ͼƬ�ߴ�
        large_platform.collisionShape.left = (float)large_platform.draw_pos.x + 30;
        large_platform.collisionShape.right = (float)large_platform.draw_pos.x + img_platform_large.getwidth() - 30;
        large_platform.collisionShape.y = (float)large_platform.draw_pos.y + 60;

        Platform& small_platform_1 = platforms[1];
        small_platform_1.img = &img_platform_small;
        small_platform_1.draw_pos.x = 175;
        small_platform_1.draw_pos.y = 360;
        small_platform_1.collisionShape.left = (float)small_platform_1.draw_pos.x + 40;
        small_platform_1.collisionShape.right = (float)small_platform_1.draw_pos.x + img_platform_small.getwidth() - 40;
        small_platform_1.collisionShape.y = (float)small_platform_1.draw_pos.y + img_platform_small.getheight() / 2;

        Platform& small_platform_2 = platforms[2];
        small_platform_2.img = &img_platform_small;
        small_platform_2.draw_pos.x = 855;
        small_platform_2.draw_pos.y = 360;
        small_platform_2.collisionShape.left = (float)small_platform_2.draw_pos.x + 40;
        small_platform_2.collisionShape.right = (float)small_platform_2.draw_pos.x + img_platform_small.getwidth() - 40;
        small_platform_2.collisionShape.y = (float)small_platform_2.draw_pos.y + img_platform_small.getheight() / 2;

        Platform& small_platform_3 = platforms[3];
        small_platform_3.img = &img_platform_small;
        small_platform_3.draw_pos.x = 515;
        small_platform_3.draw_pos.y = 225;
        small_platform_3.collisionShape.left = (float)small_platform_3.draw_pos.x + 40;
        small_platform_3.collisionShape.right = (float)small_platform_3.draw_pos.x + img_platform_small.getwidth() - 40;
        small_platform_3.collisionShape.y = (float)small_platform_3.draw_pos.y + img_platform_small.getheight() / 2;

        mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);
    }
    void on_exit() override
    {
        delete player1; player1 = nullptr;
        delete player2; player2 = nullptr;
        ISDEBUGING = false;
        bullets.clear();
        camera.ResetPosition();
    }
    void on_update(int dt) override
    {
        player1->on_update(dt);
        player2->on_update(dt);
        camera.Update(dt);

        bullets.erase(//remove_if�Ὣ��������������Ԫ���ƶ���������ĩβ��������һ��ָ����ЩԪ����ʼλ�õĵ�����
            std::remove_if(
                bullets.begin(),
                bullets.end(),
                [](const Bullet* bullet) {
                    bool deletable = bullet->check_can_remove();
                    if (deletable)
                        delete bullet;
                    return deletable;
                }
            ),
            bullets.end()
        );

        for (Bullet* bullet : bullets)
            bullet->on_update(dt);

        const Vector2& pos_player1 = player1->get_position();
        const Vector2& pos_player2 = player2->get_position();
        if (pos_player1.y >= getheight())
            player1->set_hp(0);
        if (pos_player2.y >= getheight())
            player2->set_hp(0);
        if (player1->get_hp() <= 0 || player2->get_hp() <= 0)
        {
            if (!is_game_over)
            {
                mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
                mciSendString(_T("play ui_win from 0"), NULL, 0, NULL);
            }

            is_game_over = true;
        }

        status_bar_P1.set_hp(player1->get_hp());
        status_bar_P1.set_mp(player1->get_mp());
        status_bar_P2.set_hp(player2->get_hp());
        status_bar_P2.set_mp(player2->get_mp());

        if (is_game_over)
        {
            pos_img_winner_bar.x += (int)(speed_winner_bar * dt);
            pos_img_winner_text.x += (int)(speed_winner_text * dt);
            if (!is_slide_out_started)//���붯��δ��ʼ
            {
                timer_winner_slide_in.Update(dt);//���»���ʱ��
                if (pos_img_winner_bar.x > pos_x_img_winner_bar_dst)
                    pos_img_winner_bar.x = pos_x_img_winner_bar_dst;
                if (pos_img_winner_text.x > pos_x_img_winner_text_dst)
                    pos_img_winner_text.x = pos_x_img_winner_text_dst;
            }
            else
                timer_winner_slide_out.Update(dt);//���»���ʱ��
        }
    }
    void on_draw(const Camera& camera) override
    {
        putimage_alpha(pos_img_sky.x, pos_img_sky.y, &img_sky);
        putimage_alpha(pos_img_hills.x, pos_img_hills.y, &img_hills);

        for (const Platform& platform : platforms)
            platform.on_draw(camera);

        player1->on_draw(camera);
        player2->on_draw(camera);

        for (const Bullet* bullet : bullets)
            bullet->on_draw(camera);
        if (is_game_over)
        {
            putimage_alpha(pos_img_winner_bar.x, pos_img_winner_bar.y, &img_winner_bar);
            putimage_alpha(pos_img_winner_text.x, pos_img_winner_text.y,
                player1->get_hp() > 0 ? &img_1P_winner : &img_2P_winner);
        }
        else
        {
            status_bar_P1.on_draw();
            status_bar_P2.on_draw();
        }

        if (!ISDEBUGING) return;//û�п���������ģʽ

        //������ײ��
        player1->debug_draw(camera);
        player2->debug_draw(camera);
        for (const Platform& platform : platforms)
            platform.debug_draw(camera);
        for (const Bullet* bullet : bullets)
            bullet->debug_draw(camera);
    }
    void on_input(const ExMessage& msg) override
    {
        switch (msg.message)
        {
            case WM_KEYUP:
                if (msg.vkcode == 0x51)//Q
                    ISDEBUGING = !ISDEBUGING;
                break;
        }
        player1->Input(msg);
        player2->Input(msg);
    }
};
#endif // _GAME_SCENE_H_