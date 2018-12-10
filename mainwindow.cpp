/**************************************************************************
 *
 * file mainwindow.cpp
 * brief Short description:通信调试助手，支持网络和串口通信
 * Detailed description:
 *          与400进行通信调试。
 *          实现手段：异步事件机制。
 *
 *
 * date 2018-10-31
 * author RD330
 *
**************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include "serial.h"
#include "tcp.h"
#include "control.h"
#include "mymsg.h"

#include <log4cxx/logger.h>

#include <log4cxx/propertyconfigurator.h>
#include <QRegExpValidator>
#include <QRegExp>

#include <QDebug>
#include <QThread>
#include "work.h"
#include <QTimer>

MainWindow* MainWindow::main_static = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("通信调试助手 V1.4.1"));//更新了库
    ui->edit_show->setReadOnly(true);
    ui->ed_info->setReadOnly(true);


    set_Model();
    log4cxx::PropertyConfigurator::configure("ZS400log.properties");


    w = new Work();
    connect(w, SIGNAL(sig_num(bool)), this, SLOT(update_(bool)));//握手
    connect(w, SIGNAL(sig_init(bool)),this, SLOT(slot_con(bool)));//连接

    //线程
    th = new QThread(this);
    w->moveToThread(th);
    connect(this, SIGNAL(startRun()), w, SLOT(run()));//主线程握手信号
    connect(this, SIGNAL(startNet()), w, SLOT(net()));//主线程连接信号
    th->start();

    //延时提前断开连接的bug
    t = new QTimer();
    connect(t,SIGNAL(timeout()), this, SLOT(end()));

    ui->ed_num->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->ed_num_2->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));

    //新版本
    ui->pushButton->hide();

    set_bt(true);
    ui->progressBar->setMaximum(100);//设置进度条最大值。设置为100，到时候的值则是：curr * 100 / tatol;改：(num1*tatol1+num2)*100 / (tatol1+tatol2)
    connect(this, SIGNAL(next()), this, SLOT(send_clicked()));//连接成功之后，才会发送。

    m_dialog = new Dialog(this);
    m_np = new net_param_t;
    m_cp = new comm_param_t;
    ui->bt_sreach->hide();

    main_static = this;



}

MainWindow::~MainWindow()
{
//    释放资源。
//    disconnect(th, SIGNAL(started()), w, SLOT(run()));
    disconnect(th, SIGNAL(finished()), w, SLOT(deleteLater()));
    if(th){
        if(th->isRunning()){
            th->quit();
            th->wait();
        }
        delete th;
        th = nullptr;
        qDebug()<<"~th";
    }
    if(w){
        delete w;
        w = nullptr;
        qDebug()<<"~w";
    }
    delete m_np,m_cp;
    delete m_dialog;
    delete t;
    delete ui;
    qDebug()<<"~MainWindow";
}
//QObject 类型存在该方法。
bool MainWindow::event(QEvent *event)
{
    if(event->type() == (QEvent::Type)TRANSPORT_OFFLINE){
//        if(ui->cb_select->currentIndex() == 0)
//        show_Msg(tr("通信断开！"));
        return true;
    }
    if(event->type() == (QEvent::Type)TRANSPORT_RECONNECTED){
//        show_Msg(tr("通信已重连"));
        return true;
    }
    return QWidget::event(event);
}

#include <QMessageBox>
void MainWindow::on_bt_send_clicked()
{
/*

    //最大次数int的最大值：2147483647
    quint64 num = ui->ed_num->text().toLongLong();
//    qDebug()<<"num:"<<num;
    if(num <= 0){
        QMessageBox::information(this, "警告", "发送次数有效值为>0");
        return;
    }

    ui->l_num->setText("0");
    //防止在发送时候，乱编辑
//    ui->bt_send->setEnabled(false);
//    ui->ed_num->setEnabled(false);

    //如果线程未启动，那么启动线程
    if(!th->isRunning()){
        th->start();
    }
    else{
//        qDebug()<<"starting";
    }

//    connect(th,SIGNAL(finished()),this,SLOT(runOut()));
//    connect(th, SIGNAL(finished()), this, SLOT(end()));

    w->set_(num);
    w->set_Enable(m_control);
    /*
    //count = 0;
//    bool b = true;

//    do{
//        if(m_control->handshake()){
//            if(b){
//                show_Msg(tr("handshake():握手成功！"));
//                b = false;
//                th->start();
//            }
//            ui->l_num->setText(QString("%1").arg(count));
//            ui->progressBar->setValue(count++);
//            count++;
//            qDebug()<<count;

//        }
//        else{
//            show_Msg(tr("handshake():握手失败！"));
//            on_pushButton_clicked();
//            break;//握手失败，需要跳出循环。
//        }
//    }while(--num);
//    show_Msg(tr("结束时间点"));

                //释放资源。
//                disconnect(th, SIGNAL(started()), w, SLOT(run()));
//                disconnect(th, SIGNAL(finished()), w, SLOT(deleteLater()));
//                if(th){
//                    if(th->isRunning()){
//                        th->quit();
//                        th->wait();
//                    }
//                    delete th;
//                    th = nullptr;
//                    qDebug()<<"~th";
//                }

    emit startRun();
    show_Msg(tr("start...."));
//    qDebug()<<"on_bt_send_clicked";
    */
}


//void MainWindow::on_pushButton_clicked()
//{
//    qDebug()<<"on_pushButton_clicked:";
//    if(ui->cb_select->isEnabled()){
//        init_Contrl();

//        ui->progressBar->setValue(0);
//        ui->l_num->setText("0");
//    }
//    else{
//        w->stop();
////        t->start(500);
//        //立即断开
//        m_control->quit();
//        show_Msg(tr("断开连接！"));
//        set_Conn(true);
////        set_ed(false);
//    }

//}

void MainWindow::show_Msg(QString msg)
{

    QDateTime local(QDateTime::currentDateTime());
    QString localTime = QString("【%1】：%2\n%3\n").arg(local.toString("yyyy-MM-dd:hh:mm:ss.zzz")).arg(ui->cb_select->currentText()).arg(msg);
    ui->edit_show->appendPlainText(localTime);
}

void MainWindow::set_Conn(bool b)
{

    ui->cb_select->setEnabled(b);
//    ui->bt_send->setEnabled(!b);
    ui->widget->set_Enable(b);
    ui->widget_2->set_Enable(b);
    if(!b)
        ui->pushButton->setText("断开");
    else
        ui->pushButton->setText("连接");

}

void MainWindow::set_Model()
{
    if(ui->cb_select->currentIndex() == 0){

        ui->widget->show();
        ui->widget_2->hide();
    }else{

        ui->widget->hide();
        ui->widget_2->show();
    }

}

void MainWindow::init_Contrl()
{
    auto toWstring = [](std::string &str){
        std::wstring wstr(str.length(),L' ');
        std::copy(str.begin(), str.end(), wstr.begin());
        return wstr;
    };

    if(ui->cb_select->currentIndex() == 0){

        net_param_t* np = m_np;
        np->addr = ui->widget->get_Ip().toStdString();
        np->port = ui->widget->get_Port().toInt();

        w->set_np(np);
        emit startNet();
        if(ui->l_num_2->text().toLongLong() == 0)
             m_dialog->exec(this);
//        if(!m_control->init(np)){
//            show_Msg(tr("初始化网口失败！"));
//            set_ed(false);
//            //UI恢复
//            restart();
//        }
//        else{
//            show_Msg(tr("初始化成功！"));
//            set_Conn(false);

//            emit next();
////            set_ed(true);
//        }
    }else{
        comm_param_t* cp = m_cp;
        QStringList list = ui->widget_2->get_Value();
        //强转
        int i = 0;
        cp->lpszPortName = toWstring(list[i++].toStdString());
        cp->emBaudRate = (BaudRateEnum)list[i++].toInt();
        cp->emParity = (ParityEnum)list[i++].toInt();
        cp->emByteSize = (ByteSizeEnum)list[i++].toInt();
        cp->emStopBits = (StopBitsEnum)list[i++].toInt();

        w->set_cp(cp);
        emit startNet();
        if(ui->l_num_2->text().toLongLong() == 0)
            m_dialog->exec(this);
//        if(!m_control->init(cp)){
//            show_Msg(tr("初始化串口失败"));
//            set_ed(false);
//            restart();
//        }
//        else{
//            set_Conn(false);
//            show_Msg(tr("初始化成功！"));
//            emit next();
////            set_ed(true);
//        }
    }
}

