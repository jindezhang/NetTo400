/**************************************************************************
 *
 * file main.cpp
 * brief Short description:
 * Detailed description:
 *
 *
 * date 2018-10-31
 * author RD330
 *
**************************************************************************/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
