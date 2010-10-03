#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <QDialog>
#include <QTimerEvent>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Dialog : public QDialog{
    Q_OBJECT;

public:
    Dialog(QWidget *parent = 0);

public slots:
    void setTimer();
    void stopTimer();
    void timerEvent(QTimerEvent *e);

private:
    int firstTimeCounter;
    int secondTimeCounter;
    int firstTimer_id;
    int secondTimer_id;

    QLabel *firstLabel;
    QLabel *secondLabel;
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


