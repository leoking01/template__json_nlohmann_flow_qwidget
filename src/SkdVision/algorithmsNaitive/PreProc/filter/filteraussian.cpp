#include "filteraussian.h"

//const  std:/:string  FilterAussian::name   = "FilterAussian";


#if   0     //  #endif     #if   0
FilterAussian( MODE_CV_HCON_TYPE   mode_t ):EnkAlgorithmBase(mode_t )
{
   mode_cv_or_hcon = mode_t ;
   class_name = "FilterAussian";
}

static const  std::string  name  ;//= "FilterAussian";

virtual double loadData_cv()
{
   cv::Mat  in;
   in =  cv::imread("/home/alex/images/tongzhou_a/2.bmp");
   dataIn.imgs.clear();
   dataIn.imgs.push_back( in );

   dataIn.cnfgs.push_back( cv::COLOR_BGR2GRAY  );
   return  0 ;
}
virtual double  run_cv(){
   cv::Mat  dst;
   cv::GaussianBlur(dataIn.imgs[0],dst,  cv::Size(3,3), 0.3   );
   dataOut.imgs.clear();
   dataOut.imgs.push_back(  dst );

   return   0 ;
}
virtual double   exportData_cv()
{
       if( dataOut.imgs.size()>0 )
                 if(dataOut.imgs[0].data )
     cv::imwrite(  (this->name+"."+ std::to_string(mode_cv_or_hcon)+ ".out.png").c_str(), dataOut.imgs[0] );
       return   0 ;
}




virtual double  loadData_hcon()    {
   data_in_hcon.Image.ReadImage( "/home/alex/images/tongzhou_a/2.bmp"  );
   return  0 ;
}

virtual double  run_hcon(){
   try {
       HImage out ;//= data_in_hcon. Image.Rgb1ToGray() ;
       if( 0 ) out =  data_in_hcon.Image.DerivateGauss(3,  "xxy");
       if( 0 ) data_out_hcon.Image = data_in_hcon.Image.LaplaceOfGauss(0.3 );
       if( 0 )  LaplaceOfGauss(data_in_hcon. Image, &out, 3  );
       //        data_in_hcon.ImageOutput = out;
       if( 0 ) HImage out1 = data_in_hcon.Image.ConvertImageType("int1")  ;

       GaussImage( data_in_hcon. Image,  &data_out_hcon.Image, 3 ) ;

// data_in_hcon.ImageOutput.WriteImage("png" ,255, "FilterGaussianHcon.output.png") ;
   }  catch (HalconCpp::HException  ex) {
       std::cout<< "run, ex.ErrorCode() : "<<ex.ErrorCode()   <<std::endl;
   }
   return   0;
}

virtual double exportData_hcon()    {
   try {
       if(data_out_hcon.Image.IsInitialized())
           data_out_hcon.Image.WriteImage("png" ,255, (this->name+"."+ std::to_string(mode_cv_or_hcon)+ ".out.png").c_str()) ;
   }catch (HalconCpp::HException  ex) {
       std::cout<< "exportData, ex.ErrorCode() : "<<ex.ErrorCode()   <<std::endl;
   }
}
#endif   //  #if   0
