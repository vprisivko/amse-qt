#ifndef TIMERS_H
#define TIMERS_H

#include <QtGui/QWidget>

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget * parent = 0);
    ~Dialog();

private:
    int index;
    int * timers;
    int * ticks;

	QLineEdit * editInterval;
	QLabel * labValue1;
	QLabel * labValue2;
	QComboBox * comboChooseTimer;
	QPushButton * buttSet;
	QPushButton * buttStop;

protected:
	virtual void timerEvent(QTimerEvent *);

public slots:
    void cbChange(int);
    void stop();
    void set();

signals:
	void isSet();

    friend class TestTimers;
};

#endif // TIMERS_H
