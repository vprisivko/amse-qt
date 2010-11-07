#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>


#include "ArcanoidDialog.h"

ArcanoidDialog :: ArcanoidDialog( QHostAddress& ip, int port, QWidget *parent ): QDialog( parent ) {

    setWindowTitle( "Arcanoid : Play Ground" );
    setFixedSize( DIALOG_WIDTH, DIALOG_HEIGHT );

    ballsInReserve = BALLS_IN_RESERVE;
    myPort = port;
    myAddress = ip;
    isStarted = 0;
    isGameOver = 0;

    createWidgets();
    addWidgets();
    createSocket();
    setConnection();
}

void ArcanoidDialog :: createWidgets(){
    ipLabel = new QLabel( "IP: ", this );
    portLabel = new QLabel( "PORT: ", this );
    infoLabel = new QLabel( "Set ip, port of remote controller and press 'CONNECT'.", this );

    ipTextBox = new QLineEdit( this );
    portTextBox = new QLineEdit( this );
    connectButton = new QPushButton( "CONNECT", this );

    myGame = new BallWidget( this );
}

void ArcanoidDialog :: addWidgets(){
    setLayout( new QVBoxLayout( this ) );
    layout()->addWidget( myGame );

    QHBoxLayout* ipAndPortLayout = new QHBoxLayout();
    ipAndPortLayout->addWidget( ipLabel );
    ipAndPortLayout->addWidget( ipTextBox );
    ipAndPortLayout->addWidget( portLabel );
    ipAndPortLayout->addWidget( portTextBox );
    ipAndPortLayout->addWidget( connectButton );
    layout()->addItem( ipAndPortLayout );

    layout()->addWidget( infoLabel );
}

void ArcanoidDialog :: createSocket(){
    udpSocket = new QUdpSocket( this );
    if( !udpSocket->bind( myAddress, myPort ) ){
        printf( "Sorry, this port is unavailable. Enter another one.\n" );
        isStarted = 0;
    }
}

void ArcanoidDialog :: setConnection(){
    connect( udpSocket, SIGNAL( readyRead() ), this, SLOT( readDatagrams() ) );
    connect( connectButton, SIGNAL( pressed() ), this, SLOT( setIpAndPort() ) );

    connect( myGame, SIGNAL( gameover() ), this, SLOT( gameOver() ) );
    connect( this, SIGNAL( left() ), this->myGame, SLOT( moveLeft() ) );
    connect( this, SIGNAL( right() ), this->myGame, SLOT( moveRight() ) );
    connect( this, SIGNAL( start() ), this->myGame, SLOT( start() ) );
}

void ArcanoidDialog :: setIpAndPort(){
    QHostAddress host( ipTextBox->text() );
    hostAddress = host;
    ctrlPort = portTextBox->text().toInt();

    connectButton->setEnabled( false );
    infoLabel->setText( "" );
}

QDomDocument ArcanoidDialog :: serialize() {
        QDomDocument datagram;
        QDomElement state = datagram.createElement( "state" );
        state.setAttribute( "begins", isStarted);
        state.setAttribute( "gameover", isGameOver);
        datagram.appendChild( state );
        return datagram;
}

void ArcanoidDialog :: send() {
	QDomDocument datagram = this->serialize();
        udpSocket->writeDatagram( datagram.toString().toUtf8(), hostAddress, ctrlPort );
}

void ArcanoidDialog :: gameOver() {
	isGameOver = 1;
	this->send();
        isGameOver = 0;
}

void ArcanoidDialog :: readDatagrams() {
        while ( udpSocket->hasPendingDatagrams() ) {
            QByteArray datagram;
            datagram.resize( udpSocket->pendingDatagramSize() );
            QHostAddress host;
            quint16 port;
            udpSocket->readDatagram( datagram.data(), datagram.size(), &host, &port );
            parseData( datagram );
	}
}

void ArcanoidDialog :: parseData( const QByteArray &data ) {
        ArcanoidDialog::XmlHandler* xmlHandler = new ArcanoidDialog::XmlHandler();

        QXmlSimpleReader reader;
        reader.setContentHandler( xmlHandler );
	QXmlInputSource buffer;
        buffer.setData( data );
        reader.parse( &buffer );

        myDirection = xmlHandler->my_direction;
        if ( myDirection == -1 ) {
		emit left();
	}
        if ( myDirection == 1 ) {
		emit right();
	}

	isStarted = xmlHandler->is_started;
        if ( isStarted == 1 ) {
		emit start();
	}

	this->send();
}

bool ArcanoidDialog :: XmlHandler :: startElement( const QString&, const QString&,
                                                const QString &name, const QXmlAttributes &attrs ) {
        if ( name == "start" ) {
		is_started = true;
	} else {
		is_started = false;
	}
        if ( name == "move" ) {
                my_direction = attrs.value( "direction" ).toInt();
	}

	return true;
}
