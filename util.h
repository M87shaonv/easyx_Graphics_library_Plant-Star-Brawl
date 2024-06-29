#ifndef _UTIL_H_
#define _UTIL_H_
#include "Camera.h"

#pragma comment(lib, "MSIMG32.LIB")

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
            int idx_dst = y * w + (w - x - 1);//����Ŀ��ͼ��ĵ�ǰ����,w - x - 1�ǽ�y���귭ת��ͼ����һ��
            dst_buffer[idx_dst] = src_buffer[idx_src];//��Դͼ����������ݸ��Ƶ�Ŀ��ͼ��Ķ�Ӧλ��
        }
}
//����ͼƬ�ü�
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
inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img)//���ƴ���͸���ȵ�ͼ��ĺ���
{
    int w = img->getwidth();
    int h = img->getheight();

    AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
//��ͼƬ����Ϊ����ɫ��ӰЧ��
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
//ʹ�������λ�ý��л�ͼ
inline void Line(const Camera& camera, int x1, int y1, int x2, int y2)
{
    const Vector2& pos = camera.GetPosition();
    line((int)(x1 - pos.x), (int)(y1 - pos.y), (int)(x2 - pos.x), (int)(y2 - pos.y));
}
inline void SetVolume(const char* name, const int volume)//��������,ֵ��Χ0-1000Ҳ����0-100%
{
    TCHAR command[256];
    TCHAR tname[256];
    size_t convertedChars = 0;//ת������ַ���
    mbstowcs_s(&convertedChars, tname, name, _TRUNCATE);//���ַ���ת��Ϊ���ַ�
    _stprintf_s(command, _T("setaudio %s volume to %d"), tname, volume);
    mciSendString(command, NULL, 0, NULL);
}
#endif