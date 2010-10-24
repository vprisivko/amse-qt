#include "ChatDialog.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QtNetwork/QUdpSocket>
#include<QByteArray>

UDPChatDialog :: UDPChatDialog( QWidget* parent, int newPort ) : QDialog( parent ), port( newPort ){
    setWindowTitle( "Chat" );
    createWidgets();
    createSocket();
    addWidgets();
    setConnection();
}

void UDPChatDialog :: createWidgets() {
    messageList = new QListWidget( this );
    ipLabel = new QLabel( "IP: ", this );
    ipTextBox = new QLineEdit( this );
    //ipTextBox->setText( "127.0.0.1" );
    portLabel = new QLabel( "PORT: ", this );
    portTextBox = new QLineEdit( this );
    messageLabel = new QLabel( "TEXT: ", this );
    messageTextBox = new QTextEdit( this );
    sendButton = new QPushButton( "SEND", this );
}

void UDPChatDialog :: createSocket(){
    udpSocket = new QUdpSocket( this );
    if( !udpSocket->bind( port ) ){
        printf("Sorry, this port is unavailable. Enter another one.\n");
        exit(-1);
    }
}

void UDPChatDialog :: addWidgets(){
    setLayout( new QVBoxLayout() );
    layout()->addWidget( messageList );
    QHBoxLayout* ipAndPortLayout = new QHBoxLayout();
    ipAndPortLayout->addWidget( ipLabel );
    ipAndPortLayout->addWidget( ipTextBox );
    ipAndPortLayout->addWidget( portLabel );
    ipAndPortLayout->addWidget( portTextBox );
    layout()->addItem( ipAndPortLayout );
    QHBoxLayout* textAndSendLayout = new QHBoxLayout();
    textAndSendLayout->addWidget( messageLabel );
    textAndSendLayout->addWidget( messageTextBox );
    textAndSendLayout->addWidget( sendButton );
    layout()->addItem( textAndSendLayout );
}

void UDPChatDialog :: setConnection(){
    connect( udpSocket, SIGNAL( readyRead() ), this, SLOT( readMessage() ) );
    connect( sendButton, SIGNAL( clicked() ), this, SLOT( writeMessage() ) );

}

void UDPChatDialog :: writeMessage(){
    QByteArray datagram;
    QString newMessage = messageTextBox->toPlainText();
    datagram.append( newMessage );
    QHostAddress hostAddr( ipTextBox->text() );
    quint16 port = portTextBox->text().toInt();
    udpSocket->writeDatagram( datagram, hostAddr, port);
    QString message = "Me:\t";
    message += datagram.data();
    messageList->addItem( message );
    messageTextBox->setPlainText( "" );
}

void UDPChatDialog :: readMessage(){
    while ( udpSocket->hasPendingDatagrams() ) {
                QByteArray datagram;
                datagram.resize( udpSocket->pendingDatagramSize() );
                QHostAddress host;
                quint16 port;
                udpSocket->readDatagram( datagram.data(), datagram.size(), &host, &port );
                messageList->addItem( host.toString() + ":\t" + datagram.data() ) ;
            }
}
