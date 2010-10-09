#include"ball.h"
#include<QDebug>
BallDialog ::BallDialog( int _rad, int _vx, int _vy ){
    xradius = _rad;
    yradius = _rad;
    radius = _rad;
    compressionx = 0;
    compressiony = 0;
    vx = _vx;
    vy = _vy;
    p = new QPainter();
    bTimer = new QTimer(this);
    connect( bTimer, SIGNAL(timeout()), this, SLOT( timeEvent()) );
    bTimer->start( 60 );
    x = 0;
    y = 0;
}

void BallDialog::paintEvent( QPaintEvent * ) {
    p->begin( this );
    p->setBrush( Qt::SolidPattern );
    p->setPen( Qt::green );
    int x1, y1, x2, y2;
    this->geometry().getCoords( &x1, &y1, &x2, &y2);
    p->drawEllipse( QPoint( x + 0.5 * ( x2 - x1 ), y + 0.5 * ( y2 - y1 ) ), xradius, yradius);
    p->end();
}

void BallDialog::timeEvent() {
    if( compressionx == 0 && compressiony == 0 ) {
     if( ( x + xradius + vx ) >= this->width()/2  || ( x - xradius + vx ) <= -this->width()/2) {
        compressionx = 1; //need to press. if compress ==-1 -> need to unpress//
     }
     else if( ( y + yradius + vy) >= this->height()/2 || ( y - yradius + vy) <= -this->height()/2) {
        compressiony = 1;
     }
     else{
     x += vx;
     y += vy;
    }
    }
    else {
        int ax = 1 ? compressionx !=0 : 2;
        press( ax);
        x += vx;
        y += vy;
    }
    repaint();
}

void BallDialog :: press( int axes ) {
    if( axes ==1 ) {
        if( compressionx == 1 && xradius > radius/2 ) {
            xradius -= abs(vx);
        }
        else if( compressionx == 1 && xradius <= radius/2 ) {
            compressionx = -1;
            vx = -vx;
        }
        else if( compressionx == -1 && xradius < radius)  {
            xradius += abs( vx );
        }
        else {
            compressionx = 0;
        }
    }
    else {
        if( compressiony == 1 && yradius > radius/2 ) {
            yradius -= abs(vy);
        }
        else if( compressiony == 1 && yradius <= radius/2) {
            compressiony = -1;
            vy = -vy;
        }
        else if( compressiony == -1 && yradius < radius) {
            yradius += abs(vy);
        }
        else {
            compressiony = 0;
        }
    }
}
