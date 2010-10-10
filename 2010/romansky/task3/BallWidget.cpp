#include "BallWidget.h"

BallWidget::BallWidget(QWidget* p): QWidget(p){
  qsrand(time(0));
  myvx=qrand()%30 - 15;
  myvy=qrand()%30 -15;
  myx=320;
  myy=240;
  myg=0;
  myradius = 30;
  mycolor = new QColor(Qt::yellow);
  mybackcolor = new QColor(0,150,250);
  mytimer = new QTimer(this);
  mytimer->start(100);
  resize(640,480);
  QObject::connect(mytimer,SIGNAL(timeout()),this,SLOT(move()));
}


void BallWidget::paintEvent(QPaintEvent* e){
  QPainter p(this);
  int top = e->rect().top();
  int bottom = e->rect().bottom();
  int left = e->rect().left();
  int right = e->rect().right();
  QBrush brush(*mybackcolor);
  QPoint center(myx,myy);
  p.setPen(*mybackcolor);
  p.setBrush(brush);
  p.drawRect(e->rect());
  brush.setColor(*mycolor);
  p.setPen(*mycolor);
  p.setBrush(brush);
  if (myx > right-myradius){
    if (myy < top+myradius){
      p.drawEllipse(center,right-myx,myy-top);
    } else {
      if (myy > bottom-myradius){
        p.drawEllipse(center,right-myx,bottom-myy);
      } else {
        p.drawEllipse(center,right-myx,myradius);
      }
    }
  } else {
    if (myx < left+myradius){
      if (myy < top+myradius){
        p.drawEllipse(center,myx-left,myy-top);
      } else {
        if (myy > bottom-myradius){
          p.drawEllipse(center,myx-left,bottom-myy);
        } else {
          p.drawEllipse(center,myx-left,myradius);
        }
      }      
    } else {
      if (myy < top+myradius){
        if (myx < left+myradius) {
          p.drawEllipse(center,myx-left,myy-top);
        } else {
          if (myx > right-myradius) {
            p.drawEllipse(center,right-myx,myy-top);
          } else {
            p.drawEllipse(center,myradius,myy-top);
            if ((myy-top)<=myradius/2){
              myvy=-myvy;
              myy=top+myradius/2;
            }
          }         
        }          
      } else {
        if (myy > bottom-myradius){
          if (myx < left+myradius) {
            p.drawEllipse(center,myx-left,bottom-myy);
            if (myvx<0){
              myvx=-myvx;
            }
            if (myvy>0){
              myvy=-myvy;
            }
          } else {
            if (myx > right-myradius) {
              p.drawEllipse(center,right-myx,bottom-myy);
              if (myvx>0){
                myvx=-myvx;
              }
              if (myvy>0){
                myvy=-myvy;
              }
            } else {
              p.drawEllipse(center,myradius,bottom-myy);
              if ((bottom-myy)<=myradius/2){
                myvy=-myvy;
                myy=bottom-myradius/2;
              }
            }         
          }         
        } else {
          p.drawEllipse(center,myradius,myradius);
        }
      }
    }
  }
  if ((right-myx)<=myradius/2){
    if (myvx>0){
      myvx=-myvx;
    }
    myx=right-myradius/2;
  }
  if ((myx-left)<=myradius/2){
    if (myvx<0){
      myvx=-myvx;
    }
    myx=left+myradius/2;
  }
  if ((myy-top)<=myradius/2){
    if (myvy<0){
      myvy=-myvy;
    }
    myy=top+myradius/2;
  }
  if ((bottom-myy)<=myradius/2){
    if (myvy>0){
      myvy=-myvy;
    }
    myy=bottom-myradius/2;
  }
}

void BallWidget::move(){
  myx=myx+myvx;
  myy=myy+myvy+myg/2;
  myvy=myvy+myg;
  repaint();
}
  