//void MainWindow::set_ed(bool b)
//{
    /*
    m_stop = b;
    if(m_stop){//连接状态
//        ui->bt_connect->setText("断开");
        ui->bt_connect->setEnabled(false);
        ui->ed_num_2->setEnabled(false);
        ui->ed_num->setEnabled(false);

    }else{
        ui->bt_connect->setText("连接");
        ui->bt_connect->setEnabled(true);
        ui->ed_num_2->setEnabled(true);
        ui->ed_num_2->setEnabled(true);
    }
*/
//}

void MainWindow::work(bool b)
{
    qDebug()<<"work:";

    //失败
    if(!b){
        set_bt(true);
        w->disnet();
        return;
    }

    //成功
    quint64 num2 = ui->l_num_2->text().toLongLong();
    num2++;
    QString info = QString("第%1次发送完成...\n\n").arg(num2);
    ui->l_num_2->setText(QString("%1").arg(num2));
//    show_Msg(info);
    //断开
    w->disnet();
    //是否=max
    if(num2 == m_count_net){

        set_bt(true);
        show_Msg(tr("测试结束，结果正常。"));
        return;
    }
    //next
    //如果线程未启动，那么启动线程
    if(!th->isRunning()){
        th->start();
    }
    init_Contrl();

}

void MainWindow::on_cb_select_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    set_Model();
}

void MainWindow::on_bt_clear_clicked()
{
    ui->edit_show->clear();
    ui->edit_show->appendPlainText(tr("----欢迎使用通信调试助手----\n\n"));
}

int MainWindow::update_(bool b)
{
    quint64 num1 = ui->l_num->text().toLongLong();
    quint64 num2 = ui->l_num_2->text().toLongLong();

    quint64 total1 = m_count_send;
    quint64 total2 = m_count_net;

    num1++;
    quint64 value = (num1 + num2 *total1) *100 / (total1 * total2);
    //当相等时候，说明发送完成
    if(num1 == ui->ed_num->text().toLongLong()){
//        ui->bt_send->setEnabled(true);
//        ui->ed_num->setEnabled(true);
        ui->l_num->setText(QString("%1").arg(num1));
        ui->progressBar->setValue(value);
//        ui->progressBar->setValue((num1*100)/num_t);
//        show_Msg(tr("握手结束."));
        work(true);
        return 0;
    }

    if(b){
        if(num1 == 1){
//            show_Msg(tr("握手成功，正在重复握手...."));
        }

        ui->l_num->setText(QString("%1").arg(num1));
        ui->progressBar->setValue(value);
//        ui->progressBar->setValue((num1*100)/num_t);

    }else{
                    show_Msg(tr("测试失败！请检查通信设置，重新测试！"));
//                    on_pushButton_clicked();
//                    m_send = -1;
                    work(false);
                    return -1;
    }
//    m_send = 1;
    return 1;

}

void MainWindow::end()
{
    w->disnet();
    t->stop();
    set_bt(true);

}

//void MainWindow::runOut()
//{
////    qDebug()<<"runOut()";
//}

