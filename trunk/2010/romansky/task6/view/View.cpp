#include "View.h"

#include "ViewHandler.h"

View::View(QWidget* p, const char* ip, quint16 port):QDialog(p){
  myip.setAddress(ip);
  myport = port;
  mysocket = new QUdpSocket();
  if (mysocket->bind(myip,myport)) {
    setWidgets();
    connect(mysocket, SIGNAL(readyRead()),this, SLOT(Read()));
  } else {
    QVBoxLayout* mainlayout = new QVBoxLayout();
    QLabel* messagelabel = new QLabel("    Invalid ip or port   " + QString::number(port)+"         ");
    mainlayout->addWidget(messagelabel);
    setLayout(mainlayout);
  }
}

void View::setWidgets(){
  mysendportset = false;
  QVBoxLayout* mainlayout = new QVBoxLayout();
  QHBoxLayout* setlayout = new QHBoxLayout();

  myballwidget = new BallWidget();
  myballwidget->resize(640,480);

  myset = new QPushButton("Set");

  myportedit = new QLineEdit();
  myipedit = new QLineEdit();

  setlayout->addWidget(new QLabel("IP"));
  setlayout->addWidget(myipedit);
  setlayout->addWidget(new QLabel("port"));
  setlayout->addWidget(myportedit);
  setlayout->addWidget(myset);

  mainlayout->addWidget(myballwidget);
  mainlayout->addItem(setlayout);

  setLayout(mainlayout);



  mytimer = new QTimer(this);
 
  mystate = NOTSTARTED;
  QObject::connect(mytimer,SIGNAL(timeout()),myballwidget,SLOT(moveBall()));
  QObject::connect(mytimer,SIGNAL(timeout()),this,SLOT(send()));
  QObject::connect(myset,SIGNAL(clicked()),this,SLOT(set()));
  QObject::connect(myballwidget,SIGNAL(gameOver()),this,SLOT(gameOver()));
}

QDomDocument View::serialize(){
  QDomDocument doc;
  QDomElement state = doc.createElement("state");
  state.setAttribute("statetype",QString::number(mystate));
  state.setAttribute("ballscount", QString::number(myballwidget->getBallsCount()));
  state.setAttribute("windowwidth",QString::number(myballwidget->windowwidth));
  state.appendChild(myballwidget->getRacket().serialize(doc));
  state.appendChild(myballwidget->getBall().serialize(doc));
  doc.appendChild(state);
  return doc;
}


void View::send(){
  QMessageBox* messagebox = new QMessageBox();
  QDomDocument doc;
  if(! (isSendPortSet())){
    messagebox->setText("Set adress of receiver");
    messagebox->show();
  } else {
    doc = serialize();
    mysocket->writeDatagram(doc.toByteArray(),mysendip,mysendport);
  }
}

void View::set(){
  QMessageBox* messagebox = new QMessageBox();
  if (!(mysendip.setAddress(myipedit->text()))){
    messagebox->setText("          Invalid IP            ");
    messagebox->show();
    return;
  }
  mysendport = myportedit->text().toInt();
  mysendportset = true;
}



bool View::isSendPortSet(){
  return mysendportset;
}

void View::gameOver(){
  mystate = GAMEOVER;
}

void View::Read(){
  QByteArray datagram;
  QHostAddress sender;
  quint16 senderPort;
  while(mysocket->hasPendingDatagrams()){
    datagram.resize(mysocket->pendingDatagramSize());
    mysocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
    if (!mysendportset){
      mysendip = sender;
      mysendport = senderPort;
      mysendportset = true;
      myipedit->setText(sender.toString());
      myportedit->setText(QString::number(senderPort));
    }
    if ((mysendport == senderPort)&&(mysendip == sender)){
      parseDatagram(datagram);
    }
  }
}

void View::parseDatagram(QByteArray datagram){
  ViewHandler* handler = new ViewHandler(this);
  QXmlSimpleReader* reader = new QXmlSimpleReader();
  QXmlInputSource* buffer = new QXmlInputSource();
  buffer->setData(datagram);
  reader->setContentHandler(handler);
  reader->parse(buffer); 
}

void View::setState(int value){
  mystate = value;
}

void View::start(){
  mytimer->start(timeperiod);
  myballwidget->start();
}

void View::stop(){
  mytimer->stop();
  myballwidget->stop();
}

void View::moveRacketRight(){
  if (myballwidget != NULL) {
    myballwidget->moveRacketRight();
  }
}

void View::moveRacketLeft(){
  if (myballwidget != NULL) {
    myballwidget->moveRacketLeft();
  }
}
  
