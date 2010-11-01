#include <Arcanoid.h>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <math.h>
#include <QUdpSocket>
#include <stdlib.h>
#include <QDomDocument>
#include <MyXMLHandler.h>
#include <QXmlSimpleReader>

#define DESK_WIDTH 75
#define DESK_HEIGHT 12

Arcanoid::Arcanoid(QString destIp, int destPort, int portToListen, int BallRadius, QWidget *parent):QWidget(parent){

    this->destIp = destIp;
    this->destPort = destPort;
    this->portToListen = portToListen;

    lifesLeft = 3;
    isPaused = true;

    configureNetwork();

    //Configure variables that describe our ball
    this->BallRadius = BallRadius;
    qsrand(QTime::currentTime().msec());

    resize(350,350);

    myCurrentX = qrand() % height()/2;
    myCurrentY = qrand() % width()/2;

    mySpeed = 3 + qrand() % 2;
    myAngle = qrand() % 360;
    myDX = mySpeed * sin(myAngle);
    myDY = mySpeed * cos(myAngle);

    deskX = (350/2) - (DESK_WIDTH/2);
    deskY = (350 - DESK_HEIGHT);

    myTimer = new QTimer(this);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(sendCurrentState()));
    myTimer->start(20);

}

//Here we draw everything
void Arcanoid::paintEvent(QPaintEvent*){
    deskY = height() - DESK_HEIGHT;
    double ellipseX, ellipseY;
    double shiftX, shiftY;
    ellipseX = ellipseY = BallRadius;
    shiftX = shiftY = 0;

    QPainter deskPainter(this);
    deskPainter.setPen(Qt::blue);
    deskPainter.setBrush(Qt::blue);

    deskPainter.drawRect(deskX, deskY, DESK_WIDTH, DESK_HEIGHT);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);

    myCurrentX += myDX;
    myCurrentY += myDY;

    //Right border
    if (( myCurrentX + BallRadius > width() ) && ( myCurrentX + BallRadius/2 < width() ) ){
        ellipseX = width()-myCurrentX;
        ellipseY = BallRadius*2 - (width()-myCurrentX);
    }

    if(myCurrentX + BallRadius/2 > width()){
        myDX *= -1;
        myCurrentX = width() - BallRadius/2;

        ellipseX = BallRadius / 2;
        ellipseY = BallRadius * 1.5;
    }
    //End right border

    //Left border
    if((myCurrentX < 0) && (myCurrentX + BallRadius/2 > 0)){
        shiftX = myCurrentX;
        ellipseX = BallRadius + myCurrentX;
        ellipseY = BallRadius - myCurrentX;

    }

    if(myCurrentX + BallRadius/2 < 0){
        shiftX = myCurrentX;
        myDX *= -1;
        myCurrentX = -BallRadius / 2;

        ellipseX = BallRadius / 2;
        ellipseY = BallRadius * 1.5;
    }
    //End left border

    //Bottom
    if ( myCurrentY + BallRadius > height() + 1){

        disconnect(myTimer,SIGNAL(timeout()),this,SLOT(update()));
        lifesLeft--;
        isPaused = true;

        if(lifesLeft != 0){
            deskPainter.drawText(10,30,"You Loosed a Ball! Press 'Go' to continue playing!");
            deskPainter.drawText(10, 60, QString("Lifes left:").append(QString::number(lifesLeft)));
        }
        else{
            deskPainter.drawText(10, 60, "No more lives left! Press 'Play again!'");
        }

        myCurrentX = qrand() % height()/2;
        myCurrentY = qrand() % width()/2;

        mySpeed = 3 + qrand() % 2;
        myAngle = qrand() % 360;
        myDX = mySpeed * sin(myAngle);
        myDY = mySpeed * cos(myAngle);


        deskX = ((width()/2) - DESK_WIDTH/2);
        deskY = (height() - DESK_HEIGHT);
    }

    //End bottom

    //Top
    if((myCurrentY < 0) && (myCurrentY + BallRadius / 2 > 0)){
        shiftY = myCurrentY;
        ellipseX = BallRadius - myCurrentY;
        ellipseY = BallRadius + myCurrentY;
    }

    if(myCurrentY + BallRadius / 2 < 0){
        shiftY = myCurrentY;
        myDY *= -1;
        myCurrentY = -BallRadius / 2;

        ellipseX = BallRadius * 1.5;
        ellipseY = BallRadius / 2;
    }
    //End top

    //Desk
    if(((myCurrentX + BallRadius/2) >= deskX && (myCurrentX + BallRadius/2) <= deskX + DESK_WIDTH) &&
       (( myCurrentY + BallRadius > height()-DESK_HEIGHT ) && ( myCurrentY + BallRadius/2 < height() - DESK_HEIGHT ) )){
        //myDY *= -1;
        ellipseY = height() - DESK_HEIGHT - myCurrentY;
        ellipseX = BallRadius * 2 - (height() - myCurrentY - DESK_HEIGHT);
    }
   if(((myCurrentX + BallRadius/2) >= deskX && (myCurrentX + BallRadius/2) <= deskX + DESK_WIDTH) &&
       (myCurrentY + BallRadius / 2 > height() - DESK_HEIGHT)){

        myDY *= -1;
        myCurrentY = height() - BallRadius / 2 - DESK_HEIGHT;

        ellipseY = BallRadius / 2;
        ellipseX = BallRadius * 1.5;
    }
    //End desk

    //Desk edges
   if( (myCurrentX - deskX)*(myCurrentX - deskX) + (myCurrentY - deskY)*(myCurrentY - deskY) < BallRadius*BallRadius){
        myDY *= -1;
   }
   if((myCurrentX - deskX + DESK_WIDTH)*(myCurrentX - deskX + DESK_WIDTH) + (myCurrentY - deskY)*(myCurrentY - deskY) < BallRadius*BallRadius){
        myDY *= -1;
   }
   //End desk edge


    painter.drawEllipse(QRectF(myCurrentX - shiftX, myCurrentY - shiftY, ellipseX, ellipseY));
}

