#include "optionFrame.h"

/*******************************************************************************
* Function Name :   MyFrame
* Description   :   构造函数
* Input         :   None
* Output        :   初始化
* Return        :   None
*******************************************************************************/
OptionFrame::OptionFrame(QWidget *parent) :
    QFrame(parent)
{
}

/*******************************************************************************
* Function Name :   mousePressEvent
* Description   :   重写mousePressEvent事件,检测事件类型是不是点击了鼠标
* Input         :   QMouseEvent *event  鼠标点击事件
* Output        :   获取当前坐标
* Return        :   None
*******************************************************************************/
void OptionFrame::mousePressEvent(QMouseEvent *event)
{

    //如果单击了就触发clicked信号
    if (event->button() == Qt::LeftButton)
    {

        posPressed = event->pos();
//        emit clicked();
    }

    // 将该事件传给父类处理
    QFrame::mousePressEvent(event);
}

/*******************************************************************************
* Function Name :   mouseReleaseEvent
* Description   :   重写mouseReleaseEvent事件,检测事件类型是不是释放了鼠标
* Input         :   QMouseEvent *event  鼠标点击事件
* Output        :   触发clicked信号
* Return        :   None
*******************************************************************************/
void OptionFrame::mouseReleaseEvent(QMouseEvent *event)
{
//    //如果单击了就触发clicked信号
    if (event->button() == Qt::LeftButton)
    {
        posRelease = event->pos();
        qDebug("%d:%d",posPressed.x(),posPressed.y());
        qDebug("%d:%d",posRelease.x(),posRelease.y());
        if ((-30<(posRelease.x() - posPressed.x()))&&((posRelease.x() - posPressed.x())<30)
                &&(-30<(posRelease.y() - posPressed.y()))&&((posRelease.y() - posPressed.y())<30))
        {
//            qDebug("%d:%d",posRelease.x() - posPressed.x(),posRelease.y() - posPressed.y());
//            qDebug("$$$$$$$$$$$$$$$$$$$$$$$$$$");
            // 触发clicked信号
            emit clicked();
//            qDebug("#######################");
        }

    }

//    // 将该事件传给父类处理
    QFrame::mouseReleaseEvent(event);
}
