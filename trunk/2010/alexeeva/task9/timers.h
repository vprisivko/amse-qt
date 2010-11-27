#ifndef TASK2_H
#define TASK2_H

#include <QtGui/QWidget>

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "timerthread.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget * parent = 0);
    ~Dialog() {};

private:
    int index;
    int * ticks;
    TimerThread * t_threads;
    QMutex * locks;

	QLineEdit * editInterval;
	QLabel * labValue1;
	QLabel * labValue2;
	QComboBox * comboChooseTimer;

protected:
	virtual void timerEvent(QTimerEvent *);

public slots:
    void cbChange(int);
    void stop();
    void set();
};

#endif // TASK2_H
