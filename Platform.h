#ifndef _PLATFORM_H_
#define _PLATFORM_H_
#include <graphics.h>
#include "util.h"
#include "Camera.h"
extern bool ISDEBUGING;

class Platform
{
public:
    Platform() = default;
    ~Platform() = default;
    void on_draw(const Camera& camera) const
    {
        putimage_alpha(camera, draw_pos.x, draw_pos.y, img);
    }
    void debug_draw(const Camera& camera) const
    {
        setlinecolor(RGB(255, 0, 0));
        Line(camera, (int)collisionShape.left, (int)collisionShape.y, (int)collisionShape.right, (int)collisionShape.y);
        settextcolor(RGB(255, 0, 0));
        settextstyle(16, 0, _T("IPix"));
        outtextxy(3, 3, _T("已开启开发者模式,Q键退出开发者模式"));
    }

public:
    struct CollisionShape
    {
        float y;
        float left, right;
    };
    CollisionShape collisionShape;
    IMAGE* img = nullptr;
    POINT draw_pos = { 0 };

private:
};
#endif // !
