#include "widget.h"

#include <QBoxLayout>

Widget::Widget(int port, QWidget *parent)
    : QWidget(parent)
{
    mySocket = new QUdpSocket(this);
    mySocket->bind(QHostAddress::LocalHost, port);
    QHostAddress address = QHostAddress::LocalHost;
    setWindowTitle(QString("%1 - %2").arg(address.toString()).arg(port));

    createWidgets();

    connect(mySocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    connect(mySendButton, SIGNAL(clicked()), this, SLOT(sendDatagram()));
}

void Widget::createWidgets() {
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    myListWidget = new QListWidget(this);
    layout->addWidget(myListWidget);

    QHBoxLayout *addressLayout = new QHBoxLayout;
    layout->addLayout(addressLayout);

    myHttpAddress = new QLineEdit(this);
    addressLayout->addWidget(myHttpAddress);

    myPort = new QLineEdit(this);
    myPort->setValidator(new QIntValidator);
    addressLayout->addWidget(myPort);

    QHBoxLayout *messageLayout = new QHBoxLayout;
    layout->addLayout(messageLayout);

    myMessage = new QLineEdit(this);
    messageLayout->addWidget(myMessage);

    mySendButton = new QPushButton("Send", this);
    messageLayout->addWidget(mySendButton);
}

void Widget::readPendingDatagrams() {
    while (mySocket->hasPendingDatagrams()) {
         QByteArray datagram;
         datagram.resize(mySocket->pendingDatagramSize());
         QHostAddress sender;
         quint16 senderPort;

         mySocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

         myListWidget->addItem(datagram);
     }
}

void Widget::sendDatagram() {
    QHostAddress address(myHttpAddress->text());
    int port = myPort->text().toInt();
    QByteArray array = myMessage->text().toAscii();
    mySocket->writeDatagram(array.data(), array.size(), address, port);
}
