 #pragma  once

#include "SKDVISION_global.h"

#include <iostream>
#include <string>

#ifdef  USE_INTERFACE_CV_OR_CPP
#include <opencv2/opencv.hpp>

/*
 * \brief: read image.
 * \para: imgFile, input ,image file name.
 * \para: mode, input ,color mode
 *         0, grey
 *         1, color
 **/
SKDVISION_EXPORT
void  api_load_img(std::string imgFile, int mode,  cv::Mat & img );

#else
#include "skd_vision_basic_cpp.h"

SKDVISION_EXPORT
void  api_load_img(std::string imgFile, skd_vision:: skd_Image & img );

#endif




