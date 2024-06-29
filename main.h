#ifndef _MAIN_H_
#define  _MAIN_H_
#include "Atlas.h"
constexpr int FPS = 120;
void init();//��ʼ��
void flip_atlas(Atlas& src, Atlas& dst);//��תͼ��
void load_game_resources();//������Ϸ��Դ

#pragma region ͼƬ��Դ
#pragma comment(lib,"Winmm.lib")

IMAGE img_menu_bg;//�˵�����
IMAGE img_VS;//vs������ͼƬ

IMAGE img_1P_text;//1P�ı�ͼƬ
IMAGE img_2P_text;//2P�ı�ͼƬ

IMAGE img_1P_desc;//1P����ͼƬ
IMAGE img_2P_desc;//2P����ͼƬ
IMAGE img_gravestone_left;//���Ĺ��ͼƬ
IMAGE img_gravestone_right;//�ұ�Ĺ��ͼƬ

IMAGE img_selector_role_tip_text;//��ɫѡ����ʾ�ı�ͼƬ
IMAGE img_selector_role_tip_bg;//��ɫѡ����ʾ����

IMAGE img_1P_selector_btn_idle_left;//1Pѡ��ťĬ��״̬��ͼƬ
IMAGE img_1P_selector_btn_idle_right;//1Pѡ��ťĬ��״̬��ͼƬ
IMAGE img_1P_selector_btn_down_left;//1Pѡ��ť����״̬��ͼƬ
IMAGE img_1P_selector_btn_down_right;//1Pѡ��ť����״̬��ͼƬ

IMAGE img_2P_selector_btn_idle_left;//2Pѡ��ťĬ��״̬��ͼƬ
IMAGE img_2P_selector_btn_idle_right;//2Pѡ��ťĬ��״̬��ͼƬ
IMAGE img_2P_selector_btn_down_left;//2Pѡ��ť����״̬��ͼƬ
IMAGE img_2P_selector_btn_down_right;//2Pѡ��ť����״̬��ͼƬ

IMAGE img_peashooter_selector_bg_left;//��ɫѡ����泯������㶹���ֱ���ͼƬ
IMAGE img_peashooter_selector_bg_right;//��ɫѡ����泯���ҵ��㶹���ֱ���ͼƬ
IMAGE img_sunflower_selector_bg_left;//��ɫѡ����泯��������տ�����ͼƬ
IMAGE img_sunflower_selector_bg_right;//��ɫѡ����泯���ҵ����տ�����ͼƬ

IMAGE img_sky;//��ձ���ͼƬ
IMAGE img_hills;//ɽ�𱳾�ͼƬ
IMAGE img_platform_large;//����ƽ̨ͼƬ
IMAGE img_platform_small;//С��ƽ̨ͼƬ

IMAGE img_1P_cursor;//1P���ͼƬ
IMAGE img_2P_cursor;//2P���ͼƬ

IMAGE img_pea;//�㶹ͼƬ
IMAGE img_1P_winner;//1Pʤ��ͼƬ
IMAGE img_2P_winner;//2Pʤ��ͼƬ
IMAGE img_winner_bar;//��ʤ����ı�����

IMAGE img_avatar_peashooter;//�㶹����ͷ��ͼƬ
IMAGE img_avatar_sunflower;//���տ�ͷ��ͼƬ
#pragma endregion

#pragma region ͼ����Դ
Atlas atlas_peashooter_idle_left;//�㶹�����󶯻�ͼ��
Atlas atlas_peashooter_idle_right;//�㶹�����Ҷ���ͼ��
Atlas atlas_peashooter_run_left;//�㶹�������ܶ�����ͼ��
Atlas atlas_peashooter_run_right;//�㶹�������ܶ�����ͼ��
Atlas atlas_peashooter_attack_ex_left;//�㶹�����󹥻�����ͼ��
Atlas atlas_peashooter_attack_ex_right;//�㶹�����ҹ�������ͼ��
Atlas atlas_peashooter_die_left;//�㶹��������������ͼ��
Atlas atlas_peashooter_die_right;//�㶹��������������ͼ��

Atlas atlas_sunflower_idle_left;//���տ��󶯻�ͼ��
Atlas atlas_sunflower_idle_right;//���տ��Ҷ���ͼ��
Atlas atlas_sunflower_run_left;//���տ����ܶ�����ͼ��
Atlas atlas_sunflower_run_right;//���տ����ܶ�����ͼ��
Atlas atlas_sunflower_attack_ex_left;//���տ��󹥻�����ͼ��
Atlas atlas_sunflower_attack_ex_right;//���տ��ҹ�������ͼ��
Atlas atlas_sunflower_die_left;//���տ�����������ͼ��
Atlas atlas_sunflower_die_right;//���տ�����������ͼ��

Atlas atlas_pea_break;//�㶹��Ƭ����ͼ��
Atlas atlas_sun;//̫������ͼ��
Atlas atlas_sun_explode;//̫����ը����ͼ��
Atlas atlas_sun_ex;//����̫������ͼ��
Atlas atlas_sun_ex_explode;//����̫����ը����ͼ��
Atlas atlas_sun_text;//���ı�����ͼ��

Atlas atlas_run_effect;//�ܶ���Ч����ͼ��
Atlas atlas_jump_effect;//��Ծ��Ч����ͼ��
Atlas atlas_land_effect;//�����Ч����ͼ��
#pragma endregion
#endif //  _MAIN_H_
