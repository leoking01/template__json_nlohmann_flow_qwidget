#include "fitcircle.h"

//fitCircle::fitCircle()
//{

//}
//const  std::string  fitCircle::name   = "fitCircle";
//fitCircle::fitCircle(MODE_CV_HCON_TYPE   mode_t ):EnkAlgorithmBase(mode_t )
//{
//    mode_cv_or_hcon = mode_t ;
//    class_name = "FitLine";
//}


#ifdef   USING_HALCON_DEFINED_LK

#ifndef __APPLE__
#  include "HalconCpp.h"
#  include "HDevThread.h"
#else
#  ifndef HC_LARGE_IMAGES
#    include <HALCONCpp/HalconCpp.h>
#    include <HALCONCpp/HDevThread.h>
#    include <HALCON/HpThread.h>
#  else
#    include <HALCONCppxl/HalconCpp.h>
#    include <HALCONCppxl/HDevThread.h>
#    include <HALCONxl/HpThread.h>
#  endif
#  include <stdio.h>
#  include <CoreFoundation/CFRunLoop.h>
#endif



using namespace HalconCpp;
#endif

//#ifndef NO_EXPORT_MAIN
// Main procedure
void action_fitCircle()
{
#ifdef   USING_HALCON_DEFINED_LK
    // Local iconic variables
    HObject  ho_Image, ho_GrayImage, ho_Region, ho_Contour;
    HObject  ho_ContCircle;

    // Local control variables
    HTuple  hv_Width, hv_Height, hv_WindowHandle;
    HTuple  hv_Row, hv_Column, hv_Radius, hv_StartPhi, hv_EndPhi;
    HTuple  hv_PointOrder;

    //
    //   Robust circle fitting
    //
    ReadImage(&ho_Image, "earth");
    Rgb1ToGray(ho_Image, &ho_GrayImage);
    if (HDevWindowStack::IsOpen())
        CloseWindow(HDevWindowStack::Pop());
    GetImageSize(ho_Image, &hv_Width, &hv_Height);
    SetWindowAttr("background_color","black");
    OpenWindow(0,0,hv_Width*2,hv_Height*2,0,"visible","",&hv_WindowHandle);
    HDevWindowStack::Push(hv_WindowHandle);
    Threshold(ho_GrayImage, &ho_Region, 60, 255);
    ClosingCircle(ho_Region, &ho_Region, 10.5);
    GenContourRegionXld(ho_Region, &ho_Contour, "border");
    if (HDevWindowStack::IsOpen())
        DispObj(ho_Image, HDevWindowStack::GetActive());
    //Algebraic distance measure
    FitCircleContourXld(ho_Contour, "atukey", -1, 2, 0, 10, 1, &hv_Row, &hv_Column,
 &hv_Radius, &hv_StartPhi, &hv_EndPhi, &hv_PointOrder);
    if (HDevWindowStack::IsOpen())
        SetColor(HDevWindowStack::GetActive(),"magenta");
    GenCircleContourXld(&ho_ContCircle, hv_Row, hv_Column, hv_Radius, 0, 4*(HTuple(0).TupleAcos()),
 "positive", 1);
    //Geometric distance measure
    FitCircleContourXld(ho_Contour, "geotukey", -1, 2, 0, 10, 1, &hv_Row, &hv_Column,
 &hv_Radius, &hv_StartPhi, &hv_EndPhi, &hv_PointOrder);
    if (HDevWindowStack::IsOpen())
        SetColor(HDevWindowStack::GetActive(),"cyan");
    GenCircleContourXld(&ho_ContCircle, hv_Row, hv_Column, hv_Radius, 0, 4*(HTuple(0).TupleAcos()),
 "positive", 1);
    #endif
}

 #if  0


fitCircle(MODE_CV_HCON_TYPE   mode_t ) ;

static const  std::string  name  ;//= "FitLine";

virtual double  loadData_cv()    {
    cv::Mat  in;
    in = cv::imread("/home/alex/images/tongzhou_a/2.bmp");
    dataIn.imgs.push_back( in );

    dataIn.cnfgs.push_back( cv::COLOR_BGR2GRAY  );
    return  0 ;
}
virtual double  run_cv(){

    //         cv::fitLine()
    //创建一个用于绘制图像的空白图
    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);

    //输入拟合点
    std::vector<cv::Point> points;
    points.push_back(cv::Point(48, 58));
    points.push_back(cv::Point(105, 98));
    points.push_back(cv::Point(155, 160));
    points.push_back(cv::Point(212, 220));
    points.push_back(cv::Point(248, 260));
    points.push_back(cv::Point(320, 300));
    points.push_back(cv::Point(350, 360));
    points.push_back(cv::Point(412, 400));

    //将拟合点绘制到空白图上
    for (int i = 0; i < points.size(); i++)
    {
        cv::circle(image, points[i], 5, cv::Scalar(0, 0, 255), 2, 8, 0);
    }

    cv::Vec4f line_para;
    // cv::fitLine(points, line_para, cv::DIST_L2, 0, 1e-2, 1e-2);
    cv::RotatedRect rorect = cv::fitEllipse( points ) ;

    std::cout << "line_para = " << line_para << std::endl;

    //获取点斜式的点和斜率
    cv::Point point0;
    point0.x = line_para[2];
    point0.y = line_para[3];

    double k = line_para[1] / line_para[0];

    //计算直线的端点(y = k(x - x0) + y0)
    cv::Point point1, point2;
    point1.x = 0;
    point1.y = k * (0 - point0.x) + point0.y;
    point2.x = 640;
    point2.y = k * (640 - point0.x) + point0.y;

    cv::line(image, point1, point2, cv::Scalar(0, 255, 0), 2, 8, 0);

    cv::imshow("image", image);
    cv::waitKey(1);
    return   0 ;
}


