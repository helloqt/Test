#ifndef SETWIFIPAGE_H
#define SETWIFIPAGE_H

#include <QWidget>

namespace Ui
{
    class SetWifiPage;
}

class SetWifiPage : public QWidget
{
    Q_OBJECT

public:

    explicit SetWifiPage(QWidget *parent = 0);
    ~SetWifiPage(void);

private slots:

    void on_button_back_clicked(void);                                  // button_back点击事件

signals:

    void signal_backDefaultPage(void);                                  // back信号

private:

    Ui::SetWifiPage *ui;
};

#endif // SETWIFIPAGE_H
