/**************************************************************************
 *
 * file header.h
 * brief Short description:
 * Detailed description:

 *
 * date 2018-11-26
 * author RD330
 *
**************************************************************************/
#ifndef HEADER_H
#define HEADER_H

#include <QEvent>
//QEvent::User
//自定义宏
#define TRANSPORT_OFFLINE   QEvent::User+10          //通信断开
#define TRANSPORT_RECONNECTED     QEvent::User+11    //通信已重连


#endif // HEADER_H
