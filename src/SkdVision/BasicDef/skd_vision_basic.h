#ifndef SKD_VISION_BASIC_H
#define SKD_VISION_BASIC_H




// 图像
typedef  struct  Stru_Image{
    unsigned char * data;
    int widght;
    int height;
    int channels;
    int depth;
}skd_Vision_Image;


// 数组
typedef  struct  Stru_array_float{
    float * data;
    int nums;
}sdk_Vision_array_float;







#endif // SKD_VISION_BASIC_H
