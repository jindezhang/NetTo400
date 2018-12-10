/**************************************************************************
 *
 * file work.h
 * brief Short description:
 * Detailed description:

            1.负责通信的初始化/断开
            2.负责发送握手指令。.,
 *
 * date 2018-11-2
 * author RD330
 *
**************************************************************************/
#ifndef WORK_H
#define WORK_H

#include <QObject>
#include "control.h"

//前置声明
class arm_control_t;
struct msg;
struct imsg_handler;

class Work : public QObject
{
    Q_OBJECT
public:
    explicit Work(QObject *parent = nullptr);
    ~Work();
    void set_(quint64 num);//设置发送的次数
    void stop();//手动停止。
    void startW();//可以运行。
    void disnet();//断开连接
    void set_cp(comm_param_t* cp);//设置串口
    void set_np(net_param_t* np);//设置网口
public slots:
    void run();//握手

    void net();//连接
signals:
    void sig_num(bool b);//握手情况信号
    void sig_init(bool b);//初始化连接情况信号


private:
    arm_control_t* m_control;
    imsg_handler *m_imsg;
    int m_num;//发送总次数
    bool m_stop;
    net_param_t* m_np;
    comm_param_t* m_cp;
};

#endif // WORK_H
