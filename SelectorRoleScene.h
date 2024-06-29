#ifndef SELECTORROLESCENE_H
#define SELECTORROLESCENE_H
#include "Scene.h"
#include "SceneManager.h"
#include "Animation.h"
#include "PlayerPeashooter.h"
#include "PlayerSunflower.h"

extern Player* player1;
extern Player* player2;
extern IMAGE* img_player1_avatar;
extern IMAGE* img_player2_avatar;

extern IMAGE img_VS;//vs艺术字图片
extern IMAGE img_1P_text;//1P文本图片
extern IMAGE img_2P_text;//2P文本图片
extern IMAGE img_1P_desc;//1P描述图片
extern IMAGE img_2P_desc;//2P描述图片
extern IMAGE img_gravestone_left;//左边墓碑图片
extern IMAGE img_gravestone_right;//右边墓碑图片
extern IMAGE img_selector_role_tip_text;//角色选择提示文本图片
extern IMAGE img_selector_role_tip_bg;//角色选择提示背景
extern IMAGE img_1P_selector_btn_idle_left;//1P选择按钮默认状态左图片
extern IMAGE img_1P_selector_btn_idle_right;//1P选择按钮默认状态右图片
extern IMAGE img_1P_selector_btn_down_left;//1P选择按钮按下状态左图片
extern IMAGE img_1P_selector_btn_down_right;//1P选择按钮按下状态右图片
extern IMAGE img_2P_selector_btn_idle_left;//2P选择按钮默认状态左图片
extern IMAGE img_2P_selector_btn_idle_right;//2P选择按钮默认状态右图片
extern IMAGE img_2P_selector_btn_down_left;//2P选择按钮按下状态左图片
extern IMAGE img_2P_selector_btn_down_right;//2P选择按钮按下状态右图片
extern IMAGE img_peashooter_selector_bg_left;//角色选择界面朝向左的豌豆射手背景图片
extern IMAGE img_peashooter_selector_bg_right;//角色选择界面朝向右的豌豆射手背景图片
extern IMAGE img_sunflower_selector_bg_left;//角色选择界面朝向左的向日葵背景图片
extern IMAGE img_sunflower_selector_bg_right;//角色选择界面朝向右的向日葵背景图片
extern Atlas atlas_peashooter_idle_right;//豌豆射手右动画图集
extern Atlas atlas_sunflower_idle_right;//向日葵右动画图集
extern IMAGE img_avatar_peashooter;//豌豆射手头像图片
extern IMAGE img_avatar_sunflower;//向日葵头像图片

extern SceneManager scene_manager;

class SelectorRoleScene : public Scene
{
public:
    SelectorRoleScene() = default;
    ~SelectorRoleScene() = default;
    void on_enter() override
    {
        //设置角色动画图集和帧间隔
        animation_peashooter.set_atlas(&atlas_peashooter_idle_right);
        animation_sunflower.set_atlas(&atlas_sunflower_idle_right);
        animation_peashooter.set_interval(100);
        animation_sunflower.set_interval(100);

        static const int OFFSET_X = 50;

        pos_img_VS.y = (getheight() - img_VS.getheight()) / 2;
        pos_img_VS.x = (getwidth() - img_VS.getwidth()) / 2;
        pos_img_tip.x = (getwidth() - img_selector_role_tip_text.getwidth()) / 2;
        pos_img_tip.y = getheight() - 125;

        pos_img_1P_text.x = (getwidth() / 2 - img_1P_text.getwidth()) / 2 - OFFSET_X;
        pos_img_1P_text.y = 35;
        pos_img_2P_text.x = getwidth() / 2 + (getwidth() / 2 - img_2P_text.getwidth()) / 2 + OFFSET_X;
        pos_img_2P_text.y = pos_img_1P_text.y;

        pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
        pos_img_1P_desc.y = getheight() - 150;
        pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
        pos_img_2P_desc.y = pos_img_1P_desc.y;

        pos_img_1P_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X;
        pos_img_1P_gravestone.y = pos_img_1P_text.y + img_1P_text.getheight() + 35;
        pos_img_2P_gravestone.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
        pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;

        pos_animation_1P.x = (getwidth() / 2 - atlas_peashooter_idle_right.GetImage(0)->getwidth()) / 2 - OFFSET_X;
        pos_animation_1P.y = pos_img_1P_gravestone.y + 80;
        pos_animation_2P.x = getwidth() / 2 + (getwidth() / 2 - atlas_peashooter_idle_right.GetImage(0)->getwidth()) / 2 + OFFSET_X;
        pos_animation_2P.y = pos_animation_1P.y;

        pos_img_1P_name.y = pos_animation_1P.y + 155;
        pos_img_2P_name.y = pos_img_1P_name.y;

        pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
        pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight()) / 2;
        pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
        pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;

        pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
        pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
        pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
        pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;
    }
    void on_exit() override
    {
        switch (player_type_1P)
        {
            case PlayerType::peashooter:
                player1 = new PlayerPeashooter();
                img_player1_avatar = &img_avatar_peashooter;
                break;
            case PlayerType::sunflower:
                player1 = new PlayerSunflower();
                img_player1_avatar = &img_avatar_sunflower;
                break;
        }
        player1->set_playerid(PlayerID::P1);
        switch (player_type_2P)
        {
            case PlayerType::peashooter:
                player2 = new PlayerPeashooter(false);
                img_player2_avatar = &img_avatar_peashooter;
                break;
            case PlayerType::sunflower:
                player2 = new PlayerSunflower(false);
                img_player2_avatar = &img_avatar_sunflower;
                break;
        }
        player2->set_playerid(PlayerID::P2);
        mciSendString(_T("stop bgm_menu"), NULL, 0, NULL);
    }
    void on_update(int dt) override
    {
        animation_peashooter.on_update(dt);
        animation_sunflower.on_update(dt);
        selector_bg_scroll_offestx += 5;//向右移动5像素
        if (selector_bg_scroll_offestx >= img_peashooter_selector_bg_left.getwidth())
            selector_bg_scroll_offestx = 0;
    }
    void on_draw(const Camera& camera) override
    {
        putimage(0, 0, &img_selector_role_tip_bg);
        putimage_alpha(selector_bg_scroll_offestx - img_1P_selector_bg->getwidth(), 0, img_1P_selector_bg);
        putimage_alpha(selector_bg_scroll_offestx, 0,
            img_1P_selector_bg->getwidth() - selector_bg_scroll_offestx, 0, img_1P_selector_bg, 0, 0);
        putimage_alpha(getwidth() - img_2P_selector_bg->getwidth(), 0,
            img_2P_selector_bg->getwidth() - selector_bg_scroll_offestx, 0, img_2P_selector_bg, selector_bg_scroll_offestx, 0);
        putimage_alpha(getwidth() - selector_bg_scroll_offestx, 0, img_2P_selector_bg);

        putimage_alpha(pos_img_VS.x, pos_img_VS.y, &img_VS);
        putimage_alpha(pos_img_1P_text.x, pos_img_1P_text.y, &img_1P_text);
        putimage_alpha(pos_img_2P_text.x, pos_img_2P_text.y, &img_2P_text);

        putimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
        putimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);

        switch (player_type_1P)
        {
            case PlayerType::peashooter:
                animation_peashooter.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);//绘制动画
                //绘制名字
                pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
                outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_peashooter_name);
                //背景剪影
                img_1P_selector_bg = &img_peashooter_selector_bg_right;
                break;
            case PlayerType::sunflower:
                animation_sunflower.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
                pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
                outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_sunflower_name);
                img_1P_selector_bg = &img_sunflower_selector_bg_right;
                break;
        }
        switch (player_type_2P)
        {
            case PlayerType::peashooter:
                animation_peashooter.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
                pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_peashooter_name)) / 2;
                outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_peashooter_name);
                img_2P_selector_bg = &img_peashooter_selector_bg_left;
                break;
            case PlayerType::sunflower:
                animation_sunflower.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
                pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_sunflower_name)) / 2;
                outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_sunflower_name);
                img_2P_selector_bg = &img_sunflower_selector_bg_left;
                break;
        }

        putimage_alpha(pos_1P_selector_btn_left.x, pos_1P_selector_btn_left.y,
            is_btn_1P_left_down ? &img_1P_selector_btn_down_left : &img_1P_selector_btn_idle_left);
        putimage_alpha(pos_1P_selector_btn_right.x, pos_1P_selector_btn_right.y,
            is_btn_1P_right_down ? &img_1P_selector_btn_down_right : &img_1P_selector_btn_idle_right);
        putimage_alpha(pos_2P_selector_btn_left.x, pos_2P_selector_btn_left.y,
            is_btn_2P_left_down ? &img_2P_selector_btn_down_left : &img_2P_selector_btn_idle_left);
        putimage_alpha(pos_2P_selector_btn_right.x, pos_2P_selector_btn_right.y,
            is_btn_2P_right_down ? &img_2P_selector_btn_down_right : &img_2P_selector_btn_idle_right);

        putimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
        putimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);

        putimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_role_tip_text);
    }

    void on_input(const ExMessage& msg) override
    {
        if (msg.message == WM_KEYDOWN)
            switch (msg.vkcode)
            {
                case 0x41:
                    is_btn_1P_left_down = true;
                    break;
                case 0x44:
                    is_btn_1P_right_down = true;
                    break;
                case VK_LEFT:
                    is_btn_2P_left_down = true;
                    break;
                case VK_RIGHT:
                    is_btn_2P_right_down = true;
                    break;
            }
        else if (msg.message == WM_KEYUP)
        {
            switch (msg.vkcode)
            {
                case 0x41:
                    is_btn_1P_left_down = false;
                    //将玩家选择值转为int并减1,加上Invalid的偏移量来确保值始终大于等于0,取模确保最终结果不会大于等于Invalid的值
                    player_type_1P = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_1P - 1) % (int)PlayerType::Invalid);
                    mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
                    break;
                case 0x44:
                    is_btn_1P_right_down = false;
                    player_type_1P = (PlayerType)(((int)player_type_1P + 1) % (int)PlayerType::Invalid);
                    mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
                    break;
                case VK_LEFT:
                    is_btn_2P_left_down = false;
                    player_type_2P = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_2P - 1) % (int)PlayerType::Invalid);
                    mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
                    break;
                case VK_RIGHT:
                    is_btn_2P_right_down = false;
                    player_type_2P = (PlayerType)(((int)player_type_2P + 1) % (int)PlayerType::Invalid);
                    mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
                    break;
                case VK_RETURN:
                    scene_manager.changeScene(SceneManager::SceneType::Game);
                    mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
                    break;
            }
        }
    }
