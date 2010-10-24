#include <QApplication>
#include <QHBoxLayout>
#include <QSettings>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QRegExp>
#include <QMessageBox>
#include <QByteArray>
#include <QDebug>

#include "NetDialog.h"

NetDialog::NetDialog(quint16 port, QWidget *parent) : QDialog(parent) {
    setupUI();
    setValidators();
    loadSettings();
    initSocket(port);
    createConnects();
}

NetDialog::~NetDialog() {
    saveSettings();
}

void NetDialog::setupUI() {
    setWindowTitle( "ChitChat" );
    setLayout( new QVBoxLayout() );

    //list widget
    myListWidget = new QListWidget(this);
    layout()->addWidget(myListWidget);

    //layouts
    QHBoxLayout* horLayout1 = new QHBoxLayout();
    QHBoxLayout* horLayout2 = new QHBoxLayout();
    layout()->addItem(horLayout1);
    layout()->addItem(horLayout2);

    //IP line edit
    myIPLineEdit = new QLineEdit("127.0.0.1",this);
    horLayout1->addWidget(myIPLineEdit);
    horLayout1->setSpacing(5);

    //port line edit
    myPortLineEdit = new QLineEdit("1000",this);
    horLayout1->addWidget(myPortLineEdit);

    //message line edit
    myMessageLineEdit = new QLineEdit("enter your message here",this);
    horLayout2->addWidget(myMessageLineEdit);

    //send button
    mySendButton = new QPushButton("Send",this);
    horLayout2->addWidget(mySendButton);

}

void NetDialog::setValidators() {
    myPortLineEdit->setValidator( new QIntValidator(0,65535,this) );
}

void NetDialog::loadSettings() {
    mySettings = new QSettings("turkin","task5",this);
    if ( mySettings->contains("geometry") ) {
        setGeometry( mySettings->value("geometry").toRect() );
    }
}
void NetDialog::saveSettings() {
    mySettings->setValue("geometry", geometry() );
}

void NetDialog::createConnects() {
    connect( mySendButton, SIGNAL(pressed()), this, SLOT(sendSlot()) );
    connect( mySocket,SIGNAL(readyRead()),this,SLOT(receiveSlot()));

}

void NetDialog::initSocket(quint16 port) {
    mySocket = new QUdpSocket(this);
    bool result = mySocket->bind(QHostAddress::LocalHost, port);
    if (result == true) {
        myListWidget->addItem( QString("Listening port %1...").arg(port) );
    } else {
        QMessageBox::critical(this, "Error", "Can't use this port!\nPlease, choose another one");
        throw std::exception();
    }
}


void NetDialog::sendSlot() {

    QHostAddress address(myIPLineEdit->text());
    if ( address.toString() == "") {
        QMessageBox::critical(this, "Error", "IP address is wrong!");
        return;
    }
    quint16 port = myPortLineEdit->text().toInt();
    qint64 result = mySocket->writeDatagram(myMessageLineEdit->text().toUtf8(),address,port);
    if (result == -1) {
        QMessageBox::critical(this, "Error", mySocket->errorString());
    } else {
        newChatMessage("You: " + myMessageLineEdit->text() );
    }
}

void NetDialog::receiveSlot() {
    while(mySocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(mySocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        mySocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
        QString chatMessage = QString("(%1:%2) %3").arg( sender.toString() ).arg( senderPort ).arg( QString::fromUtf8(datagram.data()) );
        newChatMessage(chatMessage );
    }

}

void NetDialog::newChatMessage(const QString& message) {
    myListWidget->addItem( message );
    myListWidget->scrollToBottom();
}




