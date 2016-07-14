#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QKeyEvent>
#include <QTextCodec>
#include <QFontDatabase>
#include <QCoreApplication>
#include <QtDebug>
#include <QDir>

#include "mainwindow.h"
#include "ui_mainwindow.h"

/*******************************************************************************
* Function Name :   MainWindow
* Description   :   构造函数
* Input         :   None
* Output        :   初始化
* Return        :   None
*******************************************************************************/
MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    style_setup();

    // 字体初始化
    font_init();

    // 设置下一界面

    iTestPage = OPTION_PAGE;
    ui->stackedWidget->setCurrentIndex(iTestPage);

    // 将MainWindow界面的page_option指向设置页面optionPage
    widgetOption = new OptionPage(ui->page_option);

    // 当signal_slide信号触发时，判定optionPage是否满足滑动状态
    connect( this, SIGNAL(signal_slide()), widgetOption, SLOT(is_allowed_slide()));

//    widget_slide_show( iNewPage, 0, TO_RIGHT);
}

/*******************************************************************************
* Function Name :   ~MainWindow
* Description   :   析构函数
* Input         :   None
* Output        :   回收对象
* Return        :   None
*******************************************************************************/
MainWindow::~MainWindow(void)
{
    delete ui;
}

/*******************************************************************************
* Function Name :   font_init
* Description   :   对程序字体进行设置，属于测试函数，后期可能删除
* Input         :   None
* Output        :   设置了文本字体
* Return        :   None
*******************************************************************************/
void MainWindow::font_init(void)
{
    // 支持中文路径
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    // 支持Tr中文
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); //支持中文文件名显示
    QFontDatabase::addApplicationFont("../BranQt/resource/fonts/HelveticaNeueDeskInterface.ttf");
    QFontDatabase::addApplicationFont("../BranQt/resource/fonts/STHeiti Medium.ttf");
    QFontDatabase database;
    foreach (const QString &family, database.families())
    {
        if (family == ".Helvetica Neue DeskInterface")
        {
            qDebug()<< "加入了Helvetica字体!" ;

        }
        else if (family == "Heiti SC")
        {
            qDebug()<< "加入了Heiti!" ;
        }
//         qDebug()<<family;
    }

    //将此字体设为QApplication的默认字体
    QFont font;
    font.setPointSize(32);
    font.setFamily("Heiti SC");

    //    font.setBold(true);
    ui->label_info->setFont(font);

    //将此字体设为QApplication的默认字体
    QFont font1;
    font1.setPointSize(32);
    font1.setFamily(".Helvetica Neue DeskInterface");
    //    font.setBold(true);
    ui->label_info_2->setFont(font1);

}

/*******************************************************************************
* Function Name :   keyPressEvent
* Description   :   自定义的键盘响应事件，来模仿触屏滑动效果，后期要做修改
* Input         :   QKeyEvent *event 键盘事件
* Output        :   滑动效果
* Return        :   None
*******************************************************************************/
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 获取当前页面id
    int iCurrentPage = ui->stackedWidget->currentIndex();

    // 触发siganl_slide信号，用于通知optionPage将要滑动，判定是否可以滑动
    emit signal_slide();
    qDebug("****%d",iCurrentPage);
    switch(event->key())
    {
        // ESC按键退出整个程序
        case Qt::Key_Escape:
        {
            QApplication::exit(0);

        }break;

        // 左键向左滑动
        case Qt::Key_Right:
        {
            // 当目前页面为设置页面，且允许滑动时

            if((iCurrentPage == OPTION_PAGE)&&widgetOption->is_allowed_slide())
            {
                qDebug("&&&&&&&&&&&%d",iCurrentPage);
                // 向左滑动
                widget_slide_show( DEFAULT_PAGE, iCurrentPage, TO_RIGHT);
            }
            else
            {
                return;
            }

        }break;

        // 右键向右滑动
        case Qt::Key_Left:
        {
            if(iCurrentPage == DEFAULT_PAGE )
            {   // 向右滑动
                widget_slide_show( OPTION_PAGE, iCurrentPage, TO_LEFT);
            }

        }break;

        default:break;

    }
}

/*******************************************************************************
* Function Name :   mousePressEvent
* Description   :   自定义的鼠标响应事件，来模仿触屏滑动效果
* Input         :   QMouseEvent *event 键盘事件
* Output        :   获取当前坐标
* Return        :   None
*******************************************************************************/
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        posPressed = event->pos();
        qDebug("%d:%d",posPressed.x(),posPressed.y());
    }

}

/*******************************************************************************
* Function Name :   mouseMoveEvent
* Description   :   自定义的鼠标响应事件
* Input         :   QMouseEvent *event 键盘事件
* Output        :   None
* Return        :   None
*******************************************************************************/
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{


}

/*******************************************************************************
* Function Name :   mouseReleaseEvent
* Description   :   自定义的鼠标响应事件，当鼠标释放时，触发
* Input         :   QMouseEvent *event 键盘事件
* Output        :   滑动页面
* Return        :   None
*******************************************************************************/
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // 获取当前页面i
    int iCurrentPage =  ui->stackedWidget->currentIndex();
    posRelease = event->pos();
    qDebug("%d:%d",posRelease.x(),posRelease.y());
    if( posRelease.x() > posPressed.x())
    {
        emit signal_slide();

        // 当目前页面为设置页面，且允许滑动时
        if((iCurrentPage == OPTION_PAGE)&&widgetOption->is_allowed_slide())
        {
            // 向左滑动
            widget_slide_show( DEFAULT_PAGE, iCurrentPage, TO_RIGHT);
        }
        else
        {
            return;
        }
    }
    else if(posRelease.x() < posPressed.x())
    {
        emit signal_slide();

        if(iCurrentPage == DEFAULT_PAGE )
        {   // 向右滑动
            widget_slide_show( OPTION_PAGE, iCurrentPage, TO_LEFT);
        }
    }
    else
    {
        return;
    }
}

