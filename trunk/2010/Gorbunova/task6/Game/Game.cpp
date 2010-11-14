#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Game.h"

Game::Game(QHostAddress _ip, int _port,QWidget *parent): QDialog(parent) {

 myport = _port;
 myip = _ip;
 myLostBalls = 3;
 isStarted = 0;
 isGameOver = 0;
 isLeft = 1;
 isRight = 1;
 createWidgets();
 connects();

}
void Game::connects(){
  mySocket = new QUdpSocket(this);
  mySocket->bind(myip,myport);
  QObject::connect(setButton, SIGNAL(pressed()), this, SLOT(set()));
  QObject::connect(this->myGame, SIGNAL(gameover()), this, SLOT(gameover()));
  QObject::connect(this->myGame, SIGNAL(Start()), this, SLOT(Start()));
  QObject::connect(this->myGame, SIGNAL(noleft()), this, SLOT(noleft()));
  QObject::connect(this->myGame, SIGNAL(noright()), this, SLOT(noright()));
  QObject::connect(this->myGame, SIGNAL(everything()), this, SLOT(everything()));
  QObject::connect(mySocket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
  QObject::connect(this, SIGNAL(left()), this->myGame, SLOT(left()));
  QObject::connect(this, SIGNAL(right()), this->myGame, SLOT(right()));
  QObject::connect(this, SIGNAL(start()), this->myGame, SLOT(start()));
 
}
void Game::createWidgets(){
  ip = new QLineEdit("127.0.0.1",this);
  port= new QLineEdit("5000",this);
  setButton= new QPushButton("set", this);
  myGame = new Ball( 30, 1, 1,this);
  myGame->myRacket.xTopLeft = myGame->width() / 2;
  myGame->myRacket.yTopLeft = myGame->height() - 6;
  setLayout(new QVBoxLayout(this));
  layout()->addWidget(myGame);
  QHBoxLayout* lay = new QHBoxLayout();
  lay->addWidget(ip);
  lay->addWidget(port);
  lay->addWidget(setButton);
  layout()->addItem(lay);

}
void Game::set() {
  thereip = ip->text();
  thereport = port->text().toInt();
  this->send();
}

void Game::send() {
  QDomDocument datagram = this->serialize();
  mySocket->writeDatagram(datagram.toString().toUtf8(), thereip, thereport);
}
void Game::Start(){
  isStarted = 1;
  this->send();
  }
void Game::gameover() {
  isGameOver = 1;
  this->send();
}
void Game::noleft() {
  isLeft = 0;
  this->send();
}
void Game::everything() {
  isLeft = 1;
  isRight = 1;
  this->send();
}
void Game::noright() {
  isRight = 0;
  this->send();
}
QDomDocument Game::serialize() {
  QDomDocument datagram;
  QDomElement state = datagram.createElement("state");
  state.setAttribute("isStarted", isStarted);
  state.setAttribute("gameover", isGameOver);
  state.setAttribute("left", isLeft);
  state.setAttribute("right",isRight);
  datagram.appendChild(state);
  return datagram;
}

void Game::readDatagrams() {
  while (mySocket->hasPendingDatagrams()) {

    QByteArray datagram;
    datagram.resize(mySocket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    mySocket->readDatagram(datagram.data(), datagram.size(),
                                        &sender, &senderPort);

    QXmlSimpleReader reader;
    myHandler* xmlHandler = new myHandler();

   reader.setContentHandler(xmlHandler);
   QXmlInputSource buffer;
   buffer.setData(datagram);
   reader.parse(&buffer);

   myDirection = xmlHandler->attr.direction;
        if (myDirection == -1) {
                isRight = 1;
                everything(); 
                emit left();
                
        }
        if (myDirection == 1) {
                isLeft = 1;
                everything(); 
                emit right();
        }
        isStarted = xmlHandler->attr.isStarted;
     
        if (isStarted == 1) {
                isGameOver = 0;
                isRight = 1;
                isLeft = 1;
                emit start();
        }

        this->send();
        }
}






