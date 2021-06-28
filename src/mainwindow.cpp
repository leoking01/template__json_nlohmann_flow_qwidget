#include "mainwindow.h"
#include "ui_mainwindow.h"

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow) {
    std::cout << "    __________________________________________________________________" << std::endl;
    std::cout << "    |                                                                 |" << std::endl;
    std::cout << "_____                   MainWindow():  init  start              _____" << std::endl;
    ui->setupUi(this);
    //icon
    setWindowIcon(QIcon(":/resourceMy/logo.ico")); //为窗口标题添加图片，注意要路径要添加 ": "
    init_toolList();
    m_DirRead = "d:/";
    m_DirSave = "d:/";
    //    mp_flowApp = new MainApp();
    mp_flowApp = MainApp::getInstance(); // & theMainApp;
    //=============================================== slots ====================================================================
    //  ------------------------------------   控件们 -------------------------------
    connect(this->ui->textBrowser, &QTextBrowser::textChanged, this, &MainWindow::textBrow_01_changed);
    connect(this->ui->listWidget_2, &QListWidget::doubleClicked, this, &MainWindow::slot_popEditToolItem);
    connect(this->ui->listWidget, &QListWidget::doubleClicked, this, &MainWindow::slot_doubleAddToolItem);
    //--------------------------------------------------------------------------
    std::cout << "____                         MainWindow():  init  finish.                        ____" << std::endl;
    std::cout << "    |                                                                            |" << std::endl;
    std::cout << "    -----------------------------------------------------------------------------\n\n" << std::endl;
}

MainWindow::~MainWindow() {
    delete ui;
}

//---------------------事件函数的重载-------------------------------
void MainWindow::paintEvent(QPaintEvent *event) {
    if (0) {
        QPainter painter(this->ui->label);
        if (!m_img.isNull())
            painter.drawImage(0, 0, m_img);
        QWidget::paintEvent(event);
    }
    if (0) {
        QPainter painter(this);
        if (!m_img.isNull())
            painter.drawImage(0, 0, m_img);
        QWidget::paintEvent(event);
    }
    if (0) {
        if (!m_img.isNull())
            this->ui->label->setPixmap(QPixmap::fromImage(m_img));
    }
    // 使用at的图像 qImage 进行显示；  这里不使用这个方式；
    if (0) {
        if (0) {
            QImage image;
            image.load("lena.jpg");
        }
        if (m_img.isNull())
            return;
        QPainter painter(&m_img);
        QImage resultImg = m_img.scaled(ui->label->size(),
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation);
        ui->label->setPixmap(QPixmap::fromImage(resultImg));
        ui->label->show();
    }
    if (1) {
        if (m_cv_img.empty() || !m_cv_img.data)
            return;
        displayResult(this->m_cv_img, this->ui->label);
    }
    if (1) {
        if (m_cv_img_color.empty() || !m_cv_img_color.data)
            return;
    }
}


void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QString("..退出程序.."),
                                   QString("..确认退出程序.."),
                                   QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No) {
        event->ignore(); // 忽略退出信号，程void on_pushButton_29_clicked();
    } else if (button == QMessageBox::Yes) {
        event->accept(); // 接受退出信号，程序退出
    }
}

void MainWindow::textBrow_01_changed() {
    this->ui->textBrowser->moveCursor(QTextCursor::End);
}

void MainWindow::printLogToTextBox_q(QString qWds) {
#define DEBUG_PRINT_LOG_LK
#ifdef  DEBUG_PRINT_LOG_LK
    std::string time = getDatetimeStr();
    QTextCodec *code = QTextCodec::codecForName("utf8");//解决中文路径问题   //   gb2322
    std::string stdWds = code->fromUnicode(qWds).data();
    stdWds = time + ":" + stdWds;
    this->ui->textBrowser->append(QString::fromUtf8(stdWds.c_str()));
    std::cout << qWds.toStdString() << std::endl;
#endif
}

void MainWindow::init_toolList() {
    for (int i = 0; i < nums_of_tools; i++) {
        QListWidgetItem* lst1  ;
        lst1 = new QListWidgetItem(QIcon(":/images/data.jpg")
                                   ,   QString::fromStdString(toolNameset[i])
                                   ,  this->ui->listWidget);
        //        this->ui->listWidget->addItem(    QString::fromStdString(toolNameset[i]));
        this->ui->listWidget->  insertItem( i, lst1 );
    }
}