/*******************************************************************************
* Function Name :   widget_slide_show
* Description   :   页面左右滑动函数
* Input         :   int iTargetPage                     目的页面
*                   int iCurrentPage                   当前页面
*                   SlideDirection slide_direction  滑动方向
* Output        :   None
* Return        :   None
*******************************************************************************/
void MainWindow::widget_slide_show( int iTargetPage, int iCurrentPage, SlideDirection slide_direction)
{

    // 各页面坐标
    QPoint new_start_point, new_end_point;
    QPoint old_start_point, old_end_point;

    // 目的页面坐标与当前页面坐标
    iNewPage = iTargetPage;
    iOldPage = iCurrentPage;

    // 将UI界面栈中取出需要的页面，并分别获取新页面和老页面的坐标
    ui->stackedWidget->widget(iNewPage)->setGeometry( 0, 0, ui->stackedWidget->width(), ui->stackedWidget->height());

    // 新坐标也就是所谓的（0,0）
    posNewPage = ui->stackedWidget->widget(iNewPage)->pos();
    posOldPage = ui->stackedWidget->widget(iOldPage)->pos();

    // 假如向左移动，移动新页面坐标
    if(slide_direction == TO_LEFT)
    {

        // 新页面移动至（页面宽度，0）处
        ui->stackedWidget->widget(iNewPage)->move( ui->stackedWidget->width(), 0);
        old_start_point = QPoint( posOldPage.x(), posOldPage.y());

        // 老页面移动后的坐标为（之前的横坐标减去页面宽度，纵坐标不变）
        old_end_point = QPoint( -ui->stackedWidget->width() + posOldPage.x(), posOldPage.y());
        new_start_point = QPoint( ui->stackedWidget->width() + posNewPage.x(), posNewPage.y());
        new_end_point = QPoint( posNewPage.x(), posNewPage.y());
    }

    // 假如向右移动，移动新页面坐标
    if(slide_direction == TO_RIGHT)
    {
        // 新页面移动至（-页面宽度，0）处
        ui->stackedWidget->widget(iNewPage)->move( -ui->stackedWidget->width(), 0);
        old_start_point = QPoint( posOldPage.x(), posOldPage.y());

        // 老页面移动后的坐标为（之前的横坐标加上页面宽度，纵坐标不变）
        old_end_point = QPoint( ui->stackedWidget->width() + posOldPage.x(), posOldPage.y());
        new_start_point = QPoint( -ui->stackedWidget->width() + posNewPage.x(), posNewPage.y());
        new_end_point = QPoint( posNewPage.x(), posNewPage.y());
    }

    // 将窗口显示出来并置为第一层
    ui->stackedWidget->widget(iNewPage)->show();
    ui->stackedWidget->widget(iNewPage)->raise();

    // 老界面移动动画、持续时间、运动轨迹，起点坐标，终点坐标
    QPropertyAnimation *oldpage_anim = new QPropertyAnimation( ui->stackedWidget->widget(iOldPage), "pos");
    oldpage_anim->setDuration(400);
    oldpage_anim->setEasingCurve(QEasingCurve::OutBack);
    oldpage_anim->setStartValue(old_start_point); // old pos
    oldpage_anim->setEndValue(old_end_point); // new pos

    // 新界面移动动画、持续时间、运动轨迹，起点坐标，终点坐标
    QPropertyAnimation *newpage_anim = new QPropertyAnimation( ui->stackedWidget->widget(iNewPage), "pos");
    newpage_anim->setDuration(400);
    newpage_anim->setEasingCurve(QEasingCurve::OutBack);
    newpage_anim->setStartValue(new_start_point);
    newpage_anim->setEndValue(new_end_point);

    // 新页面和老页面的运动进行并行开始
    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(oldpage_anim);
    animgroup->addAnimation(newpage_anim);

    // 当动画完成后，触发animation_done_slot()函数
    QObject::connect( animgroup, SIGNAL(finished()), this, SLOT(animation_done_slot()) );
    animgroup->start();
}

/*******************************************************************************
* Function Name :   animation_done_slot
* Description   :   动画完成后所要触发的函数，将目的页面设为当前页面
* Input         :   None
* Output        :   设置当前页面
* Return        :   None
*******************************************************************************/
void MainWindow::animation_done_slot(void)
{
    // show new page
    ui->stackedWidget->setCurrentIndex(iNewPage);

    // 隐藏老界面并移动至以前坐标
    ui->stackedWidget->widget(iOldPage)->hide();
    ui->stackedWidget->widget(iOldPage)->move(posOldPage);

    // save iOldPage
    iNewPage = iOldPage;
}

/*******************************************************************************
* Function Name :   style_setup
* Description   :   QSS初始化
* Input         :   None
* Output        :   美化界面
* Return        :   None
*******************************************************************************/
void MainWindow::style_setup(void)
{
    qDebug("qss....................start");

    // 读取 qt qss文件
    QFile qss_file(":resource/qss/BranQt.qss");
    qss_file.open(QFile::ReadOnly);
    QString qss_style = qss_file.readAll();
    qss_file.close();

    qDebug()<<qss_style;
    qApp->setStyleSheet(qss_style);

    qDebug("qss....................ok");

}
