#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_
#include "Scene.h"
#include "SceneManager.h"
#include "util.h"
extern SceneManager scene_manager;
extern IMAGE img_menu_bg;//背景图片
class MenuScene : public Scene
{
private:

public:
    MenuScene() = default;
    ~MenuScene() = default;

    void on_enter() override
    {
        mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
        SetVolume("bgm_menu", 1000);
    }
    void on_exit() override
    {}
    void on_update(int dt) override
    {}
    void on_draw(const Camera& camera) override
    {
        putimage(0, 0, &img_menu_bg);
    }
    void on_input(const ExMessage& msg) override
    {
        if (msg.message == WM_KEYUP)//任意键抬起时进入角色选择界面
        {
            mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
            scene_manager.changeScene(SceneManager::SceneType::SelectorRole);
        }
    }
};

#endif // MENU_SCENE_H
