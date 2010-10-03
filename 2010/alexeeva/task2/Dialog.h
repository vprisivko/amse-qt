#ifndef TIMERFORM_H
#define TIMERFORM_H

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>

class Dialog : public QDialog
{

    Q_OBJECT

public:
    Dialog(QWidget * parent = 0);
    ~Dialog();

private:
    int curTmrIndx;
    int * timers_id;
    int * ticks;

	QLineEdit * editInterval;
	QLabel * labValue1;
	QLabel * labValue2;

protected:
	virtual void timerEvent(QTimerEvent *);

public slots:
    void cbChange(int);
    void stop();
    void set();
};

#endif // TIMERFORM_H
