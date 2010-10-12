/* 
 * File:   BallDialog.h
 * Author: andrey
 *
 * Created on October 10, 2010, 4:42 PM
 */


#ifndef BALLDIALOG_H
#define	BALLDIALOG_H

#include <QtGui/QPushButton>
#include <QtGui/QDialog>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QLabel>
#include <QtCore/QTimerEvent>
#include <QtCore/QTimer>

class BallDialog: public QDialog {
    Q_OBJECT;

public:
    double radius;
    int compDirectionX;
    int compDirectionY;
    double x, y;
    double vx, vy;
    double ax, ay;
    double rx, ry;

    QPainter * ballPainter;
    QTimer * ballTimer;

    BallDialog(double r = 20.0, double vx_ = 0.0, double vy_ = 0.8, double ax_ = 0.008, double ay_ = 0.2, double x_ = 40.0, double y_ = 20.0 );

    void paintEvent( QPaintEvent * );
    void moveBall( double & coord, double & rad, double limit, double & speed, int & compDirection );
    void compressBall( double & coord, double & rad, double radLimit, double speed, int & compDirection );

public slots:
    void timeEvent();

    
};


#endif	/* BALLDIALOG_H */