//Bind the socket, start listening for incoming data
void Arcanoid::configureNetwork(){
    myUdpSocket = new QUdpSocket();
    if(!myUdpSocket->bind(portToListen)){
         qDebug()<<"Cannot bind socket to port: " <<  portToListen << " please try another port!";
         qDebug()<<"The application wouldn't work properly!\nRestart please!";
     }
     connect(myUdpSocket, SIGNAL(readyRead()),this, SLOT(newControlArrived()));
}

//Here we recieve 'Controls' and process them
void Arcanoid::newControlArrived(){

    while (myUdpSocket->hasPendingDatagrams()) {

        QByteArray datagram;
        datagram.resize(myUdpSocket->pendingDatagramSize());
        myUdpSocket->readDatagram(datagram.data(), datagram.size());

        QXmlSimpleReader reader;
        MyXmlHandler* myHandler = new MyXmlHandler();
        reader.setContentHandler(myHandler);
        QXmlInputSource recievedXml;
        recievedXml.setData(datagram);
        reader.parse(recievedXml);

        if(myHandler->leftPressed)
            deskX -= 25;
        if(myHandler->rightPressed)
            deskX += 25;
        if(myHandler->pausePressed){
            isPaused = true;
            disconnect(myTimer,SIGNAL(timeout()),this,SLOT(update()));
        }
        if(myHandler->goPressed){
            if(lifesLeft == 0)
                lifesLeft = 3;
            isPaused = false;
            connect(myTimer, SIGNAL(timeout()), this, SLOT(update()));
        }

    }
}

//Hee we send our current state
void Arcanoid::sendCurrentState(){

   QByteArray datagram = createDomByteArray();
   myUdpSocket->writeDatagram(datagram, QHostAddress(destIp), destPort);

}

//Here we serialize our current state using DOM XML
QByteArray Arcanoid::createDomByteArray(){

    QDomDocument doc("State");
    QDomElement root = doc.createElement("State");
    doc.appendChild(root);

    QDomElement tag[5];
    tag[0] = doc.createElement("DeskPosition");
    tag[1] = doc.createElement("GameStatus");
    tag[2] = doc.createElement("LifesLeft");
    tag[3] = doc.createElement("RightBorder");
    tag[4] = doc.createElement("DeskWidth");

    for(int i = 0; i < 5; i++){
        root.appendChild(tag[i]);
    }

    QDomAttr atr[5];
    atr[0] = doc.createAttribute("xCoordinate");
    atr[1] = doc.createAttribute("isPaused");
    atr[2] = doc.createAttribute("number");
    atr[3] = doc.createAttribute("number");
    atr[4] = doc.createAttribute("pixels");

    atr[0].setValue(QString::number(deskX));
    atr[1].setValue(QString::number(isPaused));
    atr[2].setValue(QString::number(lifesLeft));
    atr[3].setValue(QString::number(this->geometry().width()));
    atr[4].setValue(QString::number(DESK_WIDTH));

    for(int i = 0; i < 5; i++){
        tag[i].setAttributeNode(atr[i]);
    }
    return doc.toByteArray();
}
