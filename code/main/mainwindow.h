#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QPoint>
#include <QKeyEvent>
#include <QMouseEvent>
#include "optionPage.h"

#define DEFAULT_PAGE 0                                                  //
#define OPTION_PAGE 1                                                   //

enum SlideDirection                                                     // 枚举滑动方向
{
    TO_LEFT = 0x01,                                                     // 向左滑动
    TO_RIGHT = 0x02                                                     //向右滑动
};

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow(void);

private slots:

    void animation_done_slot(void);                                     // 滑动动画效果槽

signals:

    void signal_slide();                                                // 滑动信号

protected:

    void keyPressEvent(QKeyEvent *event);                               // 键盘响应事件
    void mousePressEvent(QMouseEvent *event);                           //
    void mouseMoveEvent(QMouseEvent *event);                            //
    void mouseReleaseEvent(QMouseEvent *event);                         //


private:

    Ui::MainWindow *ui;


    int iNewPage, iOldPage;                                             // 定义移动后的页面和移动前的页面
    int iTestPage;
    QPoint posNewPage, posOldPage, posPressed, posRelease;              // 用于页面移动的坐标
    OptionPage *widgetOption;                                           // 设置页面

    void style_setup(void);                                             // 风格定制
    void font_init(void);
    void widget_slide_show( int iTargetPage, int iCurrentPage ,
                           SlideDirection slide_direction );            // 实现窗口之间切换的滑动效果
};

#endif // MAINWINDOW_H

