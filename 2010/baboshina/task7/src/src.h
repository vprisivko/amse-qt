#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTimerEvent>

class myDialog : public QDialog{
    Q_OBJECT

public:
    myDialog(QWidget* p = NULL);

    virtual void timerEvent(QTimerEvent*);

private:
    int timer_id1, timer_id2;
    bool isTimerOn1, isTimerOn2;
    int count1,count2;

    QPushButton* btnSet;
    QPushButton* btnStop;
    QLabel* lbl1;
    QLabel* lbl2;
    QLabel* lbltimer1;
    QLabel* lbltimer2;
    QLineEdit* leInt;
    QComboBox* cbChoose;

public slots:
    void set();
    void stop();

signals:
    void isSet();
    void isStop();

friend class Test;

};

#endif
