#include "api_imgSource.h"

#include "loadimage.h"

void  api_load_img(  std::string imgFile, int mode,  cv::Mat & img   )
{
    img = cv::imread(  imgFile,   mode   );
}
