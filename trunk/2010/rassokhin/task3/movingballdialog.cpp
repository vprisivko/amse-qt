#include "movingballdialog.h"
#include <QtGui/QPaintEvent>

MovingBallDialog::MovingBallDialog(QWidget *parent)
    : QDialog(parent) {
    drawTimer = new QTimer(this);
    connect(drawTimer, SIGNAL(timeout()), this, SLOT(update()));
    lastUpdateTime = QTime::currentTime();
    resize(640,480);
    ball.defR = 20;
    ball.position = QPointF(width() / 2,height() / 2);
    ball.radiuses = QPointF(1,1) * ball.defR;
    ball.velocity = QPointF(63.3f,25.7);
    drawTimer->start(20);
    myPainter = new QPainter();
}

MovingBallDialog::~MovingBallDialog() {
    delete myPainter;
}

void MovingBallDialog::MyBall::process(qreal dt, QRectF borders) {
    //    //dL=(2*(R - x))//R/2<=x<=R
    //    //F=ma=kdL
    //    //a=(k/m)dL
    //    //m(Vнач**2)=k(R**2)
    //    //k/m = (Vнач/R)**2
    //    a=(Vнач/R)**2  * (2*(R - x))  //Vнач=const для каждого отдельного удара
    //    V += adt;
    //    X += Vdt;
    if( position.x() - defR <= borders.x()) {
        if (acceleration.x()==0) k.setX(velocity.x() / defR *1.2f);
        acceleration.setX( k.x()*k.x() * 2*(defR - abs(borders.x() - position.x()) ) );
    } else if( position.x() + defR >= borders.width()) {
        if (acceleration.x()==0) k.setX(velocity.x() / defR *1.2f);
        acceleration.setX( -k.x()*k.x() * 2*(defR - abs(borders.width() - position.x() ) ) );
    } else
        acceleration.setX(0);

    if( position.y() - defR <= borders.y()) {
        if (acceleration.y()==0) k.setY(velocity.y() / defR *1.2f);
        acceleration.setY( k.y()*k.y()* 2*(defR - abs(borders.y() - position.y()) ) );
    } else if( position.y() + defR >= borders.height()) {
        if (acceleration.y()==0) k.setY(velocity.y() / defR *1.2f);
        acceleration.setY( -k.y()*k.y()* 2*(defR - abs(borders.height() - position.y() ) ) );
    } else
        acceleration.setY(0);


    velocity += acceleration*dt;
    position += velocity*dt + acceleration*dt*dt/2.0f;


    if( position.x() - defR <= borders.x())
        radiuses.setX(abs(borders.x()-position.x()));
    else if( position.x() + defR >= borders.width())
        radiuses.setX(abs(borders.width()-position.x()));
    else radiuses.setX(defR);
    if( position.y() - defR <= borders.y())
        radiuses.setY(abs(borders.y()-position.y()));
    else if( position.y() + defR >= borders.height())
        radiuses.setY(abs(borders.height()-position.y()));
    else radiuses.setY(defR);

}

void MovingBallDialog::processBall() {
    QTime newTime(QTime::currentTime());
    int tdiff = lastUpdateTime.msecsTo(newTime);
    qreal dt = tdiff / 1000.0f;
    ball.process(dt,rect());
    lastUpdateTime = newTime;
}

void MovingBallDialog::paintEvent(QPaintEvent *) {
    processBall();
    myPainter->begin(this);
    myPainter->setPen(Qt::red);
    myPainter->setBrush(Qt::SolidPattern);
    myPainter->drawEllipse(ball.position,ball.radiuses.x(),ball.radiuses.y());
    myPainter->end();
}
