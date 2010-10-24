#include "udpchatdialog.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QtNetwork/QUdpSocket>
#include<QByteArray>
UdpChatDialog :: UdpChatDialog(int _port) {
    port = _port;
    createWidgets();
    addWidgets();
    connectWidgets();
}
void UdpChatDialog::createWidgets() {
    chatArea = new QListWidget(this);
    ip = new QLabel("IP: ",this);
    ipArea = new QLineEdit(this);
    ipArea->setText("127.0.0.1");
    p = new QLabel("PORT: ",this);
    listenPort = new QLineEdit(this);
    inputText = new QTextEdit(this);
    sendButton = new QPushButton("SEND",this);
//init socket//
    udpSocket = new QUdpSocket(this);
    if(!udpSocket->bind(port)){
        printf("Enter another port.\n");
        exit(-1);
    }


}
void UdpChatDialog::addWidgets(){
    setLayout(new QVBoxLayout());
    layout()->addWidget( chatArea );
    QHBoxLayout *ipAndPortLay = new QHBoxLayout();
    ipAndPortLay->addWidget( ip );
    ipAndPortLay->addWidget( ipArea );
    ipAndPortLay->addWidget( p );
    ipAndPortLay->addWidget( listenPort );
    layout()->addItem( ipAndPortLay );
    QHBoxLayout *textAndSendLay = new QHBoxLayout();
    textAndSendLay->addWidget( inputText );
    textAndSendLay->addWidget( sendButton );
    layout()->addItem( textAndSendLay );
}
void UdpChatDialog::connectWidgets(){
    connect(udpSocket, SIGNAL( readyRead()),this, SLOT(readMessage()) );
    connect(sendButton,SIGNAL( clicked()),this,SLOT(sendMessage()) );

}
void UdpChatDialog::readMessage(){

    while (udpSocket->hasPendingDatagrams()) {
                QByteArray datagram;
                datagram.resize( udpSocket->pendingDatagramSize() );
                QHostAddress senderHost;
                quint16 senderPort;
                udpSocket->readDatagram( datagram.data(), datagram.size(),&senderHost,&senderPort );
                chatArea->addItem( senderHost.toString() + ":\t" + datagram.data()) ;
            }
}
void UdpChatDialog::sendMessage(){
    QByteArray datagram;
   QString inputMessage = inputText->toPlainText();
   datagram.append( inputMessage );
   QHostAddress hostAddr(ipArea->text());
   quint16 destPort = listenPort->text().toInt();
   udpSocket->writeDatagram(datagram,hostAddr,destPort);
   QString outStr = "I:\t";
   outStr += datagram.data();
   chatArea->addItem( outStr );
   inputText->setPlainText( "" );

}
