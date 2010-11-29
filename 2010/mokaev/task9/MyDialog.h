#ifndef _MY_DIALOG_H_
#define _MY_DIALOG_H_

#include<QDialog>
#include <QLCDNumber>
#include <QLabel>
#include <QLineEdit>
#include <QEvent>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QMutex>

#include "timer.h"

const int DEFAULT_TIMER_VALUE = 10;

class MyDialog : public QDialog{

    Q_OBJECT;
    public:
        MyDialog( QWidget* parent = NULL );
        virtual void timerEvent( QTimerEvent* );

    private:
        void createWidgets();
        void addWidgets();
        void setConnection();
        void killThreadTimer( Timer* timer );

    private slots:
        void setClick();
        void stopClick();

    private:
        Timer* timer1;
        Timer* timer2;
        QMutex* mutex1;
        QMutex* mutex2;

        int timerId;
        int count1, count2;
        bool isT1Exist, isT2Exist;

    private:
        QLCDNumber* t1Value;
        QLCDNumber* t2Value;
        QComboBox* timerComboBox;
        QLineEdit* timerEditBox;
        QPushButton* setButton;
        QPushButton* stopButton;
};

#endif
