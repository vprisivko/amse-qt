/*
 * BallWidget.h
 *
 *  Created on: 07.10.2010
 *      Author: Korgov Kirill
 */

#ifndef BALLDIALOG_H_
#define BALLDIALOG_H_

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QTimerEvent>
#include <QPaintEvent>

class BallWidget: public QWidget
{
    Q_OBJECT;
private:
    int myBallX;
    int myBallY;
    int myTimerId;
    int myBallAbsRadius;
    int myBallXRadius;
    int myBallYRadius;
    int myBallStep;
    int myBallDx;
    int myBallDy;
    int myXSqueezeTimer;
    int myYSqueezeTimer;
    int myXSqueezeTimerStatus;
    int myYSqueezeTimerStatus;
public:
    BallWidget(QWidget * parent = 0);
    virtual ~BallWidget();
protected:
    void timerEvent(QTimerEvent *e);
    void paintEvent(QPaintEvent *e);
    void squeezeX(bool sqz);
    void squeezeY(bool sqz);
};

#endif /* BALLDIALOG_H_ */
