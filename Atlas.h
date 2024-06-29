#ifndef _ATLAS_H_
#define _ATLAS_H_
#include <vector>
#include <graphics.h>
class Atlas
{
public:
    Atlas() = default;
    ~Atlas() = default;

    void LoadFormFile(LPCTSTR path_template, int num)//����ͼƬ
    {
        //�����֮ǰ��ͼƬ,��ֹ�ظ�����
        image_list.clear();
        image_list.resize(num);

        TCHAR path[MAX_PATH]; //���ͼƬ·�����ַ���,MAX_PATH��ϵͳ��������·������,260���ַ�
        for (int i = 0; i < num; ++i)
        {
            _stprintf_s(path, path_template, i + 1);
            loadimage(&image_list[i], path);
        }
    }
    void clear()
    {
        image_list.clear();
    }
    int size()
    {
        return (int)image_list.size();
    }
    IMAGE* GetImage(const int index)
    {
        if (index < 0 || index >= image_list.size())
            return nullptr;

        return &image_list[index];
    }
    void AddImage(const IMAGE& img)//���ͼƬ,�ͼ���ͼƬ����,����������ˮƽ��ת�Ķ���ͼ��ʱ�õ�
    {
        image_list.push_back(img);
    }

private:
    std::vector<IMAGE> image_list;//�������ͼƬ��vector
};
#endif // _ATLAS_H_