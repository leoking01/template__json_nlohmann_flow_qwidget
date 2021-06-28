#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include "QFileInfo"
#include <QException>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QPainter>
#include <QWidget>
#include <QPaintEvent>
#include <QMessageBox>

#include <stdio.h>

#include <iostream>
#include <string>

#include <algorithm>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

#include "commonfunc.h"
#include "mainapp.h"

namespace Ui {
class MainWindow;
}

/*
        __declspec(dllexport)
 **/
class MainWindow : public QWidget
  //  class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
protected:
    void   paintEvent(QPaintEvent *event);
    void  closeEvent(QCloseEvent *event);

private slots:
    void   textBrow_01_changed();
    void   slot_popEditToolItem();
    void   slot_doubleAddToolItem();

    void on_pushButton_addTool_clicked();

    void on_pushButton_OpenImageMat_clicked();
    void on_pushButton_saveImageXml_clicked();

    void on_pushButton_loadData_clicked();
    void on_pushButton_SaveData_clicked();

    void on_pushButton_runFlow_clicked();

private:
    ////唯一的一个QT 图像
    QImage m_img;
    cv::Mat m_cv_img_color;
    cv::Mat m_cv_img;

    std::string m_DirRead;
    std::string m_DirSave;

    void  printLogToTextBox_q(QString qWds);
    void   init_toolList();

private:
    nlohmann::json m_json;
    std::string m_jsonfile;

    std::map<int, ToolBase * >    m_flow_data  ;
    MainApp *mp_flowApp;

private:
    void openImage();

    void saveImage2Xml();
    void loadFlowData();

    void saveFlowData();
    void  addToolProc_from_ui();

    void  tool_selectFile_save_path(
            std::string title
            , const QString &p_filter
            , std::string nameFunc
            ,std::string &fileNamefull
            , std::string &filePath
           , QString &qFileNameFull);

    void tool_selectFile(
            std::string title
            , const QString &p_filter
            , std::string nameFunc
            ,std::string &fileNamefull
            , std::string &filePath, QString &qFileNameFull);
private:
};


#endif // MAINWINDOW_H



