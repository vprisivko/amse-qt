#include "BallWidget.h"

BallWidget::BallWidget(QWidget* p): QWidget(p){
  qsrand(time(0));
  myball = new Ball();
  myracket = new Racket();

  mybackcolor = new QColor(0,150,250);
  myscore = 0;

  myballscount=3;

  resize(windowwidth,windowheight);
  setMaximumSize(windowwidth,windowheight);
  setMinimumSize(windowwidth,windowheight);
}


void BallWidget::paintEvent(QPaintEvent* e){
  QPainter p(this);
  int top = e->rect().top();
  int bottom = e->rect().bottom();
  int left = e->rect().left();
  int right = e->rect().right();
  QBrush brush(*mybackcolor);
  QPoint center(myball->x,myball->y);
  p.setPen(*mybackcolor);
  p.setBrush(brush);
  p.drawRect(e->rect());


  if (myracket->x< myracket->halfwidth){
    myracket->x = myracket->halfwidth;
  }
  if (myracket->x > windowwidth - myracket->halfwidth){
    myracket->x = windowwidth - myracket->halfwidth;
  }
  brush.setColor(*myracket->color);
  p.setPen(*myracket->color);
  p.setBrush(brush);
  p.drawRect(left + myracket->x-myracket->halfwidth,bottom-myracket->height,(myracket->halfwidth)*2,myracket->height);
  

  brush.setColor(*myball->color);
  p.setPen(*myball->color);
  p.setBrush(brush);
  
  if (myball->x > right - myball->radius) {
    myball->x = right - myball->radius;
    myball->vx = -myball->vx;
  }
  if (myball->x < myball->radius + left) {  
    myball->x = myball->radius + left;
    myball->vx = -myball->vx;
  }
  if (myball->y < top +myball->radius){
    myball->y = myball->radius +top;
    myball->vy = -myball->vy;
  }
  if ((myball->y <= bottom) && (myball->y >= bottom - myball->radius - myracket->height)){
    if ((myball->x - myracket->x < myracket->halfwidth)&&(myball->x - myracket->x > -myracket->halfwidth)) {
      if (myball->vy > 0) {
        myball->vy = -myball->vy;
      }
      myball->y = bottom - myball->radius - myracket->height;
    }
  }
  if (myball->y >= bottom){
    loseball();
    if (myballscount <= 0) {
      p.drawText(windowwidth/2-50,windowheight/2-20,"Game Over");
      p.drawText(windowwidth/2-50,windowheight/2,"You score  "+QString::number(myscore));
    }
  }
  p.drawEllipse(center,myball->radius,myball->radius);
  p.drawText(30,30,"Balls:  "+QString::number(myballscount));
}

void BallWidget::moveBall(){
  if (myballscount>0){
    myball->x=myball->x+myball->vx;
    myball->y=myball->y+myball->vy;
    myscore++;
    repaint();
  }
}

void BallWidget::moveRacketRight(){
  if (myballscount>0){
    myracket->x = myracket->x+myracket->step;
    repaint();
  }
}

void BallWidget::moveRacketLeft(){
  if (myballscount>0){
    myracket->x=myracket->x-myracket->step;
    repaint();
  }
}

int BallWidget::getBallsCount(){
  return myballscount;
}

Ball BallWidget::getBall(){
  return *myball;
}
Racket BallWidget::getRacket(){
  return *myracket;
}

void BallWidget::loseball(){
  myballscount = myballscount - 1;
  myball->vy = -qrand()%(ballspeed/2)-ballspeed/2;
  myball->vx = ((int) sqrt(ballspeed*ballspeed - (myball->vy)*(myball->vy)))*(2*(qrand()%2)-1);
  myball->x=windowwidth/2;
  myball->y=windowheight/2;
  if (myballscount == 0) {
    emit gameOver();
  }

}

//void BallWidget::gameOver(){
//}

void BallWidget::start(){
  myball->vy = -qrand()%(ballspeed/2)-ballspeed/2;
  myball->vx = (int) sqrt(ballspeed*ballspeed - (myball->vy)*(myball->vy));
  myball->x=windowwidth/2;
  myball->y=windowheight/2;
  
  myball->radius = ballradius;
  myracket->halfwidth = rackethalfwidth;
  myracket->height = racketheight;
  myracket->x = windowwidth/2;
  myscore = 0;

  myballscount=3;

}

void BallWidget::stop(){
   myracket->x = windowwidth/2;
}
  
