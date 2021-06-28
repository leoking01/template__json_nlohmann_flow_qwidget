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
//class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //--------------------------------------------------------------------------------

protected:
    void   paintEvent(QPaintEvent *event);

    void  closeEvent(QCloseEvent *event);

private slots:

    void on_actionopenImagePng_triggered();

    void on_actionsaveImageXml_triggered();

    void on_actionrun01_triggered();

    void   textBrow_01_changed();

    void on_actionloadData_triggered();

    void on_actionSaveData_triggered();

    void on_actionaddTool_triggered();

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
    std::string m_jsonfile;//= "D:\\AwsOneDriver\\note_light\\light_json_nlohmann_qt\\src/testOut.json";

    MainApp *mp_flowApp;

//    void MainWindow::addToolProc();
    void  addToolProc_from_ui();

    void   tool_selectFile_save_path(std::string title, const QString &p_filter, std::string nameFunc,
                                               std::string &fileNamefull, std::string &filePath,
                                               QString &qFileNameFull);

    void   tool_selectFile(std::string title, const QString &p_filter, std::string nameFunc,
                                     std::string &fileNamefull, std::string &filePath, QString &qFileNameFull);
};


#endif // MAINWINDOW_H



