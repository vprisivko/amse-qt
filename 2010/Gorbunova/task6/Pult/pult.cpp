#include "pult.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDomDocument>

Pult::Pult(QHostAddress _ip, int _port,QWidget* parent):QDialog(parent){
  lifes = 3;
  attr = new controlAttributs();
  attr->isStarted = 0;
  attr->gameover = 0;


  myport = _port;
  myip = _ip;
 createWidgets();
  connects();
}

void Pult::createWidgets(){
  QVBoxLayout* all = new QVBoxLayout(this);
  QHBoxLayout* layout1 = new QHBoxLayout();
  ip = new QLineEdit("127.0.0.1", this);
  port = new QLineEdit("6000",this);
  set = new QPushButton("set",this);
  layout1->addWidget(ip);
  layout1->addWidget(port);
  layout1->addWidget(set);
  all->addItem(layout1);
  
  QHBoxLayout* layout2 = new QHBoxLayout();
  right = new QPushButton("right",this);
  left = new QPushButton("left",this);
  layout2->addWidget(left);
  layout2->addWidget(right);
 
  all->addItem(layout2);
  
  start = new QPushButton("start",this);
  all->addWidget(start);
  
  start->setEnabled(true);
  left->setEnabled(false);
  right->setEnabled(false);
}

void Pult::connects(){
  connect(set,SIGNAL(clicked()),this, SLOT(setButton()));
  connect(left,SIGNAL(pressed()),this, SLOT(leftButton()));
  connect(right,SIGNAL(pressed()),this,SLOT(rightButton()));
  connect(start,SIGNAL(clicked()),this,SLOT(startButton()));
  mySocket = new QUdpSocket(this);
  mySocket->bind(myip,myport);
  connect(mySocket,SIGNAL(readyRead()),this,SLOT(readDatagram()));
}

void Pult::setButton(){
  thereip = ip->text();
  thereport = port->text().toInt();
  //mySocket->writeDatagram("set",thereip,thereport);
}


void Pult::rightButton(){
  QDomDocument datagram;
  QDomElement state = datagram.createElement("command");
  state.setAttribute("direction", 1);
  datagram.appendChild(state);
  mySocket->writeDatagram(datagram.toString().toUtf8(), thereip, thereport);
}
  
void Pult::leftButton(){
  QDomDocument datagram;
  QDomElement state = datagram.createElement("command");
  state.setAttribute("direction", -1);
  datagram.appendChild(state);
  mySocket->writeDatagram(datagram.toString().toUtf8(), thereip, thereport);
}

void Pult::startButton(){
  QDomDocument datagram;
  QDomElement state = datagram.createElement("start");
  datagram.appendChild(state);
  mySocket->writeDatagram(datagram.toString().toUtf8(), thereip, thereport);
  
}

void Pult::readDatagram(){
  while (mySocket->hasPendingDatagrams()){
    QByteArray datagram;
    datagram.resize(mySocket->pendingDatagramSize());
    QHostAddress  temp_ip;
    quint16 temp_port;
    mySocket->readDatagram(datagram.data(),datagram.size(),&temp_ip, &temp_port);
    
    QXmlSimpleReader reader;
    myParser* parser = new  myParser();

    reader.setContentHandler(parser);
    QXmlInputSource buffer;
    buffer.setData(datagram);
    reader.parse(&buffer);

    attr->isStarted = parser->attr.isStarted;
    attr->gameover = parser->attr.gameover;
    attr->left = parser->attr.left;
    attr->right = parser->attr.right;
    
     left->setEnabled(true);
      right->setEnabled(true);
    if (attr->isStarted == 1) {

      left->setEnabled(true);
      right->setEnabled(true);
      set->setEnabled(false);
      start->setEnabled(false);
     }
     if (attr->gameover == 1) {

       left->setEnabled(false);
       right->setEnabled(false);
       --lifes;
       if (lifes > 0) {
         start->setEnabled(true);
       } 
       else {
         start->setEnabled(false);
        }
      }
      if (attr->left == 0){
         left->setEnabled(false);

      }
       if (attr->right == 0){
         right->setEnabled(false);
      }
      
  }
}



  
  
