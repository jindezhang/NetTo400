/**************************************************************************
 *
 * file work.cpp
 * brief Short description:
 * Detailed description:

 *
 * date 2018-11-2
 * author RD330
 *
**************************************************************************/
#include "work.h"
#include "control.h"
#include "mymsg.h"

Work::Work(QObject *parent) : QObject(parent)
{
    m_stop = true;
    m_np = nullptr;
    m_cp = nullptr;

//    std::unique_ptr< msg_common_t > m_msg(new msg_common_t);
    std::shared_ptr< msg_observer > observer(new msg_observer);
//    observer->object = parent;
    m_imsg = new imsg_handler(observer);
//    m_imsg->post_msg(std::move(m_msg));
    m_control = new arm_control_t(m_imsg);

}

Work::~Work()
{
    if(m_control)
        delete m_control;
    if(m_imsg)
        delete m_imsg;
}

//void Work::set_Enable(arm_control_t *control)
//{
//    m_control = control;
//}

void Work::set_(quint64 num)
{
    m_num = num;
}

void Work::stop()
{
    m_stop = false;
}

void Work::startW()
{
    m_stop = true;
}

void Work::net()
{
    //初始化cp
    if(m_cp){
        if(!m_control->init(*m_cp)){
            emit sig_init(false);
        }
        else{
            emit sig_init(true);
        }
    }
    else{
        if(!m_control->init(*m_np)){
            emit sig_init(false);
        }
        else{
            emit sig_init(true);
        }
    }
}

void Work::disnet()
{
    m_control->quit();
}

void Work::set_cp(comm_param_t* cp)
{
    m_cp = cp;
    m_np = nullptr;//保证可以选择到一种模式初始化
}

void Work::set_np(net_param_t *np)
{
    m_np = np;
    m_cp = nullptr;//保证可以选择到一种模式初始化
}

#include <QDebug>
void Work::run()
{
    qDebug()<<"run";
//    m_stop = true;
    while(m_num){
        if(!m_stop){//手动停止
            qDebug()<<"stop:";
            //emit sig_num(false);
            break;
        }
        if(m_control->handshake()){
            emit sig_num(true);
        }
        else{
            emit sig_num(false);
            break;//握手失败，需要跳出循环。
        }
        m_num--;
    }
    qDebug()<<"run out";
}
