#ifndef _MAIN_H_
#define  _MAIN_H_
#include "Atlas.h"
constexpr int FPS = 120;
void init();//初始化
void flip_atlas(Atlas& src, Atlas& dst);//翻转图集
void load_game_resources();//加载游戏资源

#pragma region 图片资源
#pragma comment(lib,"Winmm.lib")

IMAGE img_menu_bg;//菜单背景
IMAGE img_VS;//vs艺术字图片

IMAGE img_1P_text;//1P文本图片
IMAGE img_2P_text;//2P文本图片

IMAGE img_1P_desc;//1P描述图片
IMAGE img_2P_desc;//2P描述图片
IMAGE img_gravestone_left;//左边墓碑图片
IMAGE img_gravestone_right;//右边墓碑图片

IMAGE img_selector_role_tip_text;//角色选择提示文本图片
IMAGE img_selector_role_tip_bg;//角色选择提示背景

IMAGE img_1P_selector_btn_idle_left;//1P选择按钮默认状态左图片
IMAGE img_1P_selector_btn_idle_right;//1P选择按钮默认状态右图片
IMAGE img_1P_selector_btn_down_left;//1P选择按钮按下状态左图片
IMAGE img_1P_selector_btn_down_right;//1P选择按钮按下状态右图片

IMAGE img_2P_selector_btn_idle_left;//2P选择按钮默认状态左图片
IMAGE img_2P_selector_btn_idle_right;//2P选择按钮默认状态右图片
IMAGE img_2P_selector_btn_down_left;//2P选择按钮按下状态左图片
IMAGE img_2P_selector_btn_down_right;//2P选择按钮按下状态右图片

IMAGE img_peashooter_selector_bg_left;//角色选择界面朝向左的豌豆射手背景图片
IMAGE img_peashooter_selector_bg_right;//角色选择界面朝向右的豌豆射手背景图片
IMAGE img_sunflower_selector_bg_left;//角色选择界面朝向左的向日葵背景图片
IMAGE img_sunflower_selector_bg_right;//角色选择界面朝向右的向日葵背景图片

IMAGE img_sky;//天空背景图片
IMAGE img_hills;//山丘背景图片
IMAGE img_platform_large;//大型平台图片
IMAGE img_platform_small;//小型平台图片

IMAGE img_1P_cursor;//1P光标图片
IMAGE img_2P_cursor;//2P光标图片

IMAGE img_pea;//豌豆图片
IMAGE img_1P_winner;//1P胜利图片
IMAGE img_2P_winner;//2P胜利图片
IMAGE img_winner_bar;//获胜玩家文本背景

IMAGE img_avatar_peashooter;//豌豆射手头像图片
IMAGE img_avatar_sunflower;//向日葵头像图片
#pragma endregion

#pragma region 图集资源
Atlas atlas_peashooter_idle_left;//豌豆射手左动画图集
Atlas atlas_peashooter_idle_right;//豌豆射手右动画图集
Atlas atlas_peashooter_run_left;//豌豆射手左跑动动画图集
Atlas atlas_peashooter_run_right;//豌豆射手右跑动动画图集
Atlas atlas_peashooter_attack_ex_left;//豌豆射手左攻击动画图集
Atlas atlas_peashooter_attack_ex_right;//豌豆射手右攻击动画图集
Atlas atlas_peashooter_die_left;//豌豆射手左死亡动画图集
Atlas atlas_peashooter_die_right;//豌豆射手右死亡动画图集

Atlas atlas_sunflower_idle_left;//向日葵左动画图集
Atlas atlas_sunflower_idle_right;//向日葵右动画图集
Atlas atlas_sunflower_run_left;//向日葵左跑动动画图集
Atlas atlas_sunflower_run_right;//向日葵右跑动动画图集
Atlas atlas_sunflower_attack_ex_left;//向日葵左攻击动画图集
Atlas atlas_sunflower_attack_ex_right;//向日葵右攻击动画图集
Atlas atlas_sunflower_die_left;//向日葵左死亡动画图集
Atlas atlas_sunflower_die_right;//向日葵右死亡动画图集

Atlas atlas_pea_break;//豌豆碎片动画图集
Atlas atlas_sun;//太阳动画图集
Atlas atlas_sun_explode;//太阳爆炸动画图集
Atlas atlas_sun_ex;//特殊太阳动画图集
Atlas atlas_sun_ex_explode;//特殊太阳爆炸动画图集
Atlas atlas_sun_text;//日文本动画图集

Atlas atlas_run_effect;//跑动特效动画图集
Atlas atlas_jump_effect;//跳跃特效动画图集
Atlas atlas_land_effect;//落地特效动画图集
#pragma endregion
#endif //  _MAIN_H_
