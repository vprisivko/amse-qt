#include "dialog.h"

Dialog::Dialog(int port, QWidget *parent)
        : QDialog(parent) {
    fromPort = port;
    createMainWindow();
    connects();
    socket = new QUdpSocket(this);
    socket->bind(fromPort);

    setConnectionData();
}

void Dialog::createMainWindow() {
    messageBox = new QListWidget(this);

    QHBoxLayout *hLay1 = new QHBoxLayout();
    lineIP = new QLineEdit(this);
    linePort = new QLineEdit(this);
    hLay1->addWidget(lineIP);
    hLay1->addWidget(linePort);

    QHBoxLayout *hLay2 = new QHBoxLayout();
    lineMessage = new QLineEdit(this);
    bnSend = new QPushButton("Send", this);
    hLay2->addWidget(lineMessage);
    hLay2->addWidget(bnSend);

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->addWidget(messageBox);
    mainLay->addItem(hLay1);
    mainLay->addItem(hLay2);
}

void Dialog::connects() {
    connect(bnSend, SIGNAL(pressed()), this, SLOT(ssendMessage()));
}

void Dialog::setConnectionData() {
    this->setWindowTitle(QString::number(fromPort));

    connect(socket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
}

void Dialog::ssendMessage() {
  QByteArray sendMessage;
  sendMessage.append(lineMessage->text());
  QHostAddress toIP(lineIP->text());
  quint16 toPort = linePort->text().toInt();
  socket->writeDatagram(sendMessage, toIP, toPort);
  QString myMessage = "I:\t";
  myMessage += sendMessage.data();
  messageBox->addItem(myMessage);
  lineMessage->setText("");
}

void Dialog::readDatagrams() {
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress fromIP;
        quint16 fromPort;
        socket->readDatagram(datagram.data(), datagram.size(), &fromIP, &fromPort );
        messageBox->addItem(fromIP.toString() + ":\t" + datagram.data()) ;
    }
}

Dialog::~Dialog() {
    delete bnSend;
    delete lineMessage;
    delete linePort;
    delete lineIP;
    delete messageBox;
}

//myDialog::myDialog(int _myport){
//  myport=_myport;
//  createWidgets();
//
//  udpSocket = new QUdpSocket(this);
//  if(!udpSocket->bind(myport)){
//    printf("fail\n");
//    exit(-1);
//  }
//  connects();
//}
//void myDialog::connects(){
//  connect(send, SIGNAL(clicked()), this, SLOT(Send()) );
//  QObject::connect(udpSocket, SIGNAL( readyRead()),this, SLOT(Read()) );
//}
//void myDialog::createWidgets(){
//  this->setLayout( new QVBoxLayout());
//
//  centralText = new QListWidget(this);
//  this->layout()->addWidget(centralText);
//
//  QHBoxLayout* ipconfig = new QHBoxLayout();
//  ip = new QLineEdit(this);
//  ipconfig->addWidget(ip);
//  port = new QLineEdit(this);
//  ipconfig->addWidget(port);
//  this->layout()->addItem(ipconfig);
//
//  QHBoxLayout* text = new QHBoxLayout();
//  textEdit = new QLineEdit(this);
//  text->addWidget(textEdit);
//  send = new QPushButton( "Send", this);
//  text->addWidget(send);
//  this->layout()->addItem(text);
//
//}
