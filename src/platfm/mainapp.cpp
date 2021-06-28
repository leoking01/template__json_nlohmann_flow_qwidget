#include "mainapp.h"

#pragma execution_character_set("utf-8")


MainApp *MainApp::instance = NULL;

MainApp::MainApp() {
  flowData = new  std::map<int, ToolBase *> ();
}

const int nums_of_tools = 3;
std::string toolNameset[3]
        {
                "ToolSource",    //    源文件
                "ToolSaveFile",  //保存文件
                "ToolBlur"    //滤波工具
        };



//void to_json(  nlohmann:: json& jt ,ToolSource  & p ) {
//    std::cout<< "ToolSource exe to_json()."<<std::endl;
////        ToolSource   p = *this;
//jt =     nlohmann::json{
//    {"actualName", p.actualName},
//    {"className", p.className},
//    {"toolName", p.toolName},
//    {"sole_name", p.sole_name},
//    {"order", p.order},
//    {"id", p.id},

//    {"filePath", p.filePath},
//    {"type", p.type}
//};
//     std::cout <<"jt   = "<<  jt << std::endl;
//    std::cout<< "ToolSource exe to_json()  finish."<<std::endl;
////        jt = *pj ;
//}


std::vector<std::string> split_std_string(const std::string &str, const std::string &delim) {
    std::vector<std::string> res;
    if ("" == str) return res;
    //先将要切割的字符串从string类型转换为char*类型
    char *strs = new char[str.length() + 1]; //不要忘了
    strcpy(strs, str.c_str());

    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p) {
        std::string s = p; //分割得到的字符串转换为string类型
        res.push_back(s); //存入结果数组
        p = strtok(NULL, d);
    }
    return res;
}


//判断字符串是否包含某字符串
//@params:str:大的字符串
//@params:contains_str:所包含的字符串
//@return: false:未包含 true：包含
bool IsContainsStr(std::string str, std::string contains_str) {
    std::string::size_type idx = str.find(contains_str);
    if (idx != std::string::npos) {
        return true;
    } else {
        return false;
    }
}


std::vector<std::string> split_std_string(const std::string &s, std::vector<std::string> &res, char delim) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        res.push_back(item);
    }
    return res;
}

int actualName_to_idx__from_flow_list(std::string actualName) {
    int idx = -1;
    std::cout << "actualName_to_toolName = " << actualName << std::endl;
    // std::spli
    std::vector<std::string> res;
    split_std_string(actualName, res, ',');
    if (res.size() >= 2) {
        //          std:: res[0]
        idx = std::stoi(res[1]);
    } else
        idx = -1;
    return idx;
}

//---------------------------------------------------------------




int soleName_to_className(std::string soleName, std::string &className) {
    int idx = -1;
    std::cout << "soleName = " << soleName << std::endl;
    // std::spli
    std::vector<std::string> res;
    split_std_string(soleName, res, ',');
    if (res.size() >= 3) {
        //          std:: res[0]
        idx = std::stoi(res[0]);
        className = res[2];
    } else {
        idx = -1;
        className = "";
    }
    return idx;
}

