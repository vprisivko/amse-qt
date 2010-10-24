#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtNetwork/QHostAddress>

#include "chatdialog.h"


ChatDialog::ChatDialog( int portNumber, QWidget *parent)
    : QDialog(parent)
{

    createSocket( portNumber );
    createChatDialog();
    connectAll();
}

ChatDialog::~ChatDialog()
{

}

void ChatDialog::recieveMessage() {
    quint16 port;
    QHostAddress * address = new QHostAddress();
    memset( recievedData, '\0', MAX_LEN );
    chatSocket->readDatagram( recievedData, MAX_LEN,
                              address,
                              &port );
    addChatMessage( QString(recievedData), address->toString() );
}

void ChatDialog::sendMessage() {
    quint16 port = linePortNumber->text().toInt();
    QByteArray sendText("");
    sendText.append( lineMessage->text() );
    QHostAddress sendHost( lineIP->text() );

    chatSocket->writeDatagram( sendText,
                               sendHost,
                               port );
    addChatMessage( lineMessage->text(), "You" );
    lineMessage->setText("");
}

void ChatDialog::addChatMessage( QString msg, QString from ) {
    chatList->addItem( from + ": " + msg );
    emit newLineInChat();
}

void ChatDialog::connectAll() {
    connect( chatSocket, SIGNAL( readyRead() ), this, SLOT( recieveMessage()) );
    connect( sendButton, SIGNAL( pressed() ), this, SLOT( sendMessage() ) );
    connect( this, SIGNAL( newLineInChat() ), chatList, SLOT( scrollToBottom() ) );
}

void ChatDialog::createSocket( int portNumber ) {
    chatSocket = new QUdpSocket( this );
    if (!chatSocket->bind( portNumber )) {
        throw std::exception();
    }

    recievedData = new char[ MAX_LEN ];

}

void ChatDialog::createChatDialog() {
    this->setLayout( new QVBoxLayout(this) );

    chatList = new QListWidget( this );

    QHBoxLayout * networkLayout = new QHBoxLayout( this );
    lineIP = new QLineEdit( this );
    linePortNumber = new QLineEdit( this );
    networkLayout->addWidget( new QLabel( "IP address", this ) );
    networkLayout->addWidget( lineIP );
    networkLayout->addWidget( new QLabel( "Port number", this ) );
    networkLayout->addWidget( linePortNumber );

    QHBoxLayout * messageLayout = new QHBoxLayout( this );
    lineMessage = new QLineEdit( this );
    sendButton = new QPushButton( "Send", this );
    messageLayout->addWidget( lineMessage );
    messageLayout->addWidget( sendButton );

    this->layout()->addWidget( chatList );
    this->layout()->addItem( networkLayout );
    this->layout()->addItem( messageLayout );
}
