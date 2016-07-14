#include <QDebug>

#include "optionPage.h"
#include "ui_optionPage.h"
#include "setWifiPage.h"
#include "ui_setWifiPage.h"


/*******************************************************************************
* Function Name :   OptionPage
* Description   :   构造函数
* Input         :   None
* Output        :   初始化
* Return        :   None
*******************************************************************************/
OptionPage::OptionPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionPage)
{
    ui->setupUi(this);

    // 信号与槽的连接，当时间设置选项卡clicked触发，通过函数jump_setTime_page()跳转设置页面
    connect( ui->option_setTime, SIGNAL(clicked()), this, SLOT(jump_setTime_page()));

    // 信号与槽的连接，当Wifi设置选项卡clicked触发，通过函数jump_setWifi_page()跳转设置页面
    connect( ui->option_setWifi, SIGNAL(clicked()), this, SLOT(jump_setWifi_page()));

    // 信号与槽的连接，当恢复出厂设置选项卡clicked触发，通过函数jump_resetFactory_page()跳转设置页面
    connect( ui->option_resetFactory, SIGNAL(clicked()), this, SLOT(jump_resetFactory_page()));

    // 信号与槽的连接，当恢复出厂设置选项卡clicked触发，通过函数jump_resetFactory_page()跳转设置页面
    connect( ui->option_adjustLight, SIGNAL(clicked()), this, SLOT(jump_adjustLight_page()));
}

/*******************************************************************************
* Function Name :   ~OptionPage
* Description   :   析构函数
* Input         :   None
* Output        :   回收对象
* Return        :   None
*******************************************************************************/
OptionPage::~OptionPage(void)
{
    delete ui;
}

/*******************************************************************************
* Function Name :   back_default_page
* Description   :   返回默认页面
* Input         :   None
* Output        :   设置当前页面
* Return        :   None
*******************************************************************************/
void OptionPage::back_default_page(void)
{
    // 返回默认页面，设置主页面
    ui->stackedWidget->setCurrentWidget(ui->page_defalut);
}

/*******************************************************************************
* Function Name :   is_allowed_slide
* Description   :   判定页面是否可滑动
* Input         :   None
* Output        :   判定结果
* Return        :   true/false
*******************************************************************************/
bool OptionPage::is_allowed_slide(void)
{
    // 判定当前页面是否为原始设置页面，是就返回true,不是返回false
    qDebug("#####%d",ui->stackedWidget->currentIndex());
    if(ui->stackedWidget->currentIndex() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
* Function Name :   jump_setWifi_page
* Description   :   跳转至Wifi设置页面
* Input         :   None
* Output        :   跳转Wifi设置页面
* Return        :   None
*******************************************************************************/
void OptionPage::jump_setWifi_page(void)
{
    // 将设置页面stackWidget中page_setWifi指向新建时间设置页面
    SetWifiPage *widget = new SetWifiPage(ui->page_setWifi);

    // 当页面返回触发时，返回默认页面
    connect( widget, SIGNAL(signal_backDefaultPage()), this, SLOT(back_default_page()));

    // 设置当前页面
    ui->stackedWidget->setCurrentWidget(ui->page_setWifi);
}

