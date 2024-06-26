#ifndef _UTIL_H_
#define _UTIL_H_

#include <graphics.h>

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
            int idx_dst = (h - 1 - y) * w + x;//计算目标图像的当前索引,h-1-y是将y坐标翻转到图像另一侧
            dst_buffer[idx_dst] = src_buffer[idx_src];//将源图像的像素数据复制到目标图像的对应位置
        }
}

#endif