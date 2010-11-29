#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "timer.h"
#include <QDialog>
#include <QTimerEvent>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMutex>

class Dialog : public QDialog{
    Q_OBJECT;

    public:
        Dialog(QWidget *parent = 0);
        ~Dialog();

    public slots:
        void setTimer();
        void stopTimer();
        void timerEvent(QTimerEvent*);

    signals:
        void stopTimerSignal(Timer*);

    private:
        int timerCounters[2];
        Timer timers[2];
        QMutex mutexes[2];
        const int DELAY;

        QLabel *timerLabels[2];
        QComboBox *timersComboBox;
        QLineEdit *setIntervalLineEdit;
        QPushButton *setButton;
        QPushButton *stopButton;
        QVBoxLayout *mainLayout;
        QHBoxLayout *setIntervalLayout;
        QHBoxLayout *firstLabelLayout;
        QHBoxLayout *secondLabelLayout;
};

#endif


