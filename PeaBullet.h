#ifndef _PEABULLET_H_
#define _PEABULLET_H_
#include "Bullet.h"
#include <graphics.h>

extern IMAGE img_pea;//Íã¶¹Í¼Æ¬
extern Atlas atlas_pea_break;//Íã¶¹ËéÆ¬¶¯»­Í¼¼¯

class PeaBullet :public Bullet
{
public:
    PeaBullet()
    {
        Bullet::Bullet();
        size.x = 64, size.y = 64;
        damage = 10;

        animation_break.set_atlas(&atlas_pea_break);
        animation_break.set_interval(100);
        animation_break.set_loop(false);
        animation_break.set_callback( //Íã¶¹×Óµ¯ÆÆËé¶¯»­²¥·ÅÍê±Ï»Øµ÷
            [&]() {can_remove = true; }
        );
    }
    ~PeaBullet() = default;
    void on_collide() override
    {
        Bullet::on_collide();
        switch (rand() % 3)
        {
            case 0:
                mciSendString(_T("play pea_break_1 from 0"), NULL, 0, NULL);
                break;
            case 1:
                mciSendString(_T("play pea_break_2 from 0"), NULL, 0, NULL);
                break;
            case 2:
                mciSendString(_T("play pea_break_3 from 0"), NULL, 0, NULL);
                break;
        }
    }
    void on_update(int dt) override
    {
        timer.Update(dt);
        position += velocity * (float)dt;

        if (!valid) animation_break.on_update(dt);//²¥·ÅÍã¶¹×Óµ¯ÆÆËé¶¯»­
    }
    void on_draw(const Camera& camera) const override
    {
        if (valid)
            putimage_alpha((int)position.x, (int)position.y, &img_pea);
        else
            animation_break.on_draw(camera, (int)position.x, (int)position.y);
    }
private:
    Animation animation_break;//Íã¶¹×Óµ¯ÆÆËé¶¯»­
};
#endif