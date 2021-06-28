#ifndef MAINAPP_H
#define MAINAPP_H

#include <stdio.h>

#include <iostream>
#include <string>
#include <list>
#include <set>
#include <map>
#include <vector>

#include <algorithm>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>


extern const int nums_of_tools;//= 3;
extern std::string toolNameset[3];

class ToolBase {
public:
    virtual void run() = 0;

    virtual void to_json(nlohmann::json &j) = 0;

    virtual void from_json(const nlohmann::json &j) = 0;

    std::string actualName;//  昵称，可以任意取名，显示在流程栏中，一般有中文
    std::string className;  // 类名，  用于构造实例
    std::string toolName;   //  这个是显示在工具栏中的名称，一般是中文  这个名字是固定的

    //  该工具实例的唯一的名称,
    /*
         * order,日期时间 ， className,  toolName  这个名字一般含有中文
         **/
    std::string sole_name; // 这个名字作为该工具的唯一凭据  不含有中文
    int order; //  在流程中的序号，是执行的过程
    int id;   //  该工具实例的唯一的id ,
};


class ToolSource : public ToolBase {
public:
    ToolSource() {
        actualName = "xxxxx";
        className = "ToolSource";
        toolName = "ToolSource--image-pcd-soruce-";
        sole_name = "ToolSource--image-pcd-soruce-";
        order = -1;
        id = -1;

        filePath = "d:/tmp.png";  //pcd
        type = 0;//  0 file ;1 camera;2 stereo;3 dir;
    }

    virtual void run() {

    }

    std::string filePath;
    int type;//  文件，文件夹，摄像头，体感设备

    //
    void to_json(nlohmann::json &jt) {
        std::cout << "ToolSource exe to_json()." << std::endl;
        ToolSource p = *this;
        //        ,ToolSource  & p
        jt = nlohmann::json{
                {"actualName", p.actualName},
                {"className",  p.className},
                {"toolName",   p.toolName},
                {"sole_name",  p.sole_name},
                {"order",      p.order},
                {"id",         p.id},

                {"filePath",   p.filePath},
                {"type",       p.type}
        };
        std::cout << "jt   = " << jt << std::endl;
        std::cout << "ToolSource exe to_json()  finish." << std::endl;
        //        jt = *pj ;
    }

    //
    void to_json(nlohmann::json *pjt) {
        std::cout << "ToolSource exe to_json()." << std::endl;
        ToolSource p = *this;
        //        ,ToolSource  & p
        // pjt->at( )
        nlohmann::json *pj = new nlohmann::json{
                {"actualName", p.actualName},
                {"className",  p.className},
                {"toolName",   p.toolName},
                {"sole_name",  p.sole_name},
                {"order",      p.order},
                {"id",         p.id},

                {"filePath",   p.filePath},
                {"type",       p.type}
        };
        pjt = pj;
        std::cout << " * pjt   = " << *pjt << std::endl;
        std::cout << "ToolSource exe to_json()  finish." << std::endl;
        //  jt = *pj ;
    }


    void from_json(const nlohmann::json &j) {
        ToolSource p = *this;
        j.at("actualName").get_to(p.actualName);
        j.at("className").get_to(p.className);
        j.at("toolName").get_to(p.toolName);
        j.at("sole_name").get_to(p.sole_name);

        j.at("order").get_to(p.order);
        j.at("id").get_to(p.id);

        j.at("filePath").get_to(p.filePath);
        j.at("type").get_to(p.type);
    }
};


class ToolSaveFile : public ToolBase {
public:
    ToolSaveFile() {
        actualName = "null";
        className = "ToolSaveFile";
        toolName = "ToolSaveFile--image-pcd-save";
        sole_name = "ToolSaveFile--image-pcd-soruce-";

        order = -1;
        id = -1;

        saveFilePath = "d:/tmp.save.png";
        //        type = 0;//  0 file ;1 camera;2 stereo;3 dir;
    }

    virtual void run() {

    }

    void to_json(nlohmann::json &j) {
        std::cout << "ToolSaveFile exe to_json()." << std::endl;
        ToolSaveFile p = *this;
        j = nlohmann::json{
                {"actualName",   p.actualName},
                {"className",    p.className},
                {"toolName",     p.toolName},
                {"sole_name",    p.sole_name},

                {"order",        p.order},
                {"id",           p.id},

                {"saveFilePath", p.saveFilePath}
                //        {"type", p.type}
        };

    }

    void from_json(const nlohmann::json &j) {
        ToolSaveFile p = *this;
        j.at("actualName").get_to(p.actualName);
        j.at("className").get_to(p.className);
        j.at("toolName").get_to(p.toolName);
        j.at("sole_name").get_to(p.sole_name);

        j.at("order").get_to(p.order);
        j.at("id").get_to(p.id);

        j.at("saveFilePath").get_to(p.saveFilePath);
        //        j.at("type").get_to(p.type);
    }

    std::string saveFilePath;
    //    int type;//  文件，文件夹，摄像头，体感设备
    //public:
    //    std::string  actualName;//  昵称，可以任意取名，显示在流程栏中，一般有中文
    //    std::string  className;  // 类名，  用于构造实例
    //    std::string  toolName;   //  这个是显示在工具栏中的名称，一般是中文  这个名字是固定的

    //    //  该工具实例的唯一的名称,
    //    /*
    //     * order,日期时间 ， className,  toolName  这个名字一般含有中文
    //     **/
    //    std::string  sole_name ; // 这个名字作为该工具的唯一凭据  不含有中文
    //    int order; //  在流程中的序号，是执行的过程
    //    int  id;   //  该工具实例的唯一的id ,
};


class ToolBlur : public ToolBase {
public:
    ToolBlur() {
        actualName = "null";
        className = "ToolBlur";
        toolName = "ToolBlur--image-pcd-ToolBlur";
        order = -1;
        id = -1;

        blur_size = 3;

        m_img_input = cv::imread("G:\\dPanOld\\images/1.jpg");

        m_data.push_back(10);
        m_data.push_back(22);

        m_data_mat.push_back(m_data);

        m_pt.x = 2;
        m_pt.y = 22;
        m_pt.z = 23;

        dataA[0] = 42;
        dataA[1] = 22;
        dataA[2] = 12;
    }

    virtual void run() {

    }

    void to_json(nlohmann::json &j) {
        std::cout << "ToolBlur exe to_json()." << std::endl;
        ToolBlur p = *this;
        j = nlohmann::json{
                {"actualName", p.actualName},
                {"className",  p.className},
                {"toolName",   p.toolName},
                {"sole_name",  p.sole_name},

                {"order",      p.order},
                {"id",         p.id},

                {"m_data",     p.m_data},
                {"m_data_mat", p.m_data_mat},
                //                   {"m_pt", p.m_pt},
                {"dataA",      p.dataA},
                {"blur_size",  p.blur_size}
                //                 {"m_img_input", p.m_img_input}
                //  {"saveFilePath", p.saveFilePath}
                //        {"type", p.type}
        };
    }

    void from_json(const nlohmann::json &j) {
        ToolBlur p = *this;
        j.at("actualName").get_to(p.actualName);
        j.at("className").get_to(p.className);
        j.at("toolName").get_to(p.toolName);
        j.at("sole_name").get_to(p.sole_name);

        j.at("order").get_to(p.order);
        j.at("id").get_to(p.id);

        j.at("m_data").get_to(p.m_data);
        j.at("m_data_mat").get_to(p.m_data_mat);
        //             j.at("m_pt").get_to(p.m_pt);
        j.at("dataA").get_to(p.dataA);
        j.at("blur_size").get_to(p.blur_size);

        //          j.at("m_img_input").get_to(p.m_img_input);
        //        j.at("saveFilePath").get_to(p.saveFilePath);
        //        j.at("type").get_to(p.type);
    }

    int blur_size;
    //int blur_type;
    cv::Mat m_img_input;
    cv::Mat m_img_output;

    std::vector<int> m_data;

    std::vector<std::vector<int> > m_data_mat;

    typedef struct pt3 {
        float x;
        float y;
        float z;
    } tp_Pt3;


    tp_Pt3 m_pt;
    int dataA[3];
    //public:
    //    std::string  actualName;//  昵称，可以任意取名，显示在流程栏中，一般有中文
    //    std::string  className;  // 类名，  用于构造实例
    //    std::string  toolName;   //  这个是显示在工具栏中的名称，一般是中文  这个名字是固定的

    //    //  该工具实例的唯一的名称,
    //    /*
    //     * order,日期时间 ， className,  toolName  这个名字一般含有中文
    //     **/
    //    std::string  sole_name ; // 这个名字作为该工具的唯一凭据  不含有中文
    //    int order; //  在流程中的序号，是执行的过程
    //    int  id;   //  该工具实例的唯一的id ,
};


