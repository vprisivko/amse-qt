#ifndef _BALL_DIALOG_H_
#define _BALL_DIALOG_H_

#include <QWidget>
#include <QDialog>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QSize>

class BallDialog : public QDialog {
    Q_OBJECT;
    
    public:
        BallDialog(QWidget *parent = NULL);
        
    public:
        virtual void timerEvent(QTimerEvent* e);
        virtual void paintEvent(QPaintEvent* e);
    
   	private: 
            int initRadius;
            QSize curRadius;
            QPoint coord;
            int dx,dy;
            const int DEFAULT_RADIUS;
    signals:

    public slots:
		
          

};


#endif
