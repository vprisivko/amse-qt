#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <QWidget>
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTimerEvent>

 
class Dialog : public QDialog {
    Q_OBJECT;
    
    public:
        Dialog(QWidget *parent = NULL);
        
    public:
        virtual void timerEvent(QTimerEvent* e);
        
    private: // UI elements
        QLabel* lblTimer[2];
        QComboBox* cbChooseTimer;
        QLineEdit* leInterval;
        QPushButton* btnSet;
        QPushButton* btnStop;
        
    private:
        int countTimer[2];
        int timerId[2];
        bool isTimerOn[2];
    
    signals:
    
    public slots:
        void setTimer();
        void stopTimer();

    friend class TimerDialogTest;

};


#endif
