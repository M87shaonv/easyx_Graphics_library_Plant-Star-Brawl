#ifndef _STATUS_BAR_H_
#define _STATUS_BAR_H_
#include <graphics.h>
#include "util.h"
class Status_Bar
{
public:
    Status_Bar() = default;
    ~Status_Bar() = default;
    void set_avatar(IMAGE* img)
    {
        img_avatar = img;
    }
    void set_hp(int hp)
    {
        this->hp = hp;
    }
    void set_mp(int mp)
    {
        this->mp = mp;
    }
    void set_pos(POINT pos)
    {
        this->pos = pos;
    }
    void set_pos(Vector2 pos)
    {
        this->pos.x = pos.x;
        this->pos.y = pos.y;
    }
    void set_pos(int x, int y)
    {
        pos.x = x;
        pos.y = y;
    }
    void on_draw()//UI组件不会依据摄像机位置渲染,所以这里不需要传入摄像机位置
    {
        putimage_alpha((int)pos.x, (int)pos.y, img_avatar);

        setfillcolor(RGB(5, 5, 5));
        solidroundrect(pos.x + 100, pos.y + 10, pos.x + 100 + width + 3 * 2, pos.y + 36, 8, 8);
        solidroundrect(pos.x + 100, pos.y + 45, pos.x + 100 + width + 3 * 2, pos.y + 71, 8, 8);
        setfillcolor(RGB(67, 47, 47));
        solidroundrect(pos.x + 100, pos.y + 10, pos.x + 100 + width + 3, pos.y + 33, 8, 8);
        solidroundrect(pos.x + 100, pos.y + 45, pos.x + 100 + width + 3, pos.y + 68, 8, 8);

        float hp_bar_width = width * max(0, hp) / 100.0f;//限制在0~100之间,如果 hp 小于 0，结果将是 0；否则，结果将是 hp
        float mp_bar_width = width * min(100, mp) / 100.0f;//限制在100~mp值之间 ,如果 mp 大于 100，结果将是 100；否则，结果将是 mp

        setfillcolor(RGB(197, 61, 67));
        solidroundrect(pos.x + 100, pos.y + 10, pos.x + 100 + (int)hp_bar_width + 3, pos.y + 33, 8, 8);
        setfillcolor(RGB(83, 131, 195));
        solidroundrect(pos.x + 100, pos.y + 45, pos.x + 100 + (int)mp_bar_width + 3, pos.y + 68, 8, 8);
    }
private:
    const int width = 275;
    int hp = 0;
    int mp = 0;
    POINT pos = { 0 };//位置
    IMAGE* img_avatar = nullptr;//头像
};
#endif