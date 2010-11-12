#ifndef __TIMERS_DIALOG_H
#define __TIMERS_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class TimersDialog : public QDialog {
    Q_OBJECT;

public:
    TimersDialog(QWidget * parent = 0);

public slots:
    void timerEvent(QTimerEvent *event);
    void changeTimerEditLayout(int timer_number);
    void setTimerBC();
    void stopTimerBC();

public:
    int timerId1, timerId2;
    int timer1Counter, timer2Counter;
    int timer1Interval, timer2Interval;
    int nowEditTimer;
    QLabel * timer1Label;
    QLabel * timer2Label;
    QLineEdit * intervalEdit;
    QPushButton * setButton;
    QPushButton * stopButton;
    QComboBox * combo;

private:
    void generateObjects();
    void connectObjects();
};

#endif
