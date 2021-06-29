#ifndef IMGCVTCOLOR_H
#define IMGCVTCOLOR_H

#include "algorithmbaseNaitive.h"   // AlgorithmBaseNaitive

class WMSVISION_EXPORT  ImgCvtColor : public AlgorithmBaseNaitive
{
public:
    ImgCvtColor(cv::Mat src,  cv::ColorConversionCodes mode )  ;
    cv::Mat  m_out;
    void  proc();

private:
    cv::Mat  _m_src ;
    cv::ColorConversionCodes _mode ;
};

#endif // IMGCVTCOLOR_H
