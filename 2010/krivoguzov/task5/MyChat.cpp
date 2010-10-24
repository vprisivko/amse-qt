#include <MyChat.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QByteArray>
#include <QHostAddress>

MyChat::MyChat(int port){

    listenPortNumber = port;

    createDialog();
    showExplanation();
    configureNetwork();

}

void MyChat::createDialog(){

    msgList = new QListWidget();
    ipEdit = new QLineEdit();
    portEdit = new QLineEdit();
    msgEdit = new QLineEdit();
    sendButton = new QPushButton("Send");
    udpListener = new QUdpSocket(this);
    udpSender = new QUdpSocket(this);

    msgList->setSelectionMode(QAbstractItemView::SingleSelection);

    QVBoxLayout* mainLay = new QVBoxLayout;
    QHBoxLayout* ipAndPortLay = new QHBoxLayout;
    QHBoxLayout* msgAndButtonLay = new QHBoxLayout;

    ipAndPortLay->addWidget(ipEdit);
    ipAndPortLay->addWidget(portEdit);

    msgAndButtonLay->addWidget(msgEdit);
    msgAndButtonLay->addWidget(sendButton);

    mainLay->addWidget(msgList);
    mainLay->addLayout(ipAndPortLay);
    mainLay->addLayout(msgAndButtonLay);

    setLayout(mainLay);

    setWindowTitle("We are on port " + QString::number(listenPortNumber));
    ipEdit->setText("127.0.0.1");

    resize(500,300);
}

void MyChat::showExplanation(){

    msgList->addItem("By default we listen 127.0.0.1");
    msgList->addItem(QString("on port ").append(QString::number(listenPortNumber)));
    msgList->addItem("Please specify the ip and port for sending messages");

}

void MyChat::configureNetwork(){

    udpListener->bind(QHostAddress::LocalHost,listenPortNumber);
    connect(sendButton,SIGNAL(clicked()),this,SLOT(sendPressed()));
    connect(udpListener, SIGNAL(readyRead()),this, SLOT(newMessageArrived()));

}

void MyChat::sendPressed(){

    if(ipEdit->text().isEmpty() || portEdit->text().isEmpty()){
        msgList->addItem("Message wasn't sent!\nPlease specify destination IP and Port!");
    }

    else{
        QByteArray datagram = msgEdit->text().toUtf8();
        udpSender->writeDatagram(datagram.data(), datagram.size(),QHostAddress(ipEdit->text()), portEdit->text().toInt());
        msgList->addItem(QString(">> We sended: ").append(msgEdit->text()));
        msgList->scrollToBottom();
        msgEdit->setText("");
    }
}

  void MyChat::newMessageArrived(){

      while (udpListener->hasPendingDatagrams()) {

          QByteArray datagram;
          datagram.resize(udpListener->pendingDatagramSize());
          udpListener->readDatagram(datagram.data(), datagram.size());
          msgList->addItem(QString("<< We recieved: ").append(datagram.data()));
          msgList->scrollToBottom();

         }
  }


