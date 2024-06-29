#ifndef _UTIL_H_
#define _UTIL_H_
#include "Camera.h"

#pragma comment(lib, "MSIMG32.LIB")

inline void flip_image(IMAGE* src, IMAGE* dst)//翻转图片
{
    int w = src->getwidth(), h = src->getheight();//获取图片宽高
    Resize(dst, w, h);//将目标图像dst大小调整为与源图像相同的宽高
    //DWORD 通常是一个 32 位的无符号整数类型，用于存储图像的像素数据
    DWORD* src_buffer = GetImageBuffer(src);//获取源图像的缓冲区
    DWORD* dst_buffer = GetImageBuffer(dst);//获取目标图像的缓冲区
    for (int y = 0; y < h; ++y)//嵌套循环遍历每一个像素
        for (int x = 0; x < w; ++x)
        {
            int idx_src = y * w + x;//计算源图像的当前索引
            int idx_dst = y * w + (w - x - 1);//计算目标图像的当前索引,w - x - 1是将y坐标翻转到图像另一侧
            dst_buffer[idx_dst] = src_buffer[idx_src];//将源图像的像素数据复制到目标图像的对应位置
        }
}
//适用图片裁剪
inline void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y)
{
    int w = width > 0 ? width : img->getwidth();
    int h = height > 0 ? height : img->getheight();
    AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
        GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
inline void putimage_alpha(const Camera& camera, int dst_x, int dst_y, IMAGE* img)
{
    int w = img->getwidth();
    int h = img->getheight();
    const Vector2& pos = camera.GetPosition();
    AlphaBlend(GetImageHDC(GetWorkingImage()), (int)(dst_x - pos.x), (int)(dst_y - pos.y), w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img)//绘制带有透明度的图像的函数
{
    int w = img->getwidth();
    int h = img->getheight();

    AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
//将图片处理为纯白色剪影效果
inline void sketch_image(IMAGE* src, IMAGE* dst)
{
    int w = src->getwidth(), h = src->getheight();
    Resize(dst, w, h);
    DWORD* src_buffer = GetImageBuffer(src);
    DWORD* dst_buffer = GetImageBuffer(dst);
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
        {
            int idx = y * w + x;
            dst_buffer[idx] = BGR(RGB(255, 255, 255)) | (src_buffer[idx] & 0xFF000000);
        }
}
//使用摄像机位置进行绘图
inline void Line(const Camera& camera, int x1, int y1, int x2, int y2)
{
    const Vector2& pos = camera.GetPosition();
    line((int)(x1 - pos.x), (int)(y1 - pos.y), (int)(x2 - pos.x), (int)(y2 - pos.y));
}
inline void SetVolume(const char* name, const int volume)//设置音量,值范围0-1000也就是0-100%
{
    TCHAR command[256];
    TCHAR tname[256];
    size_t convertedChars = 0;//转换后的字符数
    mbstowcs_s(&convertedChars, tname, name, _TRUNCATE);//将字符串转换为宽字符
    _stprintf_s(command, _T("setaudio %s volume to %d"), tname, volume);
    mciSendString(command, NULL, 0, NULL);
}
#endif