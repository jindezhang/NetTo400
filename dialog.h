/**************************************************************************
 *
 * file dialog.h
 * brief Short description:
 * Detailed description:

 *
 * date 2018-11-22
 * author RD330
 *
**************************************************************************/
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>

inline QWidget* init_Shade( QWidget *parent)
{
    QWidget * mpShadeWindow = new QWidget(parent);
    QString str("QWidget{background-color:rgba(0,0,0,0.6);}");
    mpShadeWindow->setStyleSheet(str);
    mpShadeWindow->setGeometry(0, 0, parent->width(), parent->height());
    mpShadeWindow->hide();
    return mpShadeWindow;
}

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    int exec(QWidget *parent);
    void hide();
private slots:
    void run();
private:
    Ui::Dialog *ui;
    QTimer *t;
    QWidget *m_shade;
};

#endif // DIALOG_H
