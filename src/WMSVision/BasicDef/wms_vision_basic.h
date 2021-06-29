#ifndef wms_VISION_BASIC_H
#define wms_VISION_BASIC_H
#include <stdio.h>
#include <stdlib.h>
//----------------------------------------------------

// 图像
typedef  struct  Stru_Image_core{
    unsigned char * data;
    int widght;
    int height;
    int channels;
}wms_Vision_Image_core;






#endif // wms_VISION_BASIC_H