//--------------------------------------------------------------------------------------
void MainWindow::tool_selectFile(std::string title, const QString &p_filter, std::string nameFunc,
                                 std::string &fileNamefull, std::string &filePath, QString &qFileNameFull) {
    printLogToTextBox_q("\n\n\n\n\n-------------------------------><--------------------------------");
    //    QPushButton *btn = (QPushButton *) sender();  // 获取到了发送该信号按钮的指针
    //    this->printLogToTextBox(("you clicked button : " + btn->text()).toStdString());
    //    nameFunc = btn->text().toStdString();
    std::string pathPast = filePath;
    if (pathPast.empty()) {
        printLogToTextBox_q("tool_selectFile: failure to get filePath from ini file.");
        pathPast = "C:/Users/";
    } else {
        this->ui->textBrowser->append(pathPast.c_str());
    }
    QString file_name;
    QString file_path = QString::fromStdString(pathPast);
    QFileInfo fi;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    QString::fromStdString(title),
                                                    file_path,
                                                    p_filter);
    if (fileName.isNull() || fileName.isEmpty())
        return;
    qFileNameFull = fileName;
    QTextCodec *code = QTextCodec::codecForName("utf-8");//解决中文路径问题
    fileNamefull = code->fromUnicode(fileName).data();
    fi = QFileInfo(fileName);
    file_name = fi.fileName();
    file_path = fi.absolutePath();
    filePath = code->fromUnicode(file_path).data();
    this->printLogToTextBox_q("tool_selectFile: fileNamefull = " + QString::fromStdString(fileNamefull));
    this->printLogToTextBox_q(
                "tool_selectFile: fileName.toStdString() = " + QString::fromStdString(fileName.toStdString()));
    this->printLogToTextBox_q(fileName.toStdString().c_str());
    this->printLogToTextBox_q(
                "tool_selectFile: file_path.toStdString() = " + QString::fromStdString(file_path.toStdString()));
    this->printLogToTextBox_q(
                "tool_selectFile: qFileNameFull.toStdString() = " + QString::fromStdString(qFileNameFull.toStdString()));
}

void MainWindow::tool_selectFile_save_path(std::string title, const QString &p_filter, std::string nameFunc,
                                           std::string &fileNamefull, std::string &filePath, QString &qFileNameFull) {
    printLogToTextBox_q("\n\n\n\n\n-------------------------------><--------------------------------");
    //    QPushButton *btn = (QPushButton *) sender();  // 获取到了发送该信号按钮的指针
    //    this->printLogToTextBox(("you clicked button : " + btn->text()).toStdString());
    //    nameFunc = btn->text().toStdString();
    std::string pathPast = filePath;
    if (pathPast.empty()) {
        printLogToTextBox_q("tool_selectFile: failure to get filePath from ini file.");
        pathPast = "C:/Users/";
    } else {
        this->ui->textBrowser->append(pathPast.c_str());
    }
    QString file_name;
    QString file_path = QString::fromStdString(pathPast);
    QFileInfo fi;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    QString::fromStdString(title),
                                                    file_path,
                                                    p_filter);
    if (fileName.isNull() || fileName.isEmpty())
        return;
    qFileNameFull = fileName;
    QTextCodec *code = QTextCodec::codecForName("utf-8");//解决中文路径问题
    fileNamefull = code->fromUnicode(fileName).data();
    fi = QFileInfo(fileName);
    file_name = fi.fileName();
    file_path = fi.absolutePath();
    filePath = code->fromUnicode(file_path).data();
    this->printLogToTextBox_q(QString::fromStdString("filepath = " + filePath));
}

#include  "QString"
#include  "QDebug"
#include <QApplication>
#include <QDebug>
#include <QWidget>

#include <QTextCodec>

void MainWindow::on_actionopenImagePng_triggered() {
    std::string filePathFull;
    std::string filePath = m_DirRead;;
    QString qFileNameFull;
    tool_selectFile(("select range iamge file."),
                    tr("allfileType(*);;图片文件(*png *jpg *pcd *ply *png);;pcd文件(*pcd *ply *png);;"
                       "本本文件(*txt)"),
                    "path_rangeImage", filePathFull, filePath, qFileNameFull);
    m_DirRead = filePath;
    qDebug("filePathFull.c_str()  = %s", filePathFull.c_str());
    qDebug(" filePath.c_str() = %s", filePath.c_str());
    qDebug(" qFileNameFull.toStdString().c_str()  = %s", qFileNameFull.toStdString().c_str());
    if (filePathFull.empty())
        return;
    cv::Mat depthImage = cv::imread(filePathFull, cv::IMREAD_UNCHANGED);//读取图片数据
    depthImage = cv::imread(qFileNameFull.toUtf8().data(), cv::IMREAD_UNCHANGED);//读取图片数据
    if (depthImage.cols <= 0 || !depthImage.data) {
        this->printLogToTextBox_q(
                    QString::fromUtf8("selectFile_rangeImage: read iamge failure .  .."));
        return;
    } else {
        m_cv_img = depthImage;
        this->printLogToTextBox_q(QString::fromUtf8("selectFile_rangeImage: read image ok.   .."));
        print_cvMat_info(depthImage, this->ui->textBrowser);
        repaint();
    }
}

std::string get_post_fix(std::string str) {
    std::string post;
    std::string name1 = str;// "/a/b/c/v/zhiodfh.jpg";
    int pos1 = name1.find_last_of('.');
    std::string name2 = name1.substr(pos1 + 1);
    std::cout << "pos1:" << pos1 << std::endl;
    std::cout << "name2:" << name2 << std::endl;
    int pos2 = name2.find('.');
    std::string name3 = name2.substr(0, pos2);
    post = name3;
    return post;
}

#include  "fstream"

template<typename Tp>
void wirte_mat_to_csv(cv::Mat img,
                      std::string savePathCsv, char separator) {
    std::ofstream file(savePathCsv.c_str(), std::ofstream::out);
    if (!file) {
        std::string error_message = "No valid input file was given, please check thegiven filename.";
    }
    std::string line, path, classlabel;
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.rows; j++) {
            if (j != img.rows - 1)
                file << img.at<Tp>(i, j) << separator;// ",";
            else
                file << img.at<Tp>(i, j) << "\n";
        }
    }
    file.close();
}

void MainWindow::on_actionsaveImageXml_triggered() {
    std::string filePathFull;
    std::string filePath;
    QString qFileNameFull;
    tool_selectFile_save_path(("select range iamge file."),
                              tr("图片文件(*png);;"
                                 "pcd文件(*jpg);;"
                                 "pcd文件(*tiff);;"
                                 "pcd文件(*tif);;"
                                 "pcd文件(*pbm);;"
                                 "pcd文件(*pgm);;"
                                 "pcd文件(*exr);;"
                                 "pcd文件(*jp2);;"
                                 "pcd文件(*SR);;"
                                 "pcd文件(*RAS);;"
                                 "pcd文件(*dib);;"
                                 "pcd文件(*bmp);;"
                                 "pcd文件(*pcd);;"
                                 "pcd文件(*ply);;"
                                 "本本文件(*xml);;"
                                 "本本文件(*csv);;"
                                 "本本文件(*txt);;"
                                 "pcd文件(*bin);;"
                                 "allfileType(*)"),
                              "path_rangeImage", filePathFull, filePath, qFileNameFull);
    if (filePathFull.empty())
        return;
    std::string post = get_post_fix(filePathFull);
    std::cout << "post = " << post << std::endl;
    if (!this->m_cv_img.data)
        return;
    if (post.compare("jpe") >= 0 ||
            post.compare("jpg") >= 0 ||
            post.compare("jpeg") >= 0 ||
            post.compare("tiff") >= 0 ||
            post.compare("tif") >= 0 ||
            post.compare("png") >= 0 ||
            post.compare("pbm") >= 0 ||
            post.compare("pgm") >= 0 ||
            post.compare("ppm") >= 0 ||
            post.compare("bmp") >= 0 ||
            post.compare("dib") >= 0 ||
            post.compare("EXR") >= 0 ||
            post.compare("jp2") >= 0 ||
            post.compare("SR") >= 0 ||
            post.compare("RAS") >= 0
            ) {
        cv::imwrite(filePathFull, this->m_cv_img);
    } else if (post.compare("csv") >= 0 || post.compare("txt") >= 0) {
        if (this->m_cv_img.elemSize1() == 2 && this->m_cv_img.channels() == 1) {
            std::ofstream of(filePathFull);
            for (int i = 0; i < this->m_cv_img.rows; i++) {
                for (int j = 0; j < this->m_cv_img.cols; j++) {
                    of << this->m_cv_img.at<ushort>(i, j);
                }
            }
            of.close();
        } else if (this->m_cv_img.elemSize1() == 4 && this->m_cv_img.channels() == 1
                   && this->m_cv_img.type() == 5) {
            std::ofstream of(filePathFull);
            for (int i = 0; i < this->m_cv_img.rows; i++) {
                for (int j = 0; j < this->m_cv_img.cols; j++) {
                    of << this->m_cv_img.at<float>(i, j);
                }
            }
            of.close();
        } else if (this->m_cv_img.elemSize1() == 1 && this->m_cv_img.channels() == 1) {
            std::ofstream of(filePathFull);
            for (int i = 0; i < this->m_cv_img.rows; i++) {
                for (int j = 0; j < this->m_cv_img.cols; j++) {
                    of << this->m_cv_img.at<uchar>(i, j);
                }
            }
            of.close();
        } else if (this->m_cv_img.elemSize1() == 1 && this->m_cv_img.channels() == 3) {
            std::ofstream of(filePathFull);
            for (int i = 0; i < this->m_cv_img.rows; i++) {
                for (int j = 0; j < this->m_cv_img.cols; j++) {
                    of << this->m_cv_img.at<cv::Vec3b>(i, j)[0] << this->m_cv_img.at<cv::Vec3b>(i, j)[1]
                            << this->m_cv_img.at<cv::Vec3b>(i, j)[2];
                }
            }
            of.close();
        } else {
            std::cout << "cant transfer img format .  " << std::endl;
            return;
        }
    } else if (post.compare("xml") >= 0) {
        std::string mat_save_path_xml = filePathFull;//+".xml";

        cv::FileStorage fswrite(mat_save_path_xml, cv::FileStorage::WRITE);
        fswrite << "m_cv_img" << this->m_cv_img;
        fswrite.release();
        std::cout << "save mat to: mat_save_path_xml = " << mat_save_path_xml << std::endl;
    } else {
        std::cout << "unkown format cancel.  " << std::endl;
        return;
    }

    return;

    //show image
    cv::Mat depthImage = cv::imread(filePathFull, cv::IMREAD_UNCHANGED);//读取图片数据
    if (depthImage.cols <= 0 || !depthImage.data) {
        this->printLogToTextBox_q(
                    QString::fromUtf8("selectFile_rangeImage: read iamge failure .   .."));
        return;
    } else {
        m_cv_img = depthImage;
        //print
        this->printLogToTextBox_q(QString::fromUtf8("selectFile_rangeImage: read image ok.  .."));
        print_cvMat_info(depthImage);
        repaint();
    }

    return;

#if 0
    //----------------------------------------------------
    std::string filePathFull;
    std::string filePath = m_DirSave;
    QString qFileNameFull;
    tool_selectFile_save_path(("select range iamge file."),
                              tr("allfileType(*);;图片文件(*png *jpg *pcd *ply *png);;pcd文件(*pcd *ply *png);;"
                                 "本本文件(*txt)"),
                              "path_rangeImage", filePathFull, filePath, qFileNameFull);
    m_DirSave = filePath ;
    if (filePathFull.empty())
        return;
    // qDebug() << "\nfilePathFull : " << qFileNameFull;
    // this->ui->lineEdit_7->setText(qFileNameFull);
    //   this->ui->comboBox->addItem(qFileNameFull);


    if( ! this->m_cv_img.data )return ;
    //if( ! this->ui->lineEdit_7->text().isEmpty() )return ;
    std::string mat_save_path_xml =  filePathFull +".xml";//this->ui->lineEdit_7->text().toStdString()+     ".xml";

    cv::FileStorage fswrite(mat_save_path_xml, cv:: FileStorage::WRITE);
    fswrite << "m_cv_img" << this->m_cv_img;
    fswrite.release();
    std::cout << "save mat to: mat_save_path_xml = " << mat_save_path_xml<<   std::   endl;
    return;


    //show image
    cv::Mat depthImage = cv::imread(filePathFull, cv::IMREAD_UNCHANGED);//读取图片数据
    if (depthImage.cols <= 0 || !depthImage.data) {
        this->printLogToTextBox_q(
                    QString::fromUtf8("selectFile_rangeImage: read iamge failure .   ..") );
        return;
    } else {
        m_cv_img = depthImage;
        //print
        this->printLogToTextBox_q(QString::fromUtf8("selectFile_rangeImage: read image ok.  ..") );
        print_cvMat_info(depthImage);
        repaint();
    }
#endif
}

//---------------------------------------------------------------------
void MainWindow::on_actionrun01_triggered() {
    this->printLogToTextBox_q(QString::fromUtf8("on_actionrun01_triggered: null ..."));
}

//-------------------------------------------------------------------------------
/*
 *  \brief:  添加工具
*/
//编辑弹出的工具项
void MainWindow::slot_popEditToolItem() {
    //listWidget_2
    if (!this->ui->listWidget_2->currentItem()) return;
    int idx = this->ui->listWidget_2->currentRow();
    QString curLine = this->ui->listWidget_2->currentItem()->text();

    std::string actualName = curLine.toStdString();
    std::string toolName;// = actualName_to_toolName(actualName);
    std::cout << "slot_popEditToolItem: actualName = " << actualName << "---------> -->"
              << std::endl;

    int id_tool = -1;// = actualName_to_idx__from_flow_list(actualName);
    std::cout << "id_tool = " << id_tool << std::endl;

    switch (id_tool) {
    case 2: {
        //        UISourceFilePcd *dt = new UISourceFilePcd(this, this->mp_flowApp, actualName);//QDialog
        //        dt->setWindowTitle(QString::fromStdString(actualName));
        //        dt->setAttribute(Qt::WA_DeleteOnClose);
        //        dt->setWindowModality(Qt::NonModal);
        //        //        dt->mp_flowData = this->mp_flowApp;
        //        dt->show();
        break;
    default:
            this->printLogToTextBox_q(" no ui provided just now.  ");
            break;
        }
        return;
    }
}

void MainWindow::addToolProc_from_ui() {
    //    QPushButton *btn = (QPushButton *) sender();  // 获取到了发送该信号按钮的指针
    //    this->printLogToTextBox_q("you clicked button : " + btn->text().toStdString());
    this->printLogToTextBox_q("slot__addToolItemToFlow");
    //选择工具名字
    int id = this->ui->listWidget->currentRow();
    int nums = this->ui->listWidget_2->count();
    QString curIt = this->ui->listWidget->currentItem()->text();
    std::string toolItemName = curIt.toStdString();
    std::string timeIdStr = getDatetimeStr_forID();
    if (id < 0) {
        printLogToTextBox_q("no tool was selected .没有工具被选中.");
        return;
    } else {
        printLogToTextBox_q((QString("you have selected tool id: 已经选中工具: id: ") + QString::number(id) +
        " : " + curIt));
    }
#if 0
    //这句话 用 rapidjson写到文件中去。
    setConfig(toolItemName, str_insert);
#endif
#if 0
    //打印一下   当前的pcd 文件
    QString qPcdFileNameCur = this->ui->lineEdit->text();
    std::string pcdFileNameCur = qPcdFileNameCur.toStdString();
    printLogToTextBox("当前线框的pcdfile ： " + pcdFileNameCur);
#endif
    //    std::string str_insert;
    //    str_insert = std::to_string(nums ) +"," +
    //            getDatetimeStr_forID() + "," +
    //            toolItemName;
    //    this->printLogToTextBox_q(  "str_insert =  "+ QString::fromStdString( str_insert) );
    // add  to  app data
    //    std::map<std::string, std::string> tooldAta;
    //    ToolBase *absTool = new ToolSource();//= gen_tool_by_actualName(str_insert);
    //    if (!absTool) {
    //        this->printLogToTextBox_q("can,t generate tool instance . please check. null tool.  return ; ");
    //        return;
    //    }
    //   ToolFactory  *fac = new ToolFactory ();
    //   //std::string  soleName ;
    //   fac->order = nums;
    //fac->ToolName = toolItemName ;
    //fac->str_time = timeIdStr ;
    //   ToolBase *absTool  = fac->generate_by_toolName();// toolItemName,nums, timeIdStr,  soleName  ) ;
    //----- ------添加到流程---- ----------
    std::string soleName;
    bool res_insert = this->mp_flowApp->addToolItem_from_ui(nums,
                                                            toolItemName, timeIdStr, soleName);
    if (res_insert) {
        //添加到流程表
        if( 0 )
            this->ui->listWidget_2->addItem(QString::fromStdString(soleName));

        QListWidgetItem* lst5 = new QListWidgetItem(QIcon(":/images/printer.jpeg"), QString::fromStdString(soleName),   this->ui->listWidget_2);
        this->ui->listWidget_2->insertItem(1, lst5);
    }
    //  this->mp_flowApp->print_info();
    //   delete  fac;
    return;
}
//-------------------------------------------------------------------------

void MainWindow::slot_doubleAddToolItem() {
    addToolProc_from_ui();
}



//---------------------------------------------------------------------
void MainWindow::on_actionloadData_triggered() {
    // m_jsonfile = "D:\\AwsOneDriver\\note_light\\light_json_nlohmann_qt\\src/test.json";
    //    load_json( m_json  ,m_jsonfile ) ;
    std::string readFile = "../../src/out.json";
    printLogToTextBox_q("load from readFile: " + QString::fromStdString(readFile));
    this->m_json.clear();
    load_json(this->m_json, readFile);
    //return  ;
    //this->mp_flowApp->m
    //update app
    bool res = this->mp_flowApp->from_json(this->m_json);
    if (!res) {
        std::cout << "unserialization  falure.  " << std::endl;//'\n';
        this->m_json.clear();
    } else {
        std::cout << "unserialization  success.  " << std::endl;//'\n';
    }
    this->ui->listWidget_2->clear();
    for (nlohmann::json::iterator it = this->m_json.begin(); it != this->m_json.end(); ++it) {
        std::cout << "*it = " << *it << std::endl;//'\n';
        if( 0 )
            this->ui->listWidget_2->addItem(
                    QString::fromStdString((*it)["sole_name"]));

        QListWidgetItem* lst5 = new QListWidgetItem(QIcon(":/images/printer.jpeg")
                                                    , QString::fromStdString((*it)["sole_name"])
                ,   this->ui->listWidget_2);
        this->ui->listWidget_2->insertItem(1, lst5);
    }
}

void MainWindow::on_actionSaveData_triggered() {
    std::string savefile = "../../src/out.json";
    //    save_json( m_json  ,m_jsonfile ) ;
    this->m_json = {};
    nlohmann::json *js = new nlohmann::json();
    //    this->mp_flowApp->to_json( js  );return ;
    this->mp_flowApp->to_json(this->m_json);//return ;
    std::cout << "this->m_json  = " << this->m_json << std::endl;
    //    return ;
#if 1
    if (this->m_json.size() < 0) {
        printLogToTextBox_q("data is null. ");
        return;
    }
    save_json(this->m_json, savefile);
    printLogToTextBox_q("save to savefile : " + QString::fromStdString(savefile));
    return;
    //    // write prettified JSON to another file
    //    std::ofstream o(savefile);
    //    o << std::setw(4) << this->m_json << std::endl;
#endif
}
//-------------------------------------------------------------------------
void MainWindow::on_actionaddTool_triggered() {
    addToolProc_from_ui();
}

//add tool
void MainWindow::on_pushButton_addTool_clicked()
{
    addToolProc_from_ui();
}

void MainWindow::on_pushButton_OpenImageMat_clicked()
{
    on_actionopenImagePng_triggered ();
}
//on_actionsaveImageXml_triggered

void MainWindow::on_pushButton_saveImageXml_clicked()
{
    on_actionsaveImageXml_triggered ();
}

void MainWindow::on_pushButton_loadData_clicked()
{
    on_actionloadData_triggered();
}

void MainWindow::on_pushButton_SaveData_clicked()
{
    on_actionSaveData_triggered() ;
}
