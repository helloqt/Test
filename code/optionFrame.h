#ifndef OPTIONFRAME_H
#define OPTIONFRAME_H

#include <QFrame>
#include <QMouseEvent>
#include <QPoint>

class OptionFrame : public QFrame
{
    Q_OBJECT

public:

    explicit OptionFrame(QWidget *parent = 0);

protected:

    virtual void mousePressEvent(QMouseEvent *event);                   // 重写mousePressEvent事件
    virtual void mouseReleaseEvent(QMouseEvent *event);                 // 重写mouseReleaseEvent事件

signals:

    void clicked(void);                                                 //自定义clicked()信号,在mousePressEvent事件发生时触发

private:
//    QPoint *posPressed, *posRelease;
    QPoint posPressed, posRelease;
//    QString l;



};

#endif // MYFRAME_H


