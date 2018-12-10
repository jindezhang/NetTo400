/**************************************************************************
 *
 * file dialogs.h
 * brief Short description:
 * Detailed description:

 *
 * date 2018-11-22
 * author RD330
 *
**************************************************************************/
#ifndef DIALOGS_H
#define DIALOGS_H

#include <QDialog>

namespace Ui {
class Dialogs;
}

class Dialogs : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogs(QWidget *parent = 0);
    ~Dialogs();

private:
    Ui::Dialogs *ui;
};

#endif // DIALOGS_H