void MainWindow::enAble()
{
    /*
    m_stop = !m_stop;
    if(m_stop){//连接状态
        ui->bt_stop->setEnabled(true);
//        ui->bt_connect->setText("断开");
        ui->bt_connect->setEnabled(false);
        ui->ed_num_2->setEnabled(false);
        ui->ed_num->setEnabled(false);

    }else{
        on_pushButton_clicked();//断开
        ui->bt_stop->setEnabled(false);
        ui->bt_connect->setText("连接");
        ui->bt_connect->setEnabled(true);
        ui->ed_num_2->setEnabled(true);
        ui->ed_num->setEnabled(true);
    }
    */
}

void MainWindow::on_bt_connect_clicked()
{
    m_count_net = ui->ed_num_2->text().toLongLong();
    m_count_send = ui->ed_num->text().toLongLong();

    if(m_count_net <= 0 || m_count_send <= 0){
         QMessageBox::information(this, "警告", "输入次数有效值为大于0");
        return;
    }
    ui->l_num_2->setText(tr("0"));
    set_bt(false);

    //如果线程未启动，那么启动线程
    if(!th->isRunning()){
        th->start();
    }
    w->startW();
    init_Contrl();
/*
//    //第一次的时候，m_stop = false；
//    enAble();  //转移到连接发送的时候
//    //再次的情况

//    if(!m_stop){
//        return;
//    }
//    ui->progressBar->setValue(0);
//    m_send = ui->ed_num_2->text().toInt();
//    if(m_send<=0){
//        return;
//    }
//    m_send--;
//    ui->l_num_2->setText(tr("0"));
//    on_pushButton_clicked();



    auto toWstring = [](std::string &str){
        std::wstring wstr(str.length(),L' ');
        std::copy(str.begin(), str.end(), wstr.begin());
        return wstr;
    };
    while(m_send--){

        comm_param_t cp;
        QStringList list = ui->widget_2->get_Value();
        //强转
        int i = 0;
        cp.lpszPortName = toWstring(list[i++].toStdString());
        cp.emBaudRate = (BaudRateEnum)list[i++].toInt();
        cp.emParity = (ParityEnum)list[i++].toInt();
        cp.emByteSize = (ByteSizeEnum)list[i++].toInt();
        cp.emStopBits = (StopBitsEnum)list[i++].toInt();
        if(!m_control->init(cp)){
            show_Msg(tr("初始化串口失败"));
            set_ed(false);
        }
        else{
            set_Conn(false);
            show_Msg(tr("初始化成功！"));
            set_ed(true);
        }

       m_control->quit();
    }
    */
}

void MainWindow::restart()
{
    ui->bt_connect->setEnabled(true);
//    m_stop = false;
    ui->ed_num->setEnabled(true);
    ui->ed_num_2->setEnabled(true);
    ui->bt_stop->setEnabled(false);
}

void MainWindow::on_bt_stop_clicked()
{
    ui->bt_stop->setEnabled(false);

    w->stop();
    t->start(500);

    show_Msg(tr("已停止！"));
//    set_Conn(true);

}

void MainWindow::slot_con(bool b)
{
    if(b){
//        show_Msg(tr("初始化成功！"));
        if(ui->l_num_2->text().toLongLong() == 0)
             m_dialog->hide();
        //next
        emit next();
    }else{
        show_Msg(tr("初始化失败，请确认设置等是否正确！"));
        set_bt(true);
        if(ui->l_num_2->text().toLongLong() == 0)
            m_dialog->hide();
    }
}

void MainWindow::set_bt(bool b)
{
    ui->bt_connect->setEnabled(b);
    ui->bt_stop->setEnabled(!b);

}

void MainWindow::send_clicked()
{
    ui->l_num->setText("0");
    w->set_(m_count_send);
    emit startRun();
//    show_Msg(tr("握手开始....."));
}


void MainWindow::on_bt_sreach_clicked()
{
    ui->edit_show->find(tr("第1次"), QTextDocument::FindBackward);
}
