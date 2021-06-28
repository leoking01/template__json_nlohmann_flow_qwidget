#include "commonfunc.h"

#pragma execution_character_set("utf-8")


CommonFunc::CommonFunc() {

}

#include <QtWidgets/QTextBrowser>

void printLogToTextBox_q(QString qWds, QTextBrowser *pt) {
#define DEBUG_PRINT_LOG_LK
#ifdef  DEBUG_PRINT_LOG_LK
    if (!pt) return;
    std::string time = getDatetimeStr();
    QTextCodec *code = QTextCodec::codecForName("utf8");//解决中文路径问题   //   gb2322
    std::string stdWds = code->fromUnicode(qWds).data();
    stdWds = time + ":" + stdWds;
    pt->append(QString::fromUtf8(stdWds.c_str()));
    std::cout << qWds.toStdString() << std::endl;
#endif
}


void print_cvMat_info(cv::Mat img, QTextBrowser *pt) {
    //    std::stringstream
    std::cout << "_______________img info:____________________" << std::endl;
    std::cout << "img.isContinuous() = " << img.isContinuous() << std::endl;
    std::cout << "img.isSubmatrix() = " << img.isSubmatrix() << std::endl;
    std::cout << "img.elemSize() = " << img.elemSize() << std::endl;
    std::cout << "img.elemSize1() = " << img.elemSize1() << std::endl;
    std::cout << "img.type() = " << img.type() << std::endl;
    std::cout << "img.depth() = " << img.depth() << std::endl;
    std::cout << "img.channels() = " << img.channels() << std::endl;
    std::cout << "img.step1() = " << img.step1() << std::endl;
    std::cout << "img.empty() = " << img.empty() << std::endl;
    std::cout << "img.total() = " << img.total() << std::endl;
    std::cout << "img.flags = " << img.flags << std::endl;
    std::cout << "img.dims = " << img.dims << std::endl;
    std::cout << "img.rows = " << img.rows << std::endl;
    std::cout << "img.cols = " << img.cols << std::endl;

    double min;
    double max;
    cv::minMaxLoc(img, &min, &max);
    std::cout << "min = " << min << std::endl;
    std::cout << "max = " << max << std::endl;

    std::cout << "_______________img info end____________________" << std::endl;
}

//---------------------------格式转换： opencv mat proc ----------------------------------------
/*
 * \brief: 将单通道的16位灰度图或者深度图转化为8位灰度图进行显示. 实际是从 ushort  转换到 uchar
 * \input: cv::Mat &src,  输入图像
 * \output:   cv::Mat  &out， 输出图像
 */
void cvMat_16bit_to_8bit(cv::Mat &src, cv::Mat &out) {
    if (src.elemSize1() != 2 || src.channels() != 1)
        return;
    cv::Mat ff = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    for (int k = 0; k < src.rows; k++) {
        for (int kk = 0; kk < src.cols; kk++) {
            int n = src.at<ushort>(k, kk);
            ff.at<uchar>(k, kk) = n;
        }
    }
    out = ff;
}

void cvMat_32bit_to_8bit(cv::Mat &src, cv::Mat &out) {
    if (src.elemSize1() != 4 || src.channels() != 1)
        return;
    cv::Mat ff = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    for (int k = 0; k < src.rows; k++) {
        for (int kk = 0; kk < src.cols; kk++) {
            int n = src.at<float>(k, kk);
            ff.at<uchar>(k, kk) = n;
        }
    }
    out = ff;
}


//-------------------------显示函数-： opencv   -----------------------------------
// 缩放图像
int getMatProper(cv::Mat &imageProper) {
    //    return  0;
    try {
        QString imgInfo = QString("getMatProper--imageProper----cols,rows = ") +
                          QString::number(imageProper.cols) + QString(",") + QString::number(imageProper.rows);
        //        ui->textEdit->append( QString ("getMatProper----imgInfo--init---") + imgInfo  );

        cv::Mat srcImage = imageProper;//.clone();
        //    ui->textEdit->setText(  QString("open image file:  ").append(   fileName.toLatin1().data()  )   );
        cv::Mat tmp;
        //    cv::resize( srcImage, tmp, Size(  rc.right()-rc.left() ,rc.bottom()-rc.top()   ) );

        int wid, hei;
        double lenTar = 400.0;
        double rateWid = lenTar / (double) imageProper.cols;
        double rateHei = 300 / (double) imageProper.rows;
        bool a = 1 > 3 ? false : true;
        double rateTar = rateWid > rateHei ? rateHei : rateWid;
        //    double  rateTar = min( rateWid, rateHei   );
        wid = (int) (imageProper.cols * rateTar);
        hei = (int) (imageProper.rows * rateTar);

        wid = (int) ((int) (wid / 4)) * 4;
        hei = (int) ((int) (hei / 4)) * 4;

        cv::resize(srcImage, tmp, cv::Size((int) wid, (int) hei));

        imgInfo = QString("getMatProper--finlImageWidHei----wid , hei = ") +
                  QString::number(wid) + QString(",") + QString::number(hei);
        //        ui->textEdit->append( QString ("getMatProper----imgInfo--after---") + imgInfo  );


        tmp.copyTo(imageProper);
    }
    catch (std::exception ex) {
        //        ui->textEdit->append( QString ("getMatProper--发生异常--")   );
    }

    return 0;
}

#include  <QLabel>
#include  <QImage>
#include  <QPainter>
#include  <QLabel>

