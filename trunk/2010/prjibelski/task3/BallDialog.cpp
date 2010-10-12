#include "BallDialog.h"

BallDialog::BallDialog(double r, double vx_, double vy_, double ax_, double ay_, double x_, double y_) {
    radius = r;
    x = x_;
    y = y_;
    vx = vx_;
    vy = vy_;
    ax = ax_;
    ay = ay_;
    rx = r;
    ry =  r;

    compDirectionX = 0;
    compDirectionY = 0;

    this->setWindowTitle( "Ball bouncer" );

    ballPainter = new QPainter();
    ballTimer = new QTimer( this );
    connect( ballTimer, SIGNAL( timeout() ), this, SLOT( timeEvent()) );
    ballTimer->start( 20 );

}

void BallDialog::paintEvent( QPaintEvent * ) {
    ballPainter->begin( this );
    QBrush * ballBrush = new QBrush( Qt::yellow, Qt::SolidPattern );
    ballPainter->setBrush( *ballBrush );
    ballPainter->setPen( Qt::red );

    ballPainter->drawEllipse( (int) (x-rx), (int) (y-ry), (int) (2*rx), (int) (2*ry) );
    ballPainter->end();
}

void BallDialog::timeEvent() {
    vx += ax;
    vy += ay;

    //Horizonatal case
    if ( compDirectionX == 0 ) {
         moveBall(x, rx, vx > 0 ? (double) this->width() : 0.0, vx, compDirectionX );
    }
    else {
         if ( ( compDirectionX == 1 ) && ( (vx - ax) * vx < 0 ) ) {
               compDirectionX = -1;
         }
         int compDirectionXT = compDirectionX;
         compressBall( x, rx, compDirectionX > 0 ? radius/2.0 : radius, vx, compDirectionX);
         vx = (compDirectionX == -compDirectionXT) ? -vx : vx;
    }

    //Vertical case
    if ( compDirectionY == 0 ) {
         moveBall(y, ry, vy > 0 ? this->height() : 0, vy, compDirectionY );
    }
    else {
         if ( ( compDirectionY == 1 ) && ( (vy - ay) * vy < 0 ) ) {
               compDirectionY = -1;
         }
         int compDirectionYT = compDirectionY;
         compressBall( y, ry, compDirectionY > 0 ? radius/2.0 : radius, vy, compDirectionY);
         vy = (compDirectionY == -compDirectionYT) ? -vy : vy;
    }

    repaint();
}


void BallDialog::moveBall( double & coord, double & rad, double limit, double & speed, int & compDirection ) {
    int direction = speed > 0 ? 1 : -1;
    double newCoord = coord + direction * rad + speed;

    if ( direction * newCoord > direction * limit ) {
         coord = limit - direction * radius;
         compDirection = 1;
         compressBall( coord, rad, radius/2.0, speed - (newCoord - limit), compDirection );
         speed = compDirection > 0 ? speed : -speed;
    }
    else {
        coord += speed;
    }
}


void BallDialog::compressBall( double & coord, double & rad, double radLimit, double speed, int & compDirection ) {
    int direction = speed > 0 ? 1 : -1;
    double newRad = rad - compDirection * direction * speed/2.0;

    if ( compDirection * newRad < compDirection * radLimit ) {
         rad = radLimit;
         if ( compDirection == 1 ) {
              coord += speed/2.0 - 2.0 * direction * (radLimit - newRad);
              rad += (radLimit - newRad);
              compDirection = -1;
         } 
         else {
              compDirection = 0;
              coord += speed/2.0;
         }
    }
    else {
        rad = newRad;
        coord += speed/2.0;
    }
}