virtual double   exportData_cv()    {
    if( dataIn.imgs.size()>0 )
        if(dataIn.imgs[0].data )
            cv::imwrite(  (this->name+"."+ std::to_string(mode_cv_or_hcon)+ ".out.png").c_str(),   dataIn.imgs[0] );
    return   0 ;
}


virtual double  loadData_hcon()    { return  0 ; }
virtual double  run_hcon()    {
    //         fit_line_contour_xld();
    //         FitLineContourXld(    ) ;
    //        FitCircleContourXld
    action_fitCircle() ;
    return  0 ; }
virtual double  exportData_hcon()    { data_out_hcon.Image.WriteImage("png" ,255, (this->name+"."+ std::to_string(mode_cv_or_hcon)+ ".out.png").c_str()) ; return  0 ; }



#if   0
private:
// 拟合代码，外部调用，我这里是传入首尾两点，起始可以传入任意位置的点来拟合，
// 传入不是首尾点的话，计算方式要做一点修改
bool FitLine_my(HTuple start, HTuple end, HTuple& phi)
{
    //公式AX + BY + C = 0
    double a = 0;
    double b = 0;
    double c = 0;
    a = end[0].D() - start[0].D();
    b = start[1].D() - end[1].D();
    c = end[1].D() * start[0].D() - start[1].D() * end[0].D();
    HTuple len = HTuple();
    DistancePp(start[0], start[1], end[0], end[1], &len);
    AngleLx(start[0], start[1], end[0], end[1], &phi);
    //x_len是x轴的直角边长度，看需求是用斜边len长，还是x_len长度，或者再求个y轴长度都行
    double x_len = cos(phi[0].D() * 180 / PI) * len[0].D();
    QList<double> rows, cols;
    rows.append(start[0].D());
    cols.append(start[1].D());
    double newX = 0;
    double newY = 0;
    //len[0].D() / 10.0，除10是点与点的像素间隔，你可以用5、20、17任意数字都行。
    //当然，别用负值，比较间隔没有负值  - -0
    for(int i = 2; i < static_cast<int>(len[0].D() / 10.0) - 2; i++)
    {
        newX = start[1].D() + (i * 10);
        newY = (-1 * a * newX - c) / b;
        rows.append(newY);
        cols.append(newX);
    }

    rows.append(end[0].D());
    cols.append(end[1].D());
    QPoint startPoint, endPoint;

    if(FitLineByTwoPoint(rows, cols, startPoint, endPoint))
    {
        AngleLx(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), &phi);
        //这里可以在形参那里多传入一个HObject引用来获取直线结果对象
        //HObject line;
        //GenRegionLine(&line, startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
        //DispObj(line, winID);
        return TRUE;
    }

    return FALSE;
}

// 拟合代码，被FitLine使用：参数类型是QList，是Qt的，可以改成HTuple或者标准类型。
bool FitLineByTwoPoint(QList<double> rows, QList<double> cols, QPoint& startPoint, QPoint& endPoint)
{
    try  {
        HTuple dst_rows = HTuple();
        HTuple dst_cols = HTuple();
        for (int i = 0; i < rows.length(); i++)  {
            dst_rows.Append(rows[i]);
            dst_cols.Append(cols[i]);
        }

        //SortPairs(rows, cols, &dst_rows, &dst_cols);
        HTuple rowBegin = HTuple(), colBegin = HTuple(), rowEnd = HTuple(), colEnd = HTuple(), nr = HTuple(), nc = HTuple(), dist = HTuple();
        HXLDCont lineXLD = HXLDCont(dst_rows, dst_cols);
        FitLineContourXld(lineXLD, "tukey", -1, 0, 5, 2, &rowBegin, &colBegin, &rowEnd, &colEnd, &nr, &nc, &dist); //tukey剔除算法为halcon推荐算法
        startPoint = QPoint(colBegin.D(), rowBegin.D());
        endPoint = QPoint(colEnd.D(), rowEnd.D());
        return true;
    }
    catch (HException* ex)  {
    }
    return false;
}


#endif
   #endif
