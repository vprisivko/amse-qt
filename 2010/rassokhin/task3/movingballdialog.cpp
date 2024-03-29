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

    setMinimumWidth(100);
    setMinimumHeight(100);
}

MovingBallDialog::~MovingBallDialog() {
    delete myPainter;
}

qreal max(qreal a, qreal b) { //Strange Mood
    return (a>b)? a : b;
}
qreal abs(qreal a) {
    return (a>=0)? a : -a;
} // Strange mood end ;)

void MovingBallDialog::MyBall::process(qreal dt, QRectF borders) {
    //    //dL=(2*(R - x))//R/2<=x<=R
    //    //F=ma=kdL
    //    //a=(k/m)dL
    //    //m(Vнач**2)=k(R**2)
    //    //k = (Vнач/R)**2 * m
    //    a=(Vнач/R)**2  * (2*(R - x))  //Vнач=const для каждого отдельного удара
    //    V += adt;
    //    X += Vdt;
    if( position.x() - defR <= borders.x()) {
        if (acceleration.x()==0) k.setX(max(abs(velocity.x() / defR * 1.0f), 1.0f));
        acceleration.setX( k.x()*k.x() * 2*abs(defR - abs(borders.x() - position.x()) ) );
    } else if( position.x() + defR >= borders.width()) {
        if (acceleration.x()==0) k.setX(max(abs(velocity.x() / defR * 1.0f), 1.0f));
        acceleration.setX( -k.x()*k.x() * 2*abs(defR - abs(borders.width() - position.x() ) ) );
    } else
        acceleration.setX(0);

    if( position.y() - defR <= borders.y()) {
        if (acceleration.y()==0) k.setY(max(abs(velocity.y() / defR * 1.2f), 2.0f));
        acceleration.setY( k.y()*k.y()* 2*(defR - abs(borders.y() - position.y()) ) );
    } else if( position.y() + defR >= borders.height()) {
        if (acceleration.y()==0) k.setY(max(abs(velocity.y() / defR * 1.2f), 2.0f));
        acceleration.setY( -k.y()*k.y()* 2*(defR - abs(borders.height() - position.y() ) ) );
    } else
        acceleration.setY(0);


    velocity += acceleration*dt;
    position += velocity*dt;// + acceleration*dt*dt/2.0f;

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

    if (position.x() < borders.x()) position.setX(borders.x());
    if (position.x() > borders.width()) position.setX(borders.width());
    if (position.y() < borders.y()) position.setY(borders.y());
    if (position.y() > borders.height()) position.setY(borders.height());

}

void MovingBallDialog::processBall() {
    QTime newTime(QTime::currentTime());
    int tdiff = lastUpdateTime.msecsTo(newTime);
    qreal dt = abs(tdiff) / 1000.0f;
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
