#ifndef OPTIONPAGE_H
#define OPTIONPAGE_H

#include <QWidget>

namespace Ui
{
    class OptionPage;
}

class OptionPage : public QWidget
{
    Q_OBJECT

public:

    explicit OptionPage(QWidget *parent = 0);
    ~OptionPage(void);

private slots:

    void back_default_page(void);                                       // 返回默认界面
    void jump_setWifi_page(void);                                       // 跳转至Wifi设置页面

	public slots:

    bool is_allowed_slide(void);                                        // 是否允许滑动

private:

    Ui::OptionPage *ui;

};

#endif // OPTIONPAGE_H
