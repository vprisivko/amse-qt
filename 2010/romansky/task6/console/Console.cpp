#include "Console.h"
#include "ConsoleHandler.h"

Console::Console(QWidget* p, const char* ip, quint16 port):QDialog(p){
  myip.setAddress(ip);
  myport = port;
  mysocket = new QUdpSocket();
  if (mysocket->bind(myip,myport)) {
    setWidgets();
    connectButtons();
    connect(mysocket, SIGNAL(readyRead()),this, SLOT(Read()));
  } else {
    QVBoxLayout* mainlayout = new QVBoxLayout();
    QLabel* messagelabel = new QLabel("    Invalid ip or port   " + QString::number(port)+"         ");
    mainlayout->addWidget(messagelabel);
    setLayout(mainlayout);
  }
}
void Console::setWidgets(){
  QVBoxLayout* mainlayout = new QVBoxLayout();
  QHBoxLayout* setlayout = new QHBoxLayout();
  QHBoxLayout* startstoplayout = new QHBoxLayout();
  QHBoxLayout* rightleftlayout = new QHBoxLayout();

  myright = new QPushButton("Right");
  myleft = new QPushButton("Left");
  mystop = new QPushButton("Stop");
  mystart = new QPushButton("Start");
  myset = new QPushButton("Set");

  myright->setEnabled(false);
  myleft->setEnabled(false);
  mystart->setEnabled(false);
  mystop->setEnabled(false);
  myset->setEnabled(true);

  myportedit = new QLineEdit();
  myipedit = new QLineEdit();

  setlayout->addWidget(new QLabel("IP"));
  setlayout->addWidget(myipedit);
  setlayout->addWidget(new QLabel("port"));
  setlayout->addWidget(myportedit);
  setlayout->addWidget(myset);

  startstoplayout->addWidget(mystart);
  startstoplayout->addWidget(mystop);
  
  rightleftlayout->addWidget(myleft);
  rightleftlayout->addWidget(myright);
  
  mainlayout->addItem(setlayout);
  mainlayout->addItem(startstoplayout);
  mainlayout->addItem(rightleftlayout);

  setLayout(mainlayout);

  mysendportset = false;
  mystate = new State();
}

void Console::connectButtons(){
  if (myright != NULL){
    connect(myright, SIGNAL(clicked()),this, SLOT(sendRight()));
  }
  if (myleft != NULL){
    connect(myleft, SIGNAL(clicked()), this, SLOT(sendLeft()));
  }
  if (mystart != NULL){
    connect(mystart, SIGNAL(clicked()), this, SLOT(sendStart()));
  }
  if (mystop != NULL) {
    connect(mystop, SIGNAL(clicked()), this, SLOT(sendStop()));
  }
  if (myset != NULL){
    connect(myset, SIGNAL(clicked()), this, SLOT(set()));
  }
}

void Console::set(){

  QMessageBox* messagebox = new QMessageBox();
  if (!(mysendip.setAddress(myipedit->text()))){
    messagebox->setText("          Invalid IP            ");
    messagebox->show();
    return;
  }
  myright->setEnabled(false);
  myleft->setEnabled(false);
  mystart->setEnabled(true);
  mystop->setEnabled(false);
  myset->setEnabled(false);

  mysendport = myportedit->text().toInt();
  mysendportset = true;
}

void Console::sendRight(){
  QMessageBox* messagebox = new QMessageBox();
  //QByteArray datagram;
  if(! (isSendPortSet())){
    messagebox->setText("Set adress of receiver");
    messagebox->show();
  } else {
    //datagram = "<right/>";
    mysocket->writeDatagram("<right>",mysendip,mysendport);
    //mysocket->writeDatagram("</right>",mysendip,mysendport);
  }
}

void Console::sendLeft(){
  QMessageBox* messagebox = new QMessageBox();
  //QByteArray datagram;
  if(! (isSendPortSet())){
    messagebox->setText("Set adress of receiver");
    messagebox->show();
  } else {
    //datagram = "<left/>";
    mysocket->writeDatagram("<left>",mysendip,mysendport);
  }
}

void Console::sendStart(){
  QMessageBox* messagebox = new QMessageBox();
  QByteArray datagram;
  
  if(! (isSendPortSet())){
    messagebox->setText("Set adress of receiver");
    messagebox->show();
  } else {
    datagram = "<start>";
    mysocket->writeDatagram(datagram,mysendip,mysendport);
    myright->setEnabled(true);
    myleft->setEnabled(true);
    mystart->setEnabled(false);
    mystop->setEnabled(true);
    myset->setEnabled(false);
  }
}

void Console::sendStop(){
  QMessageBox* messagebox = new QMessageBox();
  QByteArray datagram;

  
  if(! (isSendPortSet())){
    messagebox->setText("Set adress of receiver");
    messagebox->show();
  } else {
    datagram = "<stop>";
    mysocket->writeDatagram(datagram,mysendip,mysendport);
    myright->setEnabled(false);
    myleft->setEnabled(false);
    mystart->setEnabled(true);
    mystop->setEnabled(false);
    myset->setEnabled(true);
  }
}

void Console::Read(){
  QByteArray datagram;
  QHostAddress sender;
  quint16 senderPort;
  while(mysocket->hasPendingDatagrams()){
    datagram.resize(mysocket->pendingDatagramSize());
    mysocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
    parseDatagram(datagram);
    analizestate();
  }
}

bool Console::isSendPortSet(){
  return mysendportset;
}

void Console::parseDatagram(QByteArray datagram){
  ConsoleHandler* handler = new ConsoleHandler(this);
  QXmlSimpleReader* reader = new QXmlSimpleReader();
  QXmlInputSource* buffer = new QXmlInputSource();
  buffer->setData(datagram);
  reader->setContentHandler(handler);
  reader->parse(buffer); 
}

void Console::setstatetype(int value){
  mystate->statetype = value;
}

void Console::setballscount(int value){
  mystate->ballscount = value;
}

void Console::setwindowwidth(int value){
  mystate->windowwidth = value;
}

void Console::setballx(int value){
  mystate->ballx = value;
}

void Console::setbally(int value){
  mystate->bally = value;
}

void Console::setracketx(int value){
  mystate->racketx = value;
}

void Console::setrackethalfwidth(int value){
  mystate->rackethalfwidth = value;
}

void Console::analizestate(){
  if (mystate->statetype == State::NOTSTARTED){
    myright->setEnabled(false);
    myleft->setEnabled(false);
    mystart->setEnabled(true);
    mystop->setEnabled(false);
    myset->setEnabled(true);
  }
  if (mystate->statetype == State::STARTED){
    myright->setEnabled(true);
    myleft->setEnabled(true);
    mystart->setEnabled(false);
    mystop->setEnabled(true);
    myset->setEnabled(false); 
    if (mystate->racketx <= mystate->rackethalfwidth) {
      myleft->setEnabled(false);   
    }
    if (mystate->racketx >=mystate->windowwidth - mystate->rackethalfwidth) {
      myright->setEnabled(false);   
    }
  }
  if (mystate->statetype == State::GAMEOVER){
    myright->setEnabled(false);
    myleft->setEnabled(false);
    mystart->setEnabled(true);
    mystop->setEnabled(false);
    myset->setEnabled(true);
  }
   
}


