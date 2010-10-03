#ifndef TIMERDIALOG_H
#define TIMERDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QLCDNumber>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

class TimerDialog : public QDialog {
    Q_OBJECT;

private:
    int myTimerId1,myTimerId2;
    QLabel *label1;
    QLabel *label2;
    QLCDNumber *number1;
    QLCDNumber *number2;
    QComboBox *myBox;
    QLineEdit *intervalEdit;
    QPushButton *setButton;
    QPushButton *stopButton;

public:
    TimerDialog(QDialog *parent = 0);
    void timerEvent(QTimerEvent *);

public slots:
    void stopPressed();
    void setPressed();

};

#endif // TIMERDIALOG_H
