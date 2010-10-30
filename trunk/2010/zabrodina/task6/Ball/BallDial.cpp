#include"BallDial.h"
#include<QDebug>
#include<QFile>
BallDial ::BallDial(QHostAddress _ip, qint16 _port){
    //setMinimumSize(4*radius,4*radius);
    setFixedSize(600,400);
    state = new State();
    p = new QPainter();
    bTimer = new QTimer(this);
    connect( bTimer, SIGNAL(timeout()), this, SLOT( timeEvent()) );
    bTimer->start( 10 );
    socket = new QUdpSocket(this);
    ip = _ip;
    port = _port;

    if(!socket->bind(ip,port)){
         qDebug()<<"Update ip and port i file \"ip_port.txt\" \n";
         exit(-1);
    }


}

void BallDial::paintEvent( QPaintEvent *) {

    p->begin( this );
    p->setBrush( Qt::SolidPattern );
    p->setPen( Qt::green );
    QBrush *brush = new QBrush(Qt::blue, Qt::SolidPattern);
    p->drawEllipse( QPoint( state->b->x, state->b->y ), state->b->xradius, state->b->yradius);
    //QBrush *brush = new QBrush(Qt::magenta, Qt::SolidPattern);
    brush->setColor(Qt::magenta);
    p->setBrush(*brush);
    p->drawRect(state->r->xPosition, height() - state->r->heightRock, state->r->widthRock, state->r->heightRock);
    p->end();

}

void BallDial::timeEvent() {
    /*
     We need to remember all parameters (width, height, current coordinates of the ball),
     because our dialog can be resized&moved during this method
    */
    int w = width();
    int h = height();
    int xx = state->b->x;
    int yy = state->b->y;
     xx += state->b->vx;
     yy += state->b->vy;

     int xCurrentRadius = state->b->radius;
     int yCurrentRadius = state->b->radius;

     if ( xx + state->b->radius > w){
       xCurrentRadius = w - xx;
     }

     if ( xx - state->b->radius < 0){
       xCurrentRadius = xx;
     }

     if ( yy + state->b->radius > h-state->r->heightRock){
         if((xx + state->b->radius > state->r->xPosition) && (xx + state->b->radius  < state->r->xPosition + state->r->widthRock))
            yCurrentRadius = h-state->r->heightRock - yy;
         else {
             state->livesleft -= 1;
         }
     }

     if ( yy - state->b->radius < 0){
       yCurrentRadius = yy;
     }
     if ( xCurrentRadius < state->b->radius/2){
       state->b->vx= -state->b->vx;
     }
     if ( yCurrentRadius < state->b->radius/2){
       state->b->vy = -state->b->vy;
     }

     state->b->x=xx;
     state->b->y=yy;
     state->b->xradius = xCurrentRadius;
     state->b->yradius = yCurrentRadius;
    repaint();

}
