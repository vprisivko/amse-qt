#include"BallDial.h"
#include<QDebug>
#include<QFile>
#include<QVBoxLayout>
BallDial ::BallDial(QHostAddress _destip, qint16 _destport, qint16 _myport){
    //setMinimumSize(4*radius,4*radius);
    setFixedSize(600,400);
    state = new State();
    p = new QPainter();
    bTimer = new QTimer(this);
    connect( bTimer, SIGNAL(timeout()), this, SLOT( timeEvent()) );
  //  bTimer->start( 10 );
    xmlH = new MyXmlHandler(this);
    socket = new QUdpSocket(this);
    destip = _destip;
    destport = _destport;
    myport = _myport;
    if(!socket->bind(myport)){
         qDebug()<<"Update ip and port i file \"ip_port.txt\" \n";
         exit(-1);
    }
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(bTimer,SIGNAL(timeout()),this,SLOT(sendMessage()));
    lives = new QLabel(QString::number(state->defLives) +"  lives left",this);
    this->setLayout(new QVBoxLayout(this));
    this->layout()->addWidget(lives);
 }

void BallDial::paintEvent( QPaintEvent *) {

    p->begin( this );
    p->setBrush( Qt::SolidPattern );
    p->setPen( Qt::green );
    QBrush *brush = new QBrush(Qt::blue, Qt::SolidPattern);
    if(bTimer->isActive()){
    p->drawEllipse( QPoint( state->b->x, state->b->y ), state->b->xradius, state->b->yradius);
    }
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
             state->livesleft-= 1;
             lives->setText(QString::number(state->livesleft) + "  lives left");
             if(state->livesleft > 0){
                state->b->restartBall();
            }
             else {
                  bTimer->stop();
             }
             repaint();
             sendMessage();
             return;

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
    sendMessage();

}
void BallDial::readMessage(){
    QXmlSimpleReader sReader;
    sReader.setContentHandler(xmlH);
    QXmlInputSource buffer;
    while (socket->hasPendingDatagrams()) {
          QByteArray datagram;
          datagram.resize( socket->pendingDatagramSize() );
          QHostAddress senderHost;
          quint16 senderPort;
          socket->readDatagram( datagram.data(), datagram.size(),&senderHost,&senderPort );
          buffer.setData(datagram);
          sReader.parse(buffer);
    }
}
void BallDial::sendMessage(){
     QByteArray datagram;
     QDomDocument doc;
     doc.appendChild(state->serialize(state,&doc));
     QString inputMessage = doc.toString();
     datagram.append( inputMessage );
     socket->writeDatagram(datagram,destip,destport);
}
MyXmlHandler::MyXmlHandler(BallDial *dial){
     bDial = dial;

}

bool MyXmlHandler::startElement(const QString &,
                                const QString &, const QString &qName,
                                const QXmlAttributes &atts){
    if(qName=="command"){
        if(atts.value("value") == "left"){
            bDial->state->r->xPosition -= 40;
        }
        else if(atts.value("value")== "right"){
            bDial->state->r->xPosition += 40;
        }
        else if(atts.value("value") == "run"){
            bDial->state->livesleft  = bDial->state->defLives;
            bDial->state->b->restartBall();
            bDial->lives->setText(QString::number(bDial->state->defLives) +"  lives left");
            bDial->bTimer->start(10);
        }

   }
    return true;
}
