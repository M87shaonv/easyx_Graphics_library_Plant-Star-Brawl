#ifndef _ATLAS_H_
#define _ATLAS_H_
#include <vector>
#include <graphics.h>
class Atlas
{
public:
    Atlas() = default;
    ~Atlas() = default;

    void LoadFormFile(LPCTSTR path_template, int num)//加载图片
    {
        //先清空之前的图片,防止重复加载
        image_list.clear();
        image_list.resize(num);

        TCHAR path[MAX_PATH]; //存放图片路径的字符串,MAX_PATH是系统定义的最大路径长度,260个字符
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
    void AddImage(const IMAGE& img)//添加图片,和加载图片类似,但这在生成水平翻转的动画图集时用到
    {
        image_list.push_back(img);
    }

private:
    std::vector<IMAGE> image_list;//存放所有图片的vector
};
#endif // _ATLAS_H_