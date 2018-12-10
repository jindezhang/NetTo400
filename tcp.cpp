/**************************************************************************
 *
 * file tcp.cpp
 * brief Short description:
 * Detailed description:
 *
 *
 * date 2018-10-31
 * author RD330
 *
**************************************************************************/
#include "tcp.h"
#include "ui_tcp.h"

Tcp::Tcp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tcp)
{
    ui->setupUi(this);
#ifndef QT_NO_DEBUG
    ui->ed_ip->setText(tr("127.0.0.1"));
    ui->ed_port->setText((tr("8081")));
#endif
}

Tcp::~Tcp()
{
    delete ui;
}

QString Tcp::get_Ip()
{
    return ui->ed_ip->text();
}

QString Tcp::get_Port()
{
    return ui->ed_port->text();
}

void Tcp::set_Enable(bool b)
{
    ui->ed_ip->setEnabled(b);
    ui->ed_port->setEnabled(b);
}


