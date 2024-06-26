#ifndef _UTIL_H_
#define _UTIL_H_

#include <graphics.h>

inline void flip_image(IMAGE* src, IMAGE* dst)//��תͼƬ
{
    int w = src->getwidth(), h = src->getheight();//��ȡͼƬ���
    Resize(dst, w, h);//��Ŀ��ͼ��dst��С����Ϊ��Դͼ����ͬ�Ŀ��
    //DWORD ͨ����һ�� 32 λ���޷����������ͣ����ڴ洢ͼ�����������
    DWORD* src_buffer = GetImageBuffer(src);//��ȡԴͼ��Ļ�����
    DWORD* dst_buffer = GetImageBuffer(dst);//��ȡĿ��ͼ��Ļ�����
    for (int y = 0; y < h; ++y)//Ƕ��ѭ������ÿһ������
        for (int x = 0; x < w; ++x)
        {
            int idx_src = y * w + x;//����Դͼ��ĵ�ǰ����
            int idx_dst = (h - 1 - y) * w + x;//����Ŀ��ͼ��ĵ�ǰ����,h-1-y�ǽ�y���귭ת��ͼ����һ��
            dst_buffer[idx_dst] = src_buffer[idx_src];//��Դͼ����������ݸ��Ƶ�Ŀ��ͼ��Ķ�Ӧλ��
        }
}

#endif