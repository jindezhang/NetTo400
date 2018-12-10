/**************************************************************************
 *
 * file serial.cpp
 * brief Short description:
 * Detailed description:
 *
 *
 * date 2018-10-31
 * author RD330
 *
**************************************************************************/
#include "serial.h"
#include "ui_serial.h"
#include <qt_windows.h>
#include <QSettings>

Serial::Serial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Serial)
{
    ui->setupUi(this);

    //init
    QStringList list;
    list = get_Comm();
    if(list.size() == 0)
        list<<"no valid comm";
    ui->comboBox->addItems(list);
    list.clear();
    list<<"110   ";
    list<<"300   ";
    list<<"600   ";
    list<<"1200  ";
    list<<"2400  ";
    list<<"4800  ";
    list<<"9600  ";
    list<<"14400 ";
    list<<"19200 ";
    list<<"38400 ";
    list<<"56000 ";
    list<<"57600 ";
    list<<"115200";
    list<<"128000";
    list<<"256000";
    ui->comboBox_2->addItems(list);
    list.clear();

//    1. even 每个字节传送整个过程中bit为1的个数是偶数个（校验位调整个数）

//    2. odd 每个字节穿送整个过程中bit为1的个数是奇数个（校验位调整个数）

//    3. noparity没有校验位

//    4. space 校验位总为0

//    5. mark 校验位总为


    parity<<"NOPARITY   ";
    parity<<"ODDPARITY  ";
    parity<<"EVENPARITY ";
    parity<<"MARKPARITY ";
    parity<<"SPACEPARITY";

//    无校验
//    奇校验
//    偶校验
//    校验置位
//    校验清零



    ui->comboBox_3->addItems(parity);
    list.clear();


    list<<"5";
    list<<"6";
    list<<"7";
    list<<"8";
    ui->comboBox_4->addItems(list);
    list.clear();


    list<<"ONESTOPBIT   ";
    list<<"ONE5STOPBITS ";
    list<<"TWOSTOPBITS  ";
    ui->comboBox_5->addItems(list);

    //default
    ui->comboBox->setCurrentIndex(2);
    ui->comboBox_4->setCurrentIndex(3);
    ui->comboBox_2->setCurrentIndex(8);

    ui->comboBox_2->setEnabled(false);
    ui->comboBox_3->setEnabled(false);
    ui->comboBox_4->setEnabled(false);
    ui->comboBox_5->setEnabled(false);
}

Serial::~Serial()
{
    delete ui;
}
#include <QDebug>

QStringList Serial::get_Value()
{
    QStringList list;
    list<<ui->comboBox->currentText();
    list<<ui->comboBox_2->currentText();
    list<<ui->comboBox_3->currentText();
    list<<ui->comboBox_4->currentText();
    list<<ui->comboBox_5->currentText();

//    qDebug()<<list;
    return list;
}

void Serial::set_Enable(bool b)
{
    ui->comboBox->setEnabled(b);
    ui->comboBox_2->setEnabled(b);
    ui->comboBox_3->setEnabled(b);
    ui->comboBox_4->setEnabled(b);
    ui->comboBox_5->setEnabled(b);
}

QStringList Serial::get_Comm()
{
    QStringList comm;
    comm.clear();
        ///*获取串口号相关
    //    QStringList m_listcomboName;
        HKEY hKey;
    //    LPCWSTR subkey;
        wchar_t keyname[256]; //键名数组
        char keyvalue[256];  //键值数组
        DWORD keysize,type,valuesize;
        int indexnum;
        ///*获取串口号相关
        QString  keyorvalue = "value";
        QString path="HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
        QSettings * settings = new QSettings(path,QSettings::NativeFormat);
        QStringList key = settings->allKeys();
        int num=(int)key.size();

        if(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"),0,KEY_READ,&hKey)!=0)
        {
            QString error="Cannotopenregedit!";//无法打开注册表时返回error
            comm<<error;
            return comm;
        }//if(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,subkey,0,KEY_READ,&hKey)!=0)

        for(int index=0;index<num;index++){
            QString commresult;

            QString keymessage;//键名
            QString message;
            QString valuemessage;//键值
            indexnum = index;//要读取键值的索引号
            keysize = sizeof(keyname);
            valuesize = sizeof(keyvalue);
            if(::RegEnumValue(hKey,indexnum,keyname,&keysize,0,&type,(BYTE*)keyvalue,&valuesize)==0)//列举键名和值
            {
                for(int i=0;i<keysize;i++)
                {
                    message = keyname[i];
                    keymessage.append(message);
                }//for(inti=0;i<=keysize;i++)    读取键名
                for(int j=0;j<valuesize;j++)
                {
                    if(keyvalue[j]!=0x00)
                    {
                        valuemessage.append(keyvalue[j]);
                    }
                }//for(intj=0;j<valuesize;j++)读取键值
                if(keyorvalue=="key")
                {
                    commresult=keymessage;
                }
                if(keyorvalue=="value")
                {
                    commresult=valuemessage;
                }
            }
            else
            {
                commresult="nokey";
            }//if(::RegEnumValue(hKey,indexnum,keyname,&keysize,0,&type,(BYTE*)keyvalue,&valuesize)==0)列举键名和值
            comm<<commresult;

        }
        ::RegCloseKey(hKey);//关闭注册表
        return comm;

}

void Serial::show()
{
    ui->comboBox->clear();
    QStringList list;
    list = get_Comm();
    if(list.size() == 0)
        list<<"no valid comm";
    ui->comboBox->addItems(list);

    QWidget::show();

}
