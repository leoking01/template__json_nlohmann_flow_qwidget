#include "findcontours.h"
//  const   std::string FindContours:: name   = "FindContours";
//FindContours::FindContours(MODE_CV_HCON_TYPE   mode_t ):EnkAlgorithmBase(mode_t )
//{
//mode_cv_or_hcon = mode_t ;
//class_name = "FindContours";
//}
#if   0     //  #endif     #if   0
FindContours(MODE_CV_HCON_TYPE   mode_t ) ;

static const  std::string  name  ;//= "ContourCanny";
virtual double  loadData_cv()    {
   cv::Mat  in;
   in = cv::imread("/home/alex/images/tongzhou_a/2.bmp");
   dataIn.imgs.push_back( in );

   dataIn.cnfgs.push_back( cv::COLOR_BGR2GRAY  );
   return  0 ;
}
virtual double  run_cv(){
//        cv::findContours(  dataIn.imgs[0],     )
   return   0 ;
}
virtual double   exportData_cv()    {
   if( dataIn.imgs.size()>0 )
       if(dataIn.imgs[0].data )
           cv::imwrite(  (this->name+"."+ std::to_string(mode_cv_or_hcon)+ ".out.png").c_str(),   dataIn.imgs[0] );
   return   0 ;
}
virtual double  loadData_hcon()    { return  0 ; }
virtual double  run_hcon()    { return  0 ; }
virtual double  exportData_hcon()    { data_out_hcon.Image.WriteImage("png" ,255, (this->name+"."+ std::to_string(mode_cv_or_hcon)+ ".out.png").c_str()) ; return  0 ; }
#endif   //  #if   0
