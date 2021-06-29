#include "imgcvtcolor.h"
//const  std::string  ImgCvtColor::name   = "ImgCvtColor";
//ImgCvtColor::ImgCvtColor(MODE_CV_HCON_TYPE   mode_t ):EnkAlgorithmBase(mode_t )
//{
//mode_cv_or_hcon = mode_t ;
//class_name = "ImgCvtColor";
//}

ImgCvtColor::
ImgCvtColor(cv::Mat  src,cv::ColorConversionCodes mode ):_m_src(src),_mode(mode)  { }


void ImgCvtColor:: proc()
{
// cv::ColorConversionCodes mode= cv::ColorConversionCodes:: COLOR_BGR2GRAY ;
    cv::cvtColor( _m_src, m_out,_mode);
}


#if   0     //  #endif     #if   0
    ImgCvtColor(MODE_CV_HCON_TYPE   mode_t ) ;

public:
    virtual double loadData_cv()
    {
        cv::Mat  in;
        in =  cv::imread("/home/alex/images/tongzhou_a/2.bmp");
        dataIn.imgs.push_back( in );

        dataIn.cnfgs.push_back( cv::COLOR_BGR2GRAY  );
        return  0 ;
    }
    virtual double  run_cv(){
        cv::Mat  out;
        if( dataIn.imgs.size()<= 0 || dataIn.cnfgs.size()<=0  )
        {
            std::cout<< "warning : dataIn.imgs.size()<= 0 || dataIn.cnfgs.size()<=0 "<< std::endl;
            return  0;
        }
        int mode  =  cv::COLOR_BGR2GRAY   ;

        mode =  dataIn.cnfgs[0];
        cv::cvtColor( dataIn.imgs[0], out, mode  );
        dataIn.imgs.clear();
        dataIn.imgs.push_back( out );
        return   0;
    }

    virtual double exportData_cv(){            if( dataIn.imgs.size()>0 )
            if(dataIn.imgs[0].data )
                cv::imwrite(  (this->name+"."+ std::to_string(mode_cv_or_hcon)+ ".out.png").c_str(),   dataIn.imgs[0] );
        return   0;
                                  }

private:
    virtual double  loadData_hcon()
    {
        data_in_hcon. Image.ReadImage(  "/home/alex/images/tongzhou_a/2.bmp"  );
        return  0 ;
    }

    virtual double  run_hcon(){
        HImage out = data_in_hcon. Image.Rgb1ToGray() ;
        data_out_hcon.Image = out;
        if( 0 )
            HImage out1 = data_in_hcon. Image.ConvertImageType("int1") ;
        return   0;
    }
    virtual double exportData_hcon()
    {
        //   cv::imwrite("ImgCvtColor.save.png",   dataIn.imgs[0] );
        //     data_in_hcon.ImageOutput .WriteImage("png" ,255, "ImgCvtColorHcon.output.png") ;
        data_out_hcon.Image.WriteImage("png" ,255, (this->name+"."+ std::to_string(mode_cv_or_hcon)+ ".out.png").c_str()) ;
        return  0 ;
    }
public:
    static const  std::string  name   ;
#endif   //  #if   0