private:
    void outtextxy_shaded(int x, int y, LPCTSTR str)//绘制带有阴影的文本
    {
        settextcolor(RGB(45, 45, 45));
        outtextxy(x + 3, y + 3, str);
        settextcolor(RGB(255, 255, 255));
        outtextxy(x, y, str);
    }
private:
    bool is_btn_1P_left_down = false;
    bool is_btn_1P_right_down = false;
    bool is_btn_2P_left_down = false;
    bool is_btn_2P_right_down = false;

    IMAGE* img_1P_selector_bg = &img_peashooter_selector_bg_right;
    IMAGE* img_2P_selector_bg = &img_sunflower_selector_bg_left;
    enum class PlayerType
    {
        peashooter,
        sunflower,
        Invalid
    };
    int selector_bg_scroll_offestx = 0;//背景板滚动偏移量
    Animation animation_peashooter;//豌豆射手动画
    Animation animation_sunflower;//向日葵动画
    PlayerType player_type_1P = PlayerType::peashooter;//1P角色类型
    PlayerType player_type_2P = PlayerType::sunflower;//2P角色类型
    LPCTSTR str_peashooter_name = _T("豌豆射手");
    LPCTSTR str_sunflower_name = _T("向日葵");

    POINT pos_img_VS = { 0 };//vs艺术字图片位置
    POINT pos_img_tip = { 0 };//提示信息文本图片位置
    POINT pos_img_1P_text = { 0 };//1P文本图片位置
    POINT pos_img_2P_text = { 0 };//2P文本图片位置
    POINT pos_img_1P_desc = { 0 };//1P描述图片位置
    POINT pos_img_2P_desc = { 0 };//2P描述图片位置
    POINT pos_img_1P_name = { 0 };//1P角色名称位置
    POINT pos_img_2P_name = { 0 };//2P角色名称位置
    POINT pos_animation_1P = { 0 };//1P动画位置
    POINT pos_animation_2P = { 0 };//2P动画位置
    POINT pos_img_1P_gravestone = { 0 };//1P墓碑位置
    POINT pos_img_2P_gravestone = { 0 };//2P墓碑位置
    POINT pos_1P_selector_btn_left = { 0 };//1P选择按钮左位置
    POINT pos_1P_selector_btn_right = { 0 };//1P选择按钮右位置
    POINT pos_2P_selector_btn_left = { 0 };//2P选择按钮左位置
    POINT pos_2P_selector_btn_right = { 0 };//2P选择按钮右位置
};
#endif // SELECTORROLESCENE_H