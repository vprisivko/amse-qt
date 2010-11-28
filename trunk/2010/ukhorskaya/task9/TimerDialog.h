#ifndef TIMERDIALOG_H
#define TIMERDIALOG_H

#include <QtGui/QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include "TimerThread.h"


class TimerDialog : public QDialog
{
    Q_OBJECT

private:
    QTimer *timer;
    TimerThread *timerThread1;
    TimerThread *timerThread2;

    QLabel *firstTimerTextLabel;
    QLabel *secondTimerTextLabel;
    QLabel *firstTimerNumberLabel;
    QLabel *secondTimerNumberLabel;
    QComboBox *changeTimerComboBox;
    QLineEdit *intervalLineEdit;
    QPushButton *setButton;
    QPushButton *stopButton;

    int currentTimerId;
    int firstTimerCounter;
    int secondTimerCounter;

public:
    TimerDialog(QWidget *parent = 0);
    ~TimerDialog();

public slots:
    void timerEvent();
    void setTimer();
    void stopTimer();
    void changeCurrentTimer();
};


#endif // TIMERDIALOG_H