std::vector<std::string> split_std_string(const std::string &s, std::vector<std::string> &res, char delim);


//  设计名字：   order,日期时间，name,
class ToolFactory {
public:

    std::string soleName;
    int order;

    std::string str_time;
    std::string ToolName;

    std::string className;

public:

    ToolBase *generate_by_soleName() {
        ToolBase *pt = NULL;
        std::cout << "generate_by_soleName: soleName: " << soleName << std::endl;
        if (soleName.empty()) return NULL;

        std::cout << "soleName.compare(toolNameset[0] =  " << soleName.find(toolNameset[0]) << std::endl;

        //IsContainerPartition

        if (soleName.find(toolNameset[0]) >= 0) {
            pt = new ToolSource();
            std::vector<std::string> res;
            split_std_string(soleName, res, ',');

            //读取
            if (res.size() >= 3) {
                int idx = std::stoi(res[0]);
                this->str_time = res[1];
                this->className = res[2];
                this->ToolName = className_to_toolName(this->className);
                this->order = idx;

                ((ToolSource *) pt)->order = order;
                ((ToolSource *) pt)->className = "ToolSource";
                (pt)->toolName = this->ToolName;
                ((ToolSource *) pt)->sole_name = soleName;
                (pt)->actualName = soleName;
            } else
                return NULL;
        } else if (soleName.find(toolNameset[1]) >= 0) {
            pt = new ToolSaveFile();
            std::vector<std::string> res;
            split_std_string(soleName, res, ',');
            if (res.size() >= 3) {
                int idx = std::stoi(res[0]);
                this->str_time = res[1];
                this->className = res[2];
                this->ToolName = className_to_toolName(this->className);
                this->order = idx;

                (pt)->order = order;
                (pt)->className = "ToolSaveFile";
                (pt)->toolName = this->ToolName;
                (pt)->sole_name = soleName;
                (pt)->actualName = soleName;
            }
        } else if (soleName.find(toolNameset[2]) >= 0) {
            pt = new ToolBlur();

            std::vector<std::string> res;
            split_std_string(soleName, res, ',');
            if (res.size() >= 3) {
                int idx = std::stoi(res[0]);
                this->str_time = res[1];
                this->className = res[2];
                this->ToolName = className_to_toolName(this->className);
                this->order = idx;

                (pt)->order = order;
                (pt)->className = "ToolBlur";
                (pt)->toolName = this->ToolName;
                (pt)->sole_name = soleName;
                (pt)->actualName = soleName;
            }
        }

        if (!pt) {
            std::cout << "gennerate  tool failure. " << std::endl; //return  false;
        } else {
            std::cout << "gennerate  tool sucess. " << std::endl; //return  false;
        }
        return pt;
    }


    //=========================================================================================

    std::string make_soleName() {
        return std::to_string(order) + "," +
               str_time + "," +
               className + ",aaa9";// +"," +
        // ToolName;
    }

    std::string
    className_to_toolName(std::string className) {
        std::string str_toolName = "";
        if (ToolName.compare(toolNameset[0]) >= 0) {
            str_toolName = "ToolSource";  //  ToolSaveFile   ToolBlur
        }
        if (ToolName.compare(toolNameset[1]) >= 0) {
            str_toolName = "ToolSaveFile";  //  ToolSaveFile   ToolBlur
        }
        if (ToolName.compare(toolNameset[2]) >= 0) {
            str_toolName = "ToolBlur";  //  ToolSaveFile   ToolBlur
        }
        return str_toolName;
    }

    ToolBase *generate_by_toolName() {
        ToolBase *pt = NULL;
        std::cout << "generate_by_toolName: ToolName: " << ToolName << std::endl;
        if (ToolName.compare(toolNameset[0]) >= 0) {
            this->className = "ToolSource";
            this->soleName = make_soleName();

            pt = new ToolSource();
            (pt)->order = this->order;
            (pt)->sole_name = this->soleName;
            (pt)->className = this->className;
            (pt)->actualName = this->soleName;
        } else if (ToolName.compare(toolNameset[1]) >= 0) {
            this->className = "ToolSaveFile";
            this->soleName = make_soleName();
            pt = new ToolSaveFile();
            (pt)->order = this->order;
            (pt)->sole_name = this->soleName;
            (pt)->className = this->className;
            (pt)->actualName = this->soleName;
        } else if (ToolName.compare(toolNameset[2]) >= 0) {
            this->className = "ToolBlur";
            this->soleName = make_soleName();
            pt = new ToolBlur();
            (pt)->order = this->order;
            (pt)->sole_name = this->soleName;
            (pt)->className = this->className;
            (pt)->actualName = this->soleName;
        } else {
            std::cout << "gennerate  tool failure. " << std::endl;
//            return  NULL;
        }

        if (!pt) {
            std::cout << "gennerate  tool failure. " << std::endl; //return  false;
        } else {
            std::cout << "gennerate  tool sucess. " << std::endl; //return  false;
        }
        return pt;
    }


