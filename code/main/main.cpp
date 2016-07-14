#include <QApplication>

#include "mainwindow.h"
#include "ui_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 鼠标隐藏
//    QApplication::setOverrideCursor(Qt::BlankCursor);
    MainWindow w;

    // 设置固定大小宽854px，高480px
    w.setGeometry(0, 0, 854, 480);

    // 去除边框
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();


    return a.exec();
}
