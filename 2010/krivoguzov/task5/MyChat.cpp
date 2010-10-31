#include <MyChat.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QByteArray>
#include <QHostAddress>

MyChat::MyChat(int port){

    portNumber = port;

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
    myUdpSocket = new QUdpSocket(this);

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

    setWindowTitle("We are on port " + QString::number(portNumber));
    ipEdit->setText("127.0.0.1");

    resize(500,300);
}

void MyChat::showExplanation(){

    msgList->addItem("By default we listen 127.0.0.1");
    msgList->addItem(QString("on port ").append(QString::number(portNumber)));
    msgList->addItem("Please specify the ip and port for sending messages");

}

void MyChat::configureNetwork(){

    myUdpSocket->bind(QHostAddress::LocalHost,portNumber);
    connect(sendButton,SIGNAL(clicked()),this,SLOT(sendPressed()));
    connect(myUdpSocket, SIGNAL(readyRead()),this, SLOT(newMessageArrived()));

}

void MyChat::sendPressed(){

    if(ipEdit->text().isEmpty() || portEdit->text().isEmpty()){

        msgList->addItem("Message wasn't sent!\nPlease specify destination IP and Port!");

    } else if (msgEdit->text() == ""){

        msgList->addItem("We don't send empty messages! Write something!");

    } else{

        QByteArray datagram = msgEdit->text().toUtf8();
        myUdpSocket->writeDatagram(datagram, QHostAddress(ipEdit->text()), portEdit->text().toInt());
        msgList->addItem(QString(">> We sended: ").append(msgEdit->text()));
        msgEdit->clear();
    }
    msgList->scrollToBottom();
}

  void MyChat::newMessageArrived(){

      while (myUdpSocket->hasPendingDatagrams()) {

          QByteArray datagram;
          datagram.resize(myUdpSocket->pendingDatagramSize());
          myUdpSocket->readDatagram(datagram.data(), datagram.size());
          msgList->addItem(QString("<< We recieved: ").append(datagram.data()));
          msgList->scrollToBottom();

      }
  }


