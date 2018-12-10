/**************************************************************************
 *
 * file mainwindow.h
 * brief Short description:通信调试助手，支持网络和串口通信
 * Detailed description:
 *          与400进行通信，支持网络和串口两种，同时支持错误信息提示。
            【1】2018年11月21日13点32分
            改为可以设置连接次数的
            设计思路：
            1.增加获取连接次数输入框
            2.增加停止按钮，修改发送按钮，隐藏连接按钮。
            修改进度条的setValue();
            发送按钮功能改:连接->发送
            发送线程响应槽函数：
                    if(发送失败)
                        断开
                     else
                        if(连接次数完成）
                            断开
                         else
                            连接
                            发送
            【2】2018年11月22日14点11分
            1.把初始化/连接等操作都放到线程。
            2.重构代码。

 * date 2018-10-31
 * author RD330
 *
**************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#pragma execution_character_set("utf-8")

namespace Ui {
class MainWindow;
}
#include <QTimer>
//前置声明
class arm_control_t;
struct imsg_handler;
struct net_param_t;
struct comm_param_t;
class QThread;
class Work;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow* get_window(){
        return main_static;
    }

    bool event(QEvent *event);//事件机制
private slots:
    void on_cb_select_currentIndexChanged(int index);//选择不同的模式
    void on_bt_clear_clicked();//请屏
    int update_(bool b);//得到握手情况。-1 失败， 0 成功完成， 1 正在发送
    void end();//手动停止的槽函数
    void on_bt_connect_clicked();//开始bt
    void on_bt_stop_clicked();//停止bt
    void slot_con(bool b);//响应连接情况的槽函数
    void set_bt(bool b);//两个功能按钮的问题
    void send_clicked();//开始发送

    void on_bt_send_clicked();//发送 【遗弃】
    //    void runOut();
    void enAble();//【遗弃】
    //    void on_pushButton_clicked();//连接
    void restart();//初始化失败之后，恢复【遗弃】
    void on_bt_sreach_clicked();

signals:
    void next();//发送按钮，连接成功后下一步；
    void startRun();
    void startNet();


private:

    void show_Msg(QString msg);//显示消息
    void work(bool b);//每次连接时候，握手情况的处理函数
    void set_Model();//不同的模式显示不同的内容
    void init_Contrl();//初始化通信端。

//    void set_ed(bool b);//【遗弃】
    void set_Conn(bool b);//设置连接状态。【遗弃】

private:
    Ui::MainWindow *ui;
//    arm_control_t* m_control;
//    imsg_handler *m_imsg;
//    int count;
//    QThread *th;
    Work *w;
    QTimer *t;
    QThread* th;
//    bool m_stop;//停止标志位.//true 表示第一次点击连接/false 表示断开连接。
//    int m_send;//发送标志位；
    quint64 m_count_net;//连接次数
    quint64 m_count_send;//握手次数
    Dialog *m_dialog;
    net_param_t* m_np;
    comm_param_t* m_cp;
//    quint64 m_start;//开始时间点的行数
    static MainWindow * main_static;
};

#endif // MAINWINDOW_H
