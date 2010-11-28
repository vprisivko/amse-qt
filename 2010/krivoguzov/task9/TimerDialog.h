#ifndef TIMERDIALOG_H
#define TIMERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLCDNumber>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QMutex>
#include "IntervalThread.h"

class TimerDialog : public QDialog {
    Q_OBJECT;

private:
    int myTimerId;
    int counter1, counter2;

    QLabel *label1;
    QLabel *label2;
    QLineEdit *number1;
    QLineEdit *number2;
    QComboBox *myBox;
    QLineEdit *intervalEdit;
    QPushButton *setButton;
    QPushButton *stopButton;

    QMutex *mutex;
    IntervalThread *firstThread, *secondThread;

public:
    TimerDialog(QDialog *parent = 0);
    void timerEvent(QTimerEvent *);

public slots:
    void stopPressed();
    void setPressed();

friend class MyTest;
};

#endif // TIMERDIALOG_H
