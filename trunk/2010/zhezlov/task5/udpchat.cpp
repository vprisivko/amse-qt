#include "udpchat.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

UdpChat::UdpChat(QWidget *parent) :
    QWidget(parent)
{

    socket = new QUdpSocket(this);

    createWidgets();
    placeItemsOnLayouts();
    bindSocket();
    connectSigSlots();


}


void UdpChat::createWidgets(){

    msgScrollArea = new QScrollArea(this);
    messageArea = new QWidget(msgScrollArea);
    ipEdit = new QLineEdit("127.0.0.1", this);
    portEdit = new QLineEdit(this);
    messageTextEdit = new QTextEdit(this);
    sendButton = new QPushButton("Send", this);

}


void UdpChat::placeItemsOnLayouts(){

    setLayout( new QVBoxLayout() );
    setMinimumSize( 400, 300 );

    QHBoxLayout* netAddrLayout = new QHBoxLayout();
    QHBoxLayout* messageControlLayout = new QHBoxLayout();

    netAddrLayout->addWidget( ipEdit );
    netAddrLayout->addWidget( portEdit );
    messageControlLayout->addWidget( messageTextEdit );
    messageControlLayout->addWidget( sendButton );

    layout()->addWidget( msgScrollArea );
    layout()->addItem( netAddrLayout );
    layout()->addItem( messageControlLayout );

    msgScrollArea->setWidget( messageArea );
    msgScrollArea->setMinimumHeight( 200 );

    messageArea->setLayout( new QVBoxLayout() );
    messageArea->layout()->setSpacing( 10 );
    messageArea->layout()->setAlignment( Qt::AlignTop );

}


void UdpChat::connectSigSlots(){

    connect( sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()) );
    connect( socket, SIGNAL(readyRead()), this, SLOT(dataAtSocket()) );

}


void UdpChat::bindSocket(){

    int port = 10101;

    while ( socket->bind(port) == false ) port++;

    portEdit->setText( "Local port: " + QString::number(port) );

}


void UdpChat::newMessage( QByteArray& msg ){

    messageArea->layout()->addWidget( new QLabel( QString::fromUtf8( msg ), messageArea) );
    messageArea->layout()->setSizeConstraint( QLayout::SetMinAndMaxSize );

}


void UdpChat::sendMessage(){

    bool portOk = false;
    QHostAddress ip( ipEdit->text() );
    int port = portEdit->text().toInt( &portOk, 10 );

    if ( !portOk || ip.isNull() ){
        QMessageBox::warning( this, "Parse error", "Specify valid ip/port",
                              QMessageBox::Close, QMessageBox::Close);
        return;
    }

    if ( messageTextEdit->toPlainText() == "" ){
        return;
    }

    QByteArray msg = messageTextEdit->toPlainText().trimmed().toUtf8();
    socket->writeDatagram( msg, ip, port );
    newMessage( msg );
    messageTextEdit->setText("");

}


void UdpChat::dataAtSocket(){

    qint64 size = socket->pendingDatagramSize();
    char* buffer;

    //some magic//////////////////
    buffer = new char[size+1];  //
    buffer[size] = 0;           //
    //buffer = new char[size];  //  <-- this line _should_ be enough, but it isn't


    socket->readDatagram( buffer, size );
    QByteArray data = QByteArray::fromRawData( buffer, size+1 );
    newMessage( data );

}
