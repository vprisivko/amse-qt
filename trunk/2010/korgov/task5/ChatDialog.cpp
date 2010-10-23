#include "ChatDialog.h"

ChatDialog::ChatDialog(quint16 port, QWidget *parent)
    : QDialog(parent)
{
    myListWidget = new QListWidget(this);
    myLineEdIp = new QLineEdit("127.0.0.1",this);
    myLineEdPort = new QLineEdit(QString::number(port+1),this);
    myLineEdMessage = new QLineEdit(this);
    myBtnSend = new QPushButton("Send", this);
    myUdpSocket = new QUdpSocket(this);

    this->resize(400,300);
    this->setLayout(new QVBoxLayout());
    this->layout()->addWidget(myListWidget);

    QHBoxLayout *layoutIpPort = new QHBoxLayout();
        layoutIpPort->setSpacing(5);
        layoutIpPort->addWidget(myLineEdIp,8);
        myLineEdPort->setFixedWidth(80);
        myLineEdPort->setValidator(new QIntValidator(0,65535,myLineEdPort));
        layoutIpPort->addWidget(myLineEdPort,2);
    this->layout()->addItem(layoutIpPort);

    QHBoxLayout *layoutMessageSend = new QHBoxLayout();
        layoutMessageSend->setSpacing(5);
        layoutMessageSend->addWidget(myLineEdMessage);
        layoutMessageSend->addWidget(myBtnSend);
    this->layout()->addItem(layoutMessageSend);

    QObject::connect(myBtnSend,SIGNAL(clicked()),this,SLOT(sendMessage()));
    QObject::connect(myUdpSocket,SIGNAL(readyRead()),this,SLOT(reciveMessage()));

    this->setWindowTitle("task5, listening on port: " + QString::number(port));
    myUdpSocket->bind(port);
}

ChatDialog::~ChatDialog()
{

}

void ChatDialog::sendMessage()
{
    if(!myLineEdIp->text().isEmpty() && !myLineEdPort->text().isEmpty()){
        QHostAddress address(myLineEdIp->text());
        quint16 port = myLineEdPort->text().toInt();
        myUdpSocket->writeDatagram(myLineEdMessage->text().toUtf8(),address,port);
        myListWidget->addItem("Me: " + myLineEdMessage->text());
    }
    else {
        QMessageBox::warning(this,"Incorrect address or port","Please specify correct address and port.\ne.g. 192.168.1.2 and 35553");
    }
}

void ChatDialog::reciveMessage()
{
    while(myUdpSocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(myUdpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        myUdpSocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
        myListWidget->addItem(sender.toString() +":"+ QString::number(senderPort) + ": " + QString::fromUtf8(datagram.data()));
    }
}