//-------------------------------------------------------------
void displayResult(cv::Mat matt, QLabel *label_2) {   //show the resultImage in result area;
    cv::Mat mat = matt.clone();
    getMatProper(mat);
    if (0) {
        cv::Mat tmp;
        cv::cvtColor(mat, tmp, cv::COLOR_GRAY2BGR);
        tmp.copyTo(mat);
    }

    if (mat.elemSize1() == 2 && mat.channels() == 1) {
        cv::Mat tmp;
        cvMat_16bit_to_8bit(mat, tmp);
        tmp.copyTo(mat);
    }

    if (mat.elemSize1() == 4 && mat.channels() == 1) {
        cv::Mat tmp;
        cvMat_32bit_to_8bit(mat, tmp);
        tmp.copyTo(mat);
    }

    if (mat.channels() == 4)    // RGB image
    {
        cv::Mat tmp;
        cv::cvtColor(mat, tmp, cv::COLOR_RGBA2BGR);
        tmp.copyTo(mat);
    }
    cv::Mat rgb;
    QImage img;
    if (mat.channels() == 3)    // RGB image
    {
        cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
        img = QImage((const uchar *) (rgb.data),  //(const unsigned char*)
                     rgb.cols, rgb.rows,
                     QImage::Format_RGB888);
    } else if (mat.channels() == 1)  // gray image
    {
        //        img = QImage((const uchar*)(mat.data),
        //                     mat.cols,mat.rows,
        //                     QImage::Format_Indexed8);//Format_Grayscale8
        img = QImage((const uchar *) (mat.data),
                     mat.cols, mat.rows,
                     QImage::Format_Grayscale8);//
    } else
        return;

    //    log4cplus::tcout <<  " mat.size() = " << mat.size() <<    std::endl;

    QPainter painter(&img);
    QImage resultImg = img.scaled(label_2->size(),
                                  Qt::KeepAspectRatio,
                                  Qt::SmoothTransformation);
    label_2->setPixmap(QPixmap::fromImage(resultImg));
    label_2->show();
    return;
}


//-----------------------------------------------
static std::time_t getTimeStamp() {
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now());
    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();

    //    timestamp.

    return timestamp;
}

static std::tm *gettm(uint64_t timestamp) {
    uint64_t milli = timestamp;
    milli += (uint64_t) 8 * 60 * 60 * 1000;//add to beijing time zone.
    auto mTime = std::chrono::milliseconds(milli);
    auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(mTime);
    auto tt = std::chrono::system_clock::to_time_t(tp);
    std::tm *now = std::gmtime(&tt);
    return now;
}

static std::string getTimeStr() {
    time_t timep;
    timep = getTimeStamp();
    struct tm *info;
    info = gettm(timep);

    char tmp[27] = {0};
    sprintf(tmp, "%04d-%02d-%02d %02d:%02d:%02d.%06ld", info->tm_year + 1900, info->tm_mon + 1, info->tm_mday,
            info->tm_hour, info->tm_min, info->tm_sec, timep % 1000000);
    return tmp;
}

std::string getDatetimeStr() {
    return std::string(getTimeStr());
    //       return  getTimeCurMicroSecond();

    // 获取本地时间
    time_t ticks = time(NULL);

    tm local_time;

//    localtime (&local_time, &ticks);

    // 格式化日期时间
    char date_time[20];

    if (0 == strftime(date_time, sizeof(date_time), "%F %T", &local_time)) {
        printf("File:%s Line:%ld 获取日期时间失败\n", __FILE__, __LINE__);
        return "--failureToGetDate--";//-1;
    } else {
        printf("%s\n", date_time);
    }

    std::cout << std::endl;
    return std::string(date_time);
}


std::string getDatetimeStr_forID() {
    return std::string(getTimeStr());
    //       return  getTimeCurMicroSecond();
    // 获取本地时间
    time_t ticks = time(NULL);
    tm local_time;
//    localtime(&local_time, &ticks);

    // 格式化日期时间
    char date_time[20];
    int rest = strftime(date_time, sizeof(date_time), "%F_%T", &local_time);
    if (0 == rest) {
        printf("File:%s Line:%ld 获取日期时间失败\n", __FILE__, __LINE__);
        return "--failureToGetDate--";//-1;
    } else {
        printf("%s\n", date_time);
    }

    std::cout << std::endl;
    return std::string(date_time);
}


//-------------------------------------------------------------------------------------


void load_json(nlohmann::json &jt, std::string file) {

    //    std::string  file = "D:\\AwsOneDriver\\note_light\\light_json_nlohmann_qt\\src/test.json";
    std::cout << "load from file: " << file << std::endl;
    // read a JSON file
    std::ifstream i(file);
    if (!i.is_open()) return;
    try {
        nlohmann::json j;
        i >> j;
//        return ;
        jt = j;
        i.close();
        if (j.size() <= 0) {
            std::cout << "data j is null.  " << std::endl;
            return;
        }
        std::cout << "j.dump(4) = " << j.dump(4) << std::endl;
    } catch (std::exception ex) {
        std::cout << "ex.what() = " << ex.what() << std::endl;
        jt.clear();
    }

}


void save_json(nlohmann::json j22, std::string file) {
    // write prettified JSON to another file
    //    std::string  file = "D:\\AwsOneDriver\\note_light\\light_json_nlohmann_qt\\src/testOut.json";
    //    json  j22;
    std::ofstream o(file);
    o << std::setw(4) << j22 << std::endl;
    o.close();

    std::cout << "save to file: " << file << std::endl;
}





