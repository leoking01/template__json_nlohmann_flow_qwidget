#ifndef SKD_VISION_BASIC_CPP_H
#define SKD_VISION_BASIC_CPP_H


#include<iostream>
#include<vector>
#include<list>
#include<map>

namespace  skd_vision{
// 图像
typedef  struct  Stru_Image{
    unsigned char * data;
    int widght;
    int height;
    int channels;
    int depth;
}skd_Image;

}


#endif // SKD_VISION_BASIC_CPP_H
