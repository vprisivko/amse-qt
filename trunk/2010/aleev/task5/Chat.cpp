#include "Chat.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QLabel>
#include <QByteArray>
#include <QMessageBox>

Chat::Chat(quint16 port, QWidget *parent) : QDialog(parent), myPort(port) {
    setWindowTitle("Welcome to UdpChat! Your port is " + QString::number(port));
    setMinimumSize(420, 300);
    createWidgets();
    connectAll();
}

void Chat::createWidgets() {
    QVBoxLayout *mainLayout = new QVBoxLayout();

    myHistory = new QListWidget(this);
    mainLayout->addWidget(myHistory);

    QHBoxLayout *infoLayout = new QHBoxLayout();
    myListenerPort = new QLineEdit("", this);
    myListenerPort->setValidator(new QIntValidator(0, 65535, myListenerPort));
    myListenerIp = new QLineEdit("192.168.44.11", this);
    infoLayout->addWidget(new QLabel("IP : "));
    infoLayout->addWidget(myListenerIp);
    infoLayout->addWidget(new QLabel("Port : "));
    infoLayout->addWidget(myListenerPort);
    mainLayout->addItem(infoLayout);

    QHBoxLayout *msgLayout = new QHBoxLayout();
    myMessageTE = new QTextEdit(this);
    mySendButton = new QPushButton("Send", this);
    myMessageTE->setMaximumHeight(60);
    msgLayout->addWidget(myMessageTE);
    msgLayout->addWidget(mySendButton);
    mainLayout->addItem(msgLayout);

    myUdpSocket = new QUdpSocket(this);
    if (!myUdpSocket->bind(myPort)) {
        printf("Cannot bind. Try another port.\n");
        exit(1);
    }

    setLayout(mainLayout);
}

void Chat::connectAll() {
    connect(mySendButton, SIGNAL(clicked()), SLOT (sendTo()));
    connect(myUdpSocket, SIGNAL(readyRead()), SLOT(recvFrom()));
}

void Chat::sendTo() {
    if ((!myListenerPort->text().isEmpty()) && (!myListenerIp->text().isEmpty())) {
        QString msg = myMessageTE->toPlainText();
        QByteArray byteArrayMessage(msg.toAscii());
        myUdpSocket->writeDatagram(msg.toAscii(), QHostAddress(myListenerIp->text()), myListenerPort->text().toInt());
        myHistory->addItem("<You> : " + msg);
        myMessageTE->clear();
    }
    else {
        QMessageBox::warning(this, "Warning", "Fields IP and Port shouldn't be empty");
    }
}

void Chat::recvFrom(){
    while(myUdpSocket->hasPendingDatagrams()) {
        QByteArray msg;
        msg.resize(myUdpSocket->pendingDatagramSize());
        QHostAddress addr;
        quint16 port;
        myUdpSocket->readDatagram(msg.data(), msg.size(), &addr, &port);
        myHistory->addItem("<" + addr.toString() + ":" + QString::number(port) + "> : " + QString(msg));
    }
}
