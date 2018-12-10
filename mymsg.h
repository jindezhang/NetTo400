/**************************************************************************
 *
 * file mymsg.h
 * brief Short description:
 * Detailed description:

 *
 * date 2018-11-2
 * author RD330
 *
**************************************************************************/
#ifndef MYMSG_H
#define MYMSG_H

#include "msg.h"
#include "mainwindow.h"
#include <QCoreApplication>
#include <QDebug>
#include "header.h"

//【遗弃】 存在：msg_common_t
//struct msg : msg_t
//{
//    unsigned type(void) const{
//        return ;
//    }
//};

struct msg_observer :public msg_observer_t{
//    QObject *object;
    void process( msg_t* msg ){
        QEvent::Type et;
        //在tcp 和串口模式下都适应。
        if(msg->type() == unsigned(msg_type_t::transport_offline)){
            et = QEvent::Type(TRANSPORT_OFFLINE);
        }
        if(msg->type() == unsigned(msg_type_t::transport_reconnected)){
            et = QEvent::Type(TRANSPORT_RECONNECTED);
        }
        QEvent *e = new QEvent(et);

        QCoreApplication::postEvent(MainWindow::get_window(), e);
    }
};

struct imsg_handler : imsg_handler_t
{
    imsg_handler(std::shared_ptr< msg_observer > observer):m_observer(observer){}
    void post_msg(std::unique_ptr<msg_t> msg){
        m_observer->process(msg.get());
    }
private:
    std::shared_ptr< msg_observer > m_observer;
};

#endif // MYMSG_H
