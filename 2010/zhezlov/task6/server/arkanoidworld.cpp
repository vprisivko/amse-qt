#include "arkanoidworld.h"
#include <QPainter>

ArkanoidWorld::ArkanoidWorld(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize( 600, 400 );

    qsrand( QTime().elapsed() );
    init();
    livesRemaining = 2;

}

void ArkanoidWorld::paintEvent(QPaintEvent *e){

    QRect rect = e->rect();
    QPainter painter( this );


    QRadialGradient gradient( rect.width()/2, 1.2 * rect.height(), rect.height() + rect.width());
    gradient.setColorAt(0, QColor::fromRgb(10, 30, 10) );
    gradient.setColorAt(1, QColor::fromRgb(60, 180, 60) );
    painter.setPen( Qt::NoPen );
    painter.setBrush( gradient );
    painter.drawRect( rect );

    painter.setBrush( Qt::black );
    painter.drawRect( wall.x, rect.height()-wall.height, wall.width, wall.height );

    QRadialGradient rg(0.5 ,0.4 ,1, 0.7, 0.2);
    rg.setCoordinateMode( QGradient::ObjectBoundingMode );
    rg.setColorAt(0, Qt::white);
    rg.setColorAt(0.2, Qt::cyan);
    rg.setColorAt(1, Qt::darkBlue);
    painter.setBrush( rg );
    painter.drawEllipse( ball.x, ball.y, ball.radius, ball.radius );

}


void ArkanoidWorld::resizeEvent(QResizeEvent *e){

    ball.radius = ( 50.0 * (e->size().height() + e->size().width()) ) / 1000;
    wall.height = ( 20.0 * e->size().height() ) / 400;
    wall.width = ( 120.0 * e->size().width() ) / 600;
    wall.speed = ( 30.0 * e->size().width() ) / 600;

}


void ArkanoidWorld::timerEvent(QTimerEvent *e){

    if ( e->timerId() == drawTimerId ){
        repaint();
    }
    if ( e->timerId() == updateWorldTimerId ){
        updateWorld();
    }

}


void ArkanoidWorld::updateWorld(){

    if ( ball.x < 0 ) ball.vx = fabs( ball.vx );
    if ( ball.y < 0 ) ball.vy = fabs( ball.vy );
    if ( rect().width() - ball.x < ball.radius ) ball.vx = - fabs( ball.vx );

    if ( (ball.x + ball.radius / 2 > wall.x) && (ball.x - ball.radius / 2 < wall.x + wall.width) &&
         (ball.y + ball.radius > rect().height() - wall.height) ){

        ball.vy = - fabs( ball.vy );

    }

    if ( ball.y + ball.radius > rect().height() ) bottomHit();

    ball.x += ball.vx / 250;
    ball.y += ball.vy / 250;

    if ( wall.x <= 0  && wallMovementDirection < 0) wallMovementDirection = 0;
    if ( wall.x + wall.width >= rect().width() && wallMovementDirection > 0) wallMovementDirection = 0;

    wall.x += wall.speed * wallMovementDirection;

}


void ArkanoidWorld::bottomHit(){

    livesRemaining--;
    isActive = false;
    init();
    repaint();
    killTimer( updateWorldTimerId );
    killTimer( drawTimerId );


}


void ArkanoidWorld::setWallMovement( int direction ){

    if (direction > 0) wallMovementDirection = 1;
    if (direction < 0) wallMovementDirection = -1;
    if (direction == 0) wallMovementDirection = 0;

}


void ArkanoidWorld::go(){

    updateWorldTimerId = startTimer( 4 );
    drawTimerId = startTimer( 25 );
    isActive = true;

}


QDomDocument ArkanoidWorld::getState(){
    QDomDocument state;
    state.appendChild(state.createElement("state"));
    state.documentElement().setAttribute( "wallRestrictedMoveDir", wallRestrictedMoveDir );
    state.documentElement().setAttribute( "isActive", (int)isActive );
    state.documentElement().setAttribute( "livesRemaining", livesRemaining );
    return state;
}


void ArkanoidWorld::init(){

    ball.radius = ( 50.0 * (rect().height() + rect().width()) ) / 1000;
    wall.height = ( 20.0 * rect().height() ) / 400;
    wall.width = ( 120.0 * rect().width() ) / 600;
    wall.speed = ( 30.0 * rect().width() ) / 600;

    wall.x = rect().width()/2 - wall.width/2;
    wallMovementDirection = 0;

    ball.vx = qrand() % 800 ;
    ball.vy = - qrand() % 800;
    ball.x = rect().width()/2 - ball.radius/2;
    ball.y = rect().height() - wall.height - ball.radius;

}
