#include "setWifiPage.h"
#include "ui_setWifiPage.h"

/*******************************************************************************
* Function Name :   SetWifipage
* Description   :   构造函数
* Input         :   None
* Output        :   初始化
* Return        :   None
*******************************************************************************/
SetWifiPage::SetWifiPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetWifiPage)
{
    ui->setupUi(this);
    connect(ui->button_back,SIGNAL(clicked()),this,SLOT(signal_backDefaultPage()));

}

/*******************************************************************************
* Function Name :   ~SetWifiPage
* Description   :   析构函数
* Input         :   None
* Output        :   回收对象
* Return        :   None
*******************************************************************************/
SetWifiPage::~SetWifiPage(void)
{
    delete ui;
}

/*******************************************************************************
* Function Name :   on_button_back_clicked
* Description   :   触发返回信号
* Input         :   None
* Output        :   触发signal_backDefaultPage信号
* Return        :   None
*******************************************************************************/
void SetWifiPage::on_button_back_clicked(void)
{
    emit signal_backDefaultPage();
}
