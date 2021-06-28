#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <iostream>
#include <string>
#include <ctime>
// using namespace std;

#include <chrono>
//using namespace std;
//using namespace chrono;

#include <QTextCodec>
#include <iomanip>
#include <thread>
#include <mutex>
#include <iomanip>
#include <chrono>
#include <time.h>
#include <chrono>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>


#include "opencv2/opencv.hpp"



// for convenience
//using json = nlohmann::json;

#include <QLabel>
#include <QtWidgets/QTextBrowser>

class CommonFunc {
public:
    CommonFunc();
};


std::string getDatetimeStr();

std::string getDatetimeStr_forID();

void load_json(nlohmann::json &j, std::string file);

void save_json(nlohmann::json j22, std::string file);

void displayResult(cv::Mat matt, QLabel *label_2);

void print_cvMat_info(cv::Mat img, QTextBrowser *pt = NULL);

#endif // COMMONFUNC_H
