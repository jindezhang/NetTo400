/**************************************************************************
 *
 * file dialog.cpp
 * brief Short description:
 * Detailed description:

 *
 * date 2018-11-22
 * author RD330
 *
**************************************************************************/
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    t = new QTimer;
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//窗体无边框，无法移动。
    connect(t, SIGNAL(timeout()), this, SLOT(run()));

    m_shade = init_Shade(parent);

}

Dialog::~Dialog()
{
    delete t;
    delete m_shade;
    delete ui;

}

int Dialog::exec(QWidget *parent)
{
    ui->progressBar->setValue(0);
    t->start(500);
    m_shade->setGeometry(0, 0, parent->width(), parent->height());
    m_shade->show();
    return QDialog::exec();
}

void Dialog::hide()
{
    t->stop();
    m_shade->hide();
    return QDialog::hide();
}
#include <QDebug>
void Dialog::run()
{
    int value = ui->progressBar->value();
    if(value >= 97){
        return;
    }
    value++;
//    qDebug()<<"Dialog::run():"<<value;
    ui->progressBar->setValue(value);
}
