#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <QWidget>
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTimerEvent>
#include <QMutex>

#include <timer.h>
 
class Dialog : public QDialog {
    Q_OBJECT;
    
    public:
        Dialog(QWidget *parent = NULL);
        ~Dialog();
        
    public:
        virtual void timerEvent(QTimerEvent* e);

    private:
        void createConnects();
        
    private: // UI elements
        QLabel* lblTimer[2];
        QComboBox* cbChooseTimer;
        QLineEdit* leInterval;
        QPushButton* btnSet;
        QPushButton* btnStop;
        
    private:
        int countTimer[2];
        bool isTimerOn[2];

        Timer timers[2];
        QMutex mutexes[2];

        const int REFRESH_TIME;
    
    signals:
    
    public slots:
        void setTimer();
        void stopTimer();   

    signals:
        void signalStopTimer(Timer*);


};


#endif
