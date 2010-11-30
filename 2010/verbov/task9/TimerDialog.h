#ifndef TIMERDIALOG_H
#define TIMERDIALOG_H

#include <QtGui/QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "TimerThread.h"

class TimerDialog : public QDialog {
    Q_OBJECT

public:
    TimerDialog(QWidget *parent = 0);
    ~TimerDialog();
    void timerEvent(QTimerEvent *);

public slots:
    void setTimer();
    void stopTimer();

private:
    void terminateCurrentThread();

private:
    QLabel *myFirstTimerLabel, *mySecondTimerLabel;
    QPushButton *mySetButton, *myStopButton;
    QLineEdit *myTimerIntervalLineEdit;
    QComboBox *myTimersList;
    TimerThread myFirstThread, mySecondThread;
    int myFirstTimerValue, mySecondTimerValue;
    int myCurrentThread;
    QMutex *myFirstLocker, *mySecondLocker;
};

#endif // TIMERDIALOG_H
