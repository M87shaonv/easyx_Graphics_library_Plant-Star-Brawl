#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include "Scene.h"
#include "SceneManager.h"

extern SceneManager scene_manager;

class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() = default;

    void on_enter() override
    {}
    void on_exit() override
    {}
    void on_update() override
    {}
    void on_draw() override
    {
        outtextxy(100, 100, _T("Game Scene"));
    }
    void on_input(const ExMessage& msg) override
    {
        if (msg.message == WM_KEYDOWN)//按下任意键切换到主菜单场景
            scene_manager.changeScene(SceneManager::SceneType::Menu);
    }
private:
};
#endif // _GAME_SCENE_H_