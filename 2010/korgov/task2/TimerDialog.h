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

class TimerDialog : public QDialog{
    Q_OBJECT;
private:
    QPushButton *mySetButton;
    QPushButton *myStopButton;
    QLabel *myTimer1ValueLabel;
    QLabel *myTimer2ValueLabel;
    QComboBox *myComboBox;
    QLineEdit *myIntervalInput;
    int myTimer1Id;
    int myTimer2Id;
    int myTimer1Value;
    int myTimer2Value;
public:
    TimerDialog(QWidget *parent = 0);
    ~TimerDialog();
private:
    void restartTimer(int &timer, int interval);
    void stopTimer(int &timer);
    void timerEvent(QTimerEvent *e);
public slots:
	void Set();
	void Stop();
};

#endif // TIMERDIALOG_H
