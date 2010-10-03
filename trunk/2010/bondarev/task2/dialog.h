#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimerEvent>
#include <QTimer>

class Dialog : public QDialog
{
    Q_OBJECT;

    QLabel *lTimer1;
    QLabel *lTimer1Counter;
    QLabel *lTimer2;
    QLabel *lTimer2Counter;
    QComboBox *cmbCheckTimer;
    QLineEdit *leInterval;
    QPushButton *btnSetInterval;
    QPushButton *btnStop;
    QVBoxLayout *lMain;
    QHBoxLayout *lay1;
    QHBoxLayout *layTimer1;
    QHBoxLayout *layTimer2;

    int counterTimer1;
    int counterTimer2;
    int idTimer1;
    int idTimer2;

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void set();
    void stop();
    void timerEvent(QTimerEvent *e);
};

#endif // _DIALOG_H_