    //ToolBase* generate(
//    std::string  soleNameOrToolName,
//    int  order,
//    std::string  str_time,
//    std::string   ToolName
//    )
    //{
    //	ToolBase* pt = NULL;
    //	if (soleNameOrToolName.compare(toolNameset[0]) >= 0)
    //	{
    //		pt = new  ToolSource();
    //		if (order >= 0)
    //			((ToolSource*)pt)->order = order;
    //		std::vector<std::string> res;
    //		split_std_string(soleNameOrToolName, res, ',');
    //		//读取
    //		if (res.size() >= 3) {
    //			//          std:: res[0]
    //			int  idx = std::stoi(res[0]);
    //			order = idx;
    //			((ToolSource*)pt)->order = order = idx;
    //			((ToolSource*)pt)->className = "ToolSource";
    //			(pt)->toolName = res[3];
    //			str_time = res[1];
    //			soleName = soleNameOrToolName;
    //			((ToolSource*)pt)->sole_name = soleNameOrToolName;
    //			(pt)->actualName = soleNameOrToolName;
    //		}
    //		//  ui 添加
    //		else
    //		{
    //			((ToolSource*)pt)->order = order;
    //			((ToolSource*)pt)->toolName = soleNameOrToolName;
    //			((ToolSource*)pt)->className = "ToolSource";
    //			soleName = std::to_string(order) + ","
    //				+ str_time + "," + "ToolSource" + "," + soleNameOrToolName;
    //			((ToolSource*)pt)->sole_name = soleName;
    //			(pt)->actualName = soleName;
    //			// soleName =  soleNameOrToolName ;
    //		}
    //	}
    //	else if (soleNameOrToolName.compare(toolNameset[1]) >= 0)
    //	{
    //		pt = new  ToolSaveFile();
    //		//            pt = new  ToolSource();
    //		if (order >= 0)
    //			(pt)->order = order;
    //		std::vector<std::string> res;
    //		split_std_string(soleNameOrToolName, res, ',');
    //		if (res.size() >= 3) {
    //			//          std:: res[0]
    //			int  idx = std::stoi(res[0]);
    //			(pt)->order = order = idx;
    //			(pt)->className = "ToolSaveFile";
    //			(pt)->toolName = res[3];
    //			(pt)->sole_name = soleNameOrToolName;
    //		}
    //		else
    //		{
    //			(pt)->order = order;
    //			(pt)->toolName = soleNameOrToolName;
    //			(pt)->className = "ToolSaveFile";
    //			(pt)->sole_name = std::to_string(order) + ","
    //				+ str_time + "," + "ToolSaveFile" + "," + soleNameOrToolName;
    //		}
    //	}
    //	else if (soleNameOrToolName.compare(toolNameset[2]) >= 0)
    //	{
    //		pt = new  ToolBlur();
    //		//            pt = new  ToolSource();
    //		if (order >= 0)
    //			((ToolBlur*)pt)->order = order;
    //		std::vector<std::string> res;
    //		split_std_string(soleNameOrToolName, res, ',');
    //		if (res.size() >= 3) {
    //			//          std:: res[0]
    //			int  idx = std::stoi(res[0]);
    //			((ToolBlur*)pt)->order = order = idx;
    //			((ToolBlur*)pt)->className = "ToolBlur";
    //			((ToolBlur*)pt)->toolName = res[3];
    //			((ToolBlur*)pt)->sole_name = soleNameOrToolName;
    //		}
    //		else
    //		{
    //			((ToolBlur*)pt)->order = order;
    //			((ToolBlur*)pt)->toolName = soleNameOrToolName;
    //			((ToolBlur*)pt)->className = "ToolBlur";
    //			((ToolBlur*)pt)->sole_name = std::to_string(order) + ","
    //				+ str_time + "," + "ToolBlur" + "," + soleNameOrToolName;
    //		}
    //	}
    //	else {
    //		//            className = "";
    //	}

