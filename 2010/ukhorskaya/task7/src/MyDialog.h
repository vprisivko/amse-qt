#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QtGui/QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>


class MyDialog : public QDialog
{
    Q_OBJECT

private:
    QLabel *firstTimerTextLabel;
    QLabel *secondTimerTextLabel;
    QLabel *firstTimerNumberLabel;
    QLabel *secondTimerNumberLabel;


    QPushButton *stopButton;

public:
    QLineEdit *intervalLineEdit;
    QPushButton *setButton;
    QComboBox *changeTimerComboBox;

    int firstTimerPeriod;
    int secondTimerPeriod;

private:

    int firstTimerId;
    int secondTimerId;
    int firstTimerCounter;
    int secondTimerCounter;   

public:
    MyDialog(QWidget *parent = 0);
    ~MyDialog();

public slots:
    void timerEvent(QTimerEvent *e);
    void setTimer();
    void stopTimer();
};

#endif // MYDIALOG_H
