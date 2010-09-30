#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui/QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>


class Dialog : public QDialog
{
    Q_OBJECT

private:
    QLabel *firstTimerTextLabel;
    QLabel *secondTimerTextLabel;
    QLabel *firstTimerNumberLabel;
    QLabel *secondTimerNumberLabel;
    QComboBox *changeTimerComboBox;
    QLineEdit *intervalLineEdit;
    QPushButton *setButton;
    QPushButton *stopButton;

    int firstTimerId;
    int secondTimerId;
    int firstTimerCounter;
    int secondTimerCounter;

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void timerEvent(QTimerEvent *e);
    void setTimer();
    void stopTimer();
};

#endif // DIALOG_H