    //	if (!pt)
    //	{
    //		std::cout << "gennerate  tool failure. " << std::endl; //return  false;
    //	}
    //	else
    //	{
    //		std::cout << "gennerate  tool sucess. " << std::endl; //return  false;
    //	}


    //	return  pt;
    //}
private:
};


class MainApp {
public:
//    MainApp();
private:
    MainApp();

public:
    static MainApp *getInstance() {
        if (!instance) instance = new MainApp();
        else return instance;
    }

private:
    static MainApp *instance;
public:
    bool addToolItem_from_ui(int order, std::string tool_name,
                             std::string str_time, std::string &soleName
    ) {
        //        absTool->actualName = std::to_string(order );
        //        absTool->order = order  ;
        //        absTool->id = order  ;
        ToolFactory fac;
        fac.order = order;
        fac.ToolName = tool_name;
        fac.str_time = str_time;
        ToolBase *absTool = fac.generate_by_toolName();
        if (!absTool) return false;
        soleName = fac.soleName;
        flowData.insert(std::pair<int, ToolBase *>(order, absTool));
        return true;
    }


    bool addToolItem_from_json(std::string &soleName) {
        //        absTool->actualName = std::to_string(order );
        //        absTool->order = order  ;
        //        absTool->id = order  ;
        ToolFactory fac;
        fac.soleName = soleName;
        //fac.ToolName = tool_name;
        //fac.str_time = str_time;
        ToolBase *absTool = fac.generate_by_soleName();
        if (!absTool) return false;
        flowData.insert(std::pair<int, ToolBase *>(fac.order, absTool));
        return true;
    }


private:
    std::map<int, ToolBase *> flowData;
    //
public:
#if 0
    void to_json(nlohmann::json* j) {
        std::cout << "\n\n_______________________to_json__________________________" << std::endl;
        std::cout << "this->flowData.size() = " << this->flowData.size() << std::endl;//'\n';
        if (this->flowData.size() <= 0)return;
        for (std::map<  int, ToolBase*    >::iterator it = flowData.begin();
             it != flowData.end(); it++)
        {
            //            nlohmann:: json j_tmp;
            //            ((ToolSource*)  it->second)->to_json( j_tmp         );
            //            j->push_back( j_tmp    ) ;
            //            std::cout <<"j_tmp  = "<<  j_tmp << std::endl;
            nlohmann::json* pjs = new nlohmann::json();
            ((ToolSource*)it->second)->to_json(pjs);
            j->push_back(*pjs);
            std::cout << "* pjs  = " << *pjs << std::endl;
        }
        std::cout << "j  = " << j << std::endl;
    }
#endif

    void to_json(nlohmann::json &j) {
        std::cout << "_______________________to_json__________________________" << std::endl;
        std::cout << "this->flowData.size() = " << this->flowData.size() << std::endl;//'\n';
        if (this->flowData.size() <= 0)return;
        for (std::map<int, ToolBase *>::iterator it = flowData.begin();
             it != flowData.end(); it++) {
            nlohmann::json j_tmp;
            (it->second)->to_json(j_tmp); //(ToolSource*)
            j.push_back(j_tmp);
            std::cout << "j_tmp  = " << j_tmp << std::endl;
        }
        std::cout << "j  = " << j << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }


    bool from_json(nlohmann::json &j) {
        std::cout << "_______________________from_json__________________________" << std::endl;
        //for(  int i)
        std::cout << "j.size() = " << j.size() << std::endl;//'\n';
        if (j.size() <= 0)
            return false;

        this->flowData.clear();
        for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
            std::cout << "*it = " << *it << std::endl;//'\n';

            ToolFactory fac;
            std::string soleName_fromFile = (*it)["sole_name"];
            std::string str_time;
            //            std::  string  str_soleName;
            int order = -1;
            fac.soleName = soleName_fromFile;
            ToolBase *pt = fac.generate_by_soleName();

            // this-> flowData.insert(std:: pair<  int  ,ToolBase*    > ( id  ,  pt      )    ) ;
            bool res = this->addToolItem_from_json(fac.soleName);
            if (!res) {
                std::cout << "add  tool failure. " << std::endl;
                return false;
            } else std::cout << "add  tool success. " << std::endl;
        }

        std::cout << std::endl;
        std::cout << std::endl;
        return true;
    }
};


//extern  MainApp   theMainApp;
#endif // MAINAPP_H
