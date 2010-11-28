#ifndef TIMERDIALOG_H
#define TIMERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimerEvent>
#include <QIntValidator>

#include <QDebug>

#include "Timer.h"

class TimerDialog : public QDialog{
    Q_OBJECT;
private:
    QPushButton *mySetButton;
    QPushButton *myStopButton;
    QLabel *myTimer1ValueLabel;
    QLabel *myTimer2ValueLabel;
    QComboBox *myComboBox;
    QLineEdit *myIntervalInput;
    Timer *myTimer1;
    Timer *myTimer2;
public:
    TimerDialog(QWidget *parent = 0);
    ~TimerDialog();
private:
    void restartTimer(Timer*, int interval, int startValue);
    void stopTimer(Timer*);
    void timerEvent(QTimerEvent *e);
public slots:
	void Set();
	void Stop();
};

#endif // TIMERDIALOG_H
