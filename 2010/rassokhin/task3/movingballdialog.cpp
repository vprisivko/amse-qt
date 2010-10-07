#include "movingballdialog.h"
#include <QtGui/QPaintEvent>

MovingBallDialog::MovingBallDialog(QWidget *parent)
    : QDialog(parent), defBallR(20), defBallDeformationRate(2) {
    drawTimer = new QTimer(this);
    connect(drawTimer, SIGNAL(timeout()), this, SLOT(update()));
    lastUpdateTime = QTime::currentTime();
    resize(640,480);
    ballCenterPosition = QPointF(width() / 2,height() / 2);
    ballRadiuses = QPointF(1,1) * defBallR;
    ballSpeed = QPointF(63.3f,25.7);
    drawTimer->start(20);
    myPainter = new QPainter();
}

MovingBallDialog::~MovingBallDialog() {
    delete myPainter;
}

void MovingBallDialog::processBall() {
    QTime newTime(QTime::currentTime());
    int tdiff = lastUpdateTime.msecsTo(newTime);
    QPointF delta = ballSpeed * (tdiff / 1000.0f);
    qreal x = ballCenterPosition.x();
    qreal y = ballCenterPosition.y();
    qreal rx = ballRadiuses.x();
    qreal ry = ballRadiuses.y();
    x += delta.x();
    y += delta.y();
    if( x - defBallR < 0) {
        x -= delta.x() / 2;
        rx = x;
        if( rx < defBallR / defBallDeformationRate) {
            ballSpeed.setX( abs( ballSpeed.x() ) );
            rx = defBallR / defBallDeformationRate;
        }
    }
    else if( x + defBallR > geometry().width()) {
        x -= delta.x() / 2;
        rx = (geometry().width() - x);
        if( rx < defBallR / defBallDeformationRate) {
            ballSpeed.setX( -abs( ballSpeed.x() ) );
            rx = defBallR / defBallDeformationRate;
        }
    } else rx = defBallR;

    if( y - defBallR < 0) {
        y -= delta.y() / 2;
        ry = y;
        if( ry < defBallR / defBallDeformationRate) {
            ballSpeed.setY( abs( ballSpeed.y() ) );
            ry = defBallR / defBallDeformationRate;
        }
    }
    else if( y + defBallR > geometry().height()) {
        y -= delta.y() / 2;
        ry = (geometry().height() - y);
        if( ry < defBallR / defBallDeformationRate) {
            ballSpeed.setY( -abs( ballSpeed.y() ) );
            ry = defBallR / defBallDeformationRate;
        }
    } else ry = defBallR;
    ballCenterPosition = QPointF(x,y);
    ballRadiuses = QPointF(rx,ry);

    lastUpdateTime = newTime;
}

void MovingBallDialog::paintEvent(QPaintEvent *) {
    processBall();
    myPainter->begin(this);
    myPainter->setPen(Qt::red);
    myPainter->setBrush(Qt::SolidPattern);
    myPainter->drawEllipse(ballCenterPosition,ballRadiuses.x(),ballRadiuses.y());
    myPainter->end();
}
