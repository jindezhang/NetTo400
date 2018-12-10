/**************************************************************************
 *
 * file serial.h
 * brief Short description:
 * Detailed description:
 *
 *
 * date 2018-10-31
 * author RD330
 *
**************************************************************************/
#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>

namespace Ui {
class Serial;
}

class Serial : public QWidget
{
    Q_OBJECT

public:
    explicit Serial(QWidget *parent = 0);
    ~Serial();
    QStringList get_Value();

    void set_Enable(bool b);
    QStringList get_Comm();
    void show();
private:
    Ui::Serial *ui;
    QStringList parity;
    QStringList StopBits;
};

#endif // SERIAL_H
