#include <graphics.h>
#include "main.h"
#include "SceneManager.h"
#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "SelectorRoleScene.h"
#include "Atlas.h"
#include "util.h"
ExMessage msg;
Scene* menu_scene = new MenuScene();
Scene* game_scene = new GameScene();
Scene* selector_role_scene = new SelectorRoleScene();
SceneManager scene_manager;
int main()
{
    init();

    while (true)
    {
        DWORD frame_start_time = GetTickCount();
        while (peekmessage(&msg))
        {
            scene_manager.on_input(msg);
        }
        scene_manager.on_update();//更新场景
        cleardevice();//清除屏幕内容
        scene_manager.on_draw();//绘制场景
        FlushBatchDraw();//将之前缓存图形绘制操作渲染到屏幕上

        DWORD frame_end_time = GetTickCount();
        DWORD frame_delta_time = frame_end_time - frame_start_time;
        if (frame_delta_time < 1000 / FPS)
            Sleep(1000 / FPS - frame_delta_time);
    }
    //游戏结束,释放资源

    EndBatchDraw();//关闭批处理绘制
}
void init()
{
    load_game_resources();//加载游戏资源
    initgraph(1280, 720, EW_SHOWCONSOLE);//第三个参数显示控制台
    BeginBatchDraw();//开启批处理绘制
    scene_manager.setCurrentScene(menu_scene); //设置当前场景为菜单场景
}
void flip_atlas(Atlas& src, Atlas& dst)
{
    dst.clear();
    for (int i = 0; i < src.size(); ++i)
    {
        IMAGE img_flpipped;
        flip_image(src.GetImage(i), &img_flpipped);//翻转图片
        dst.AddImage(img_flpipped);
    }
}
void load_game_resources()
{
    AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);//加载字体
    loadimage(&img_menu_bg, _T("resources/menu_background.png"));
    loadimage(&img_VS, _T("resources/VS.png"));
    loadimage(&img_1P_desc, _T("resources/1P_desc.png"));
    loadimage(&img_2P_desc, _T("resources/2P_desc.png"));
    loadimage(&img_gravestone_right, _T("resources/gravestone.png"));
    flip_image(&img_gravestone_right, &img_gravestone_left);//翻转图片并存储
    loadimage(&img_selector_role_tip_text, _T("resources/selector_tip.png"));
    loadimage(&img_selector_role_tip_bg, _T("resources/selector_background.png"));

    loadimage(&img_1P_selector_btn_idle_right, _T("resources/1P_selector_btn_idle.png"));
    flip_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
    loadimage(&img_1P_selector_btn_down_right, _T("resources/1P_selector_btn_down.png"));
    flip_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);

    loadimage(&img_2P_selector_btn_idle_right, _T("resources/2P_selector_btn_idle.png"));
    flip_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
    loadimage(&img_2P_selector_btn_down_right, _T("resources/2P_selector_btn_down.png"));
    flip_image(&img_2P_selector_btn_down_right, &img_2P_selector_btn_down_left);

    loadimage(&img_peashooter_selector_bg_right, _T("resources/peashooter_selector_background.png"));
    flip_image(&img_peashooter_selector_bg_right, &img_peashooter_selector_bg_left);
    loadimage(&img_sunflower_selector_bg_right, _T("resources/sunflower_selector_background.png"));
    flip_image(&img_sunflower_selector_bg_right, &img_sunflower_selector_bg_left);

    loadimage(&img_sky, _T("resources/sky.png"));
    loadimage(&img_hills, _T("resources/hills.png"));
    loadimage(&img_platform_large, _T("resources/platform_large.png"));
    loadimage(&img_platform_small, _T("resources/platform_small.png"));

    loadimage(&img_1P_cursor, _T("resources/1P_cursor.png"));
    loadimage(&img_2P_cursor, _T("resources/2P_cursor.png"));

    atlas_peashooter_idle_right.LoadFormFile(_T("resources/peashooter_idle_%d.png"), 9);
    flip_atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
    atlas_peashooter_run_right.LoadFormFile(_T("resources/peashooter_run_%d.png"), 5);
    flip_atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);
    atlas_peashooter_attack_ex_right.LoadFormFile(_T("resources/atlas_peashooter_attack_ex_%d.png"), 9);
    flip_atlas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);
    atlas_peashooter_die_right.LoadFormFile(_T("resources/peashooter_die_%d.png"), 4);
    flip_atlas(atlas_peashooter_die_right, atlas_peashooter_die_left);

    atlas_sunflower_idle_right.LoadFormFile(_T("resources/sunflower_idle_%d.png"), 9);
    flip_atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
    atlas_sunflower_run_right.LoadFormFile(_T("resources/sunflower_run_%d.png"), 5);
    flip_atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);
    atlas_sunflower_attack_ex_right.LoadFormFile(_T("resources/atlas_sunflower_attack_ex_%d.png"), 9);
    flip_atlas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);
    atlas_sunflower_die_right.LoadFormFile(_T("resources/sunflower_die_%d.png"), 4);
    flip_atlas(atlas_sunflower_die_right, atlas_sunflower_die_left);

    loadimage(&img_pea, _T("resources/pea.png"));
    atlas_pea_break.LoadFormFile(_T("resources/pea_break_%d.png"), 3);
    atlas_sun.LoadFormFile(_T("resources/sun_%d.png"), 5);
    atlas_sun_explode.LoadFormFile(_T("resources/sun_explode_%d.png"), 5);
    atlas_sun_ex.LoadFormFile(_T("resources/sun_ex_%d.png"), 5);
    atlas_sun_ex_explode.LoadFormFile(_T("resources/sun_ex_explode_%d.png"), 5);
    atlas_sun_text.LoadFormFile(_T("resources/sun_text_%d.png"), 6);

    atlas_run_effect.LoadFormFile(_T("resources/run_effect_%d.png"), 4);
    atlas_jump_effect.LoadFormFile(_T("resources/jump_effect_%d.png"), 5);
    atlas_land_effect.LoadFormFile(_T("resources/land_effect_%d.png"), 2);

    loadimage(&img_1P_winner, _T("resources/1P_winner.png"));
    loadimage(&img_2P_winner, _T("resources/2P_winner.png"));
    loadimage(&img_winner_bar, _T("resources/winner_bar.png"));

    loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
    loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));

    mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
    mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);
}