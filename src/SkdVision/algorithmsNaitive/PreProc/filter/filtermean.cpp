#include "filtermean.h"
// const  std::string  FilterMean::name   = "FilterMean";
//FilterMean::FilterMean(MODE_CV_HCON_TYPE   mode_t ):EnkAlgorithmBase(mode_t )
//{
//mode_cv_or_hcon = mode_t ;
//class_name = "FilterMean";
//}
#if   0     //  #endif     #if   0
FilterMean(MODE_CV_HCON_TYPE   mode_t ) ;

static const  std::string  name  ;//= "FilterAussian";
virtual double  loadData_cv()    {
   cv::Mat  in;
   in = cv::imread("/home/alex/images/tongzhou_a/2.bmp");
   dataIn.imgs.push_back( in );

   dataIn.cnfgs.push_back( cv::COLOR_BGR2GRAY  );
   return  0 ;
}
virtual double  run_cv(){
   cv::Mat dst;
   cv::blur(   dataIn.imgs[0],dst  ,cv::Size(3,3 ) ) ;
   dataOut.imgs.clear();
   dataOut.imgs.push_back(  dst );
   return   0 ;
}
virtual double   exportData_cv()    {
   if( dataOut.imgs.size()>0 )
             if(dataOut.imgs[0].data )
 cv::imwrite(  (this->name+"."+ std::to_string(mode_cv_or_hcon)+ ".out.png").c_str(),  dataOut.imgs[0] );
   return   0 ;
}
virtual double  loadData_hcon()    {
   data_in_hcon.Image.ReadImage( "/home/alex/images/tongzhou_a/2.bmp"  );
   return  0 ; }
virtual double  run_hcon()    {
   MeanImage( data_in_hcon.Image, &data_out_hcon.Image,  3,3   );
   return  0 ; }
virtual double  exportData_hcon()    {
  data_out_hcon.Image.WriteImage("png" ,255, (this->name+"."+ std::to_string(mode_cv_or_hcon)+ ".out.png").c_str()) ;
   return  0 ; }
#endif  //   #if   0
