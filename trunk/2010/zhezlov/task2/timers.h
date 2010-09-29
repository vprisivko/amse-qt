#ifndef TIMERS_H
#define TIMERS_H


#include <QDialog>
#include <QLabel>
#include <QEvent>
#include <QLineEdit>


class Timers : public QDialog
{
    Q_OBJECT;

public:
    Timers(QWidget *parent = 0);
    ~Timers();

private:
    int* timerIds;
    int curTimerIndex;
    int* ticks;
    QLabel *lab1, *lab2;
    QLineEdit *lEd;

protected:
    virtual void timerEvent( QTimerEvent* );

public slots:
    void cBoxChanged(int);
    void stopBtnClk();
    void setBtnClk();

};

#endif // TIMERS_H
