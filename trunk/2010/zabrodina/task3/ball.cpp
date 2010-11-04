#include"ball.h"
#include<QDebug>
BallDialog ::BallDialog( int _rad, int _vx, int _vy ){
    xradius = _rad;
    yradius = _rad;
    radius = _rad;
    setMinimumSize(4*radius,4*radius);
    vx = _vx;
    vy = _vy;
    p = new QPainter();
    bTimer = new QTimer(this);
    connect( bTimer, SIGNAL(timeout()), this, SLOT( timeEvent()) );
    bTimer->start( 20 );
    x = width()/2;
    y = height()/2;
}
bool BallDialog::isOutOfRange(){
    if((x - xradius) < 0 || (x + xradius) > width() || (y - yradius) < 0 || (y + yradius) > height()) {
        return true;
    }
    return false;
}

void BallDialog::paintEvent( QPaintEvent *) {

    p->begin( this );
    p->setBrush( Qt::SolidPattern );
    p->setPen( Qt::green );
    if(isOutOfRange())
    {
     x =  x = width()/2;
     y = height()/2;
    }
    p->drawEllipse( QPoint( x,y ), xradius, yradius);
    p->end();

}

void BallDialog::timeEvent() {
    /*
     We need to remember all parameters (width, height, current coordinates of the ball),
     because our dialog can be resized&moved during this method
    */
    int w = width();
    int h = height();
    int xx = x;
    int yy = y;
     xx += vx;
     yy += vy;

     int xCurrentRadius = radius;
     int yCurrebtRadius = radius;

     if ( xx + radius > w){
       xCurrentRadius = w - xx;
     }

     if ( xx - radius < 0){
       xCurrentRadius = xx;
     }

     if ( yy + radius > h){
       yCurrebtRadius = h - yy;
     }

     if ( yy - radius < 0){
       yCurrebtRadius = yy;
     }
     if ( xCurrentRadius < radius/2){
       vx= -vx;
     }
     if ( yCurrebtRadius < radius/2){
       vy = -vy;
     }

     x=xx;
     y=yy;
     xradius = xCurrentRadius;
     yradius = yCurrebtRadius;

    repaint();

}



