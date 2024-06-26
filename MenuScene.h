#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_
#include "Scene.h"
#include "SceneManager.h"

extern SceneManager scene_manager;
class MenuScene : public Scene
{
public:
    MenuScene() = default;
    ~MenuScene() = default;

    void on_enter() override
    {}
    void on_exit() override
    {}
    void on_update() override
    {}
    void on_draw() override
    {
        outtextxy(100, 100, _T("Menu Scene"));
    }
    void on_input(const ExMessage& msg) override
    {
        if (msg.message == WM_KEYDOWN)//按下任意键切换到游戏场景
            scene_manager.changeScene(SceneManager::SceneType::Game);
    }
private:
};

#endif // MENU_SCENE_H
