#ifndef MOVINGBALLDIALOG_H
#define MOVINGBALLDIALOG_H

#include <QtGui/QDialog>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtCore/QPointF>
#include <QtGui/QPainter>

class MovingBallDialog : public QDialog {
    Q_OBJECT

public:
    MovingBallDialog(QWidget *parent = 0);
    ~MovingBallDialog();

    virtual void paintEvent(QPaintEvent *);
    void processBall();

private:
    QTimer * drawTimer;
    QPainter * myPainter;
    QTime lastUpdateTime;
    QPointF ballCenterPosition;
    qreal defBallR;
    qreal defBallDeformationRate;
    QPointF ballRadiuses;
    QPointF ballSpeed;
};

#endif // MOVINGBALLDIALOG_H
