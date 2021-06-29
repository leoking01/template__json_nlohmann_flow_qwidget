 #pragma  once

#include "WMSVISION_global.h"

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
WMSVISION_EXPORT
void  api_load_img(std::string imgFile, int mode,  cv::Mat & img );

#else
#include "wms_vision_basic_cpp.h"

WMSVISION_EXPORT
void  api_load_img(std::string imgFile, wms_vision:: wms_Image & img );

#endif




