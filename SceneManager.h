#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__
#include "Scene.h"
extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* selector_role_scene;
class SceneManager
{
public:
    SceneManager() = default;
    ~SceneManager() = default;
    enum class SceneType
    {
        Menu,
        Game,
        SelectorRole,
    };
public:
    void setCurrentScene(Scene* scene)//设置当前场景
    {
        current_scene = scene;
        current_scene->on_enter();
    }
    void changeScene(SceneType scene_type)//切换场景
    {
        current_scene->on_exit();
        switch (scene_type)
        {
            case SceneType::Menu:
                current_scene = menu_scene;
                break;
            case SceneType::Game:
                current_scene = game_scene;
                break;
            case SceneType::SelectorRole:
                current_scene = selector_role_scene;
                break;
            default:
                break;
        }
        current_scene->on_enter();
    }
    void on_update(int dt)//更新当前场景
    {
        current_scene->on_update(dt);
    }
    void on_draw(const Camera& camera)//绘制当前场景
    {
        current_scene->on_draw(camera);
    }
    void on_input(const ExMessage& msg)//处理输入
    {
        current_scene->on_input(msg);
    }

private:
    Scene* current_scene = nullptr;
};
#endif // __SCENEMANAGER_H__