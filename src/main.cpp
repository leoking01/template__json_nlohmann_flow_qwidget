#include "mainwindow.h"
#include <QApplication>

#pragma execution_character_set("utf-8")

#include <QTextCodec>

int main(int argc, char *argv[]) {
    //中文支持
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));        //支持Tr中文
    //    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); //支持中文文件名显示
    QFont font;
    font.setPointSize(16); //实际上是16的字号，但设成16却不行
    font.setFamily(("wenquanyi"));
    font.setBold(false);
    //    a.setFont(font);

    //#define   onlyRunOnWindows
#ifdef  onlyRunOnWindows
    AllocConsole();//为当前的窗口程序申请一个Console窗口
    freopen("CONOUT$", "a+", stdout);
#endif

    //--------------------- ini 用 iniParser -------------------------------------
    std::cout << "main_test_ini_cpp_001 start:------------------" << std::endl;
    //    main_test_ini_cpp_001();
    std::cout << "main_test_ini_cpp_001 finish.------------------" << std::endl;

    //---------------------------------------------------------
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
