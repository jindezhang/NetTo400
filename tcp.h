/**************************************************************************
 *
 * file tcp.h
 * brief Short description:
 * Detailed description:
 *
 *
 * date 2018-10-31
 * author RD330
 *
**************************************************************************/
#ifndef TCP_H
#define TCP_H

#include <QWidget>

namespace Ui {
class Tcp;
}

class Tcp : public QWidget
{
    Q_OBJECT

public:
    explicit Tcp(QWidget *parent = 0);
    ~Tcp();
    QString get_Ip();
    QString get_Port();
    void set_Enable(bool b);

private:
    Ui::Tcp *ui;
};

#endif // TCP_H
