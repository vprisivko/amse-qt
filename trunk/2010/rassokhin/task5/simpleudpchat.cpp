#include "simpleudpchat.h"
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtNetwork/QHostAddress>
#include <QtGui/QMessageBox>
#include <QtGui/QApplication>
#include <QtGui/QIntValidator>
#include <QtCore/QByteArray>
#include <QtCore/QString>

SimpleUDPChat::SimpleUDPChat(QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Simple UDP Chat");

    constructObjects();
    connectObjects();
}

bool SimpleUDPChat::startUdpListener(int port) {
    if (udpSocket->isValid()) return false;
    if (!udpSocket->bind(QHostAddress::LocalHost, port)) {
        return false;
    }
    setWindowTitle("Simple UDP Chat at port " + QString::number(port));
    messagesList->addItem("Started at port " + QString::number(port));
    return true;
}

void SimpleUDPChat::constructObjects() {
    udpSocket = new QUdpSocket(this);

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QHBoxLayout * addressLayout = new QHBoxLayout();
    QHBoxLayout * messageLayout = new QHBoxLayout();

    messagesList = new QListWidget(this);
    ipAddressText = new QLineEdit(this);
    portText = new QLineEdit(this);
    messageText = new QLineEdit(this);
    sendButton = new QPushButton(this);
    
    sendButton->setText(tr("Send"));
    ipAddressText->setText(tr("127.0.0.1"));

    portText->setValidator(new QIntValidator(1, 65535, this));

    addressLayout->addWidget(ipAddressText);
    addressLayout->addWidget(portText);

    messageLayout->addWidget(messageText);
    messageLayout->addWidget(sendButton);

    mainLayout->addWidget(messagesList);
    mainLayout->addLayout(addressLayout);
    mainLayout->addLayout(messageLayout);
}

void SimpleUDPChat::connectObjects() {
    connect(sendButton, SIGNAL(clicked()),  SLOT(sendMessage()));
    connect(udpSocket,  SIGNAL(readyRead()),SLOT(readMessage()));
}

void SimpleUDPChat::sendMessage() {
    QString message = messageText->text();
    QString mcopy = message;
    mcopy.replace(" ", "");
    if (mcopy.length() == 0) {
        return;
    }
    QByteArray datagram;
    datagram.append(message);

    QHostAddress destination;
    if (!destination.setAddress(ipAddressText->text())) {
        QMessageBox::warning(0, "Simple UDP Chat","Cannot send message. May be address is invalid");
        return;
    }

    bool portGetting;
    quint16 destinationPort = portText->text().toInt(&portGetting);
    if (!portGetting || destinationPort == 0) {
        QMessageBox::warning(0, "Simple UDP Chat","Cannot send message. May be port is invalid");
        return;
    }

    qint64 sended = udpSocket->writeDatagram(datagram, destination, destinationPort);
    if (sended == -1) {
        QMessageBox::warning(0, "Simple UDP Chat","Cannot send message. Strange error occured");
        return;
    }
    messagesList->addItem(tr("to ") + ipAddressText->text() + ":" +
                          portText->text() + "|\t" + message);
    messageText->clear();

}

void SimpleUDPChat::readMessage() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        if( udpSocket->readDatagram(datagram.data(), datagram.size(), &sender,
                                    &senderPort) == -1)
            continue;

        QString toAdd = "from " + sender.toString() + ":" +
                        QString::number(senderPort) + "|\t" + QString(datagram);
        messagesList->addItem(toAdd);
    }
}

