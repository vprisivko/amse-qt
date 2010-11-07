#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtXml/QXmlInputSource>
#include <QtXml/QDomDocument>

#include "ControlDialog.h"

ControlDialog :: ControlDialog( QHostAddress& ip, int port, QWidget* parent ) : QDialog( parent ){
    setWindowTitle("Arcanoid : Controller");
    setFixedSize( DIALOG_WIDTH, DIALOG_HEIGHT );

    myAddress = ip;
    myPort = port;

    ballsInReserve = BALLS_IN_RESERVE;

    createWidgets();
    addWidgets();
    createSocket();
    setConnection();

}

void ControlDialog :: createWidgets(){
    ipLabel = new QLabel( "IP: ", this );
    portLabel = new QLabel( "PORT: ", this );
    infoLabel = new QLabel( " Input ip address, port  and press 'CONNECT'. " , this );

    ipTextBox = new QLineEdit( this );
    portTextBox = new QLineEdit( this );

    leftButton = new QPushButton( "LEFT", this );
    rightButton = new QPushButton( "RIGHT", this );
    goButton = new QPushButton( "GO!", this );
    connectButton = new QPushButton( "CONNECT", this );
}

void ControlDialog :: addWidgets(){
    setLayout( new QVBoxLayout() );

    QHBoxLayout* ipAndPortLayout = new QHBoxLayout();
    ipAndPortLayout->addWidget( ipLabel );
    ipAndPortLayout->addWidget( ipTextBox );
    ipAndPortLayout->addWidget( portLabel );
    ipAndPortLayout->addWidget( portTextBox );
    ipAndPortLayout->addWidget( connectButton );
    layout()->addItem( ipAndPortLayout );

    QHBoxLayout* ctrlButtonsLayout = new QHBoxLayout();
    ctrlButtonsLayout->addWidget( leftButton );
    ctrlButtonsLayout->addWidget( rightButton );
    ctrlButtonsLayout->addWidget( goButton );
    layout()->addItem( ctrlButtonsLayout );

    layout()->addWidget( infoLabel );
    leftButton->setEnabled(false);
    rightButton->setEnabled(false);
    goButton->setEnabled(false);
    connectButton->setEnabled(true);
}

void ControlDialog :: createSocket(){
    udpSocket = new QUdpSocket( this );
    if( !udpSocket->bind( myAddress, myPort ) ){
        printf( "Sorry, this port is unavailable. Enter another one.\n" );
        exit(-1);
    }
}

void ControlDialog :: setConnection(){
    connect( connectButton, SIGNAL( pressed() ), this, SLOT( setIpAndPort() ) );

    connect( goButton, SIGNAL( pressed() ), this, SLOT( start() ) );
    connect( leftButton, SIGNAL( pressed() ), this, SLOT( left() ) );
    connect( rightButton, SIGNAL( pressed() ), this, SLOT( right() ) );
    connect( udpSocket, SIGNAL( readyRead() ), this, SLOT( readDatagrams() ) );
}

void ControlDialog :: keyPressEvent( QKeyEvent* event){
    if( event->key() == Qt::Key_A ){
        leftButton->click();
    }else if( event->key() == Qt::Key_D ){
        rightButton->click();
    }
}

void ControlDialog :: setIpAndPort(){
    QHostAddress host( ipTextBox->text() );
    hostAddress = host;
    arcanoidPort = portTextBox->text().toInt();

    connectButton->setEnabled( false );
    goButton->setEnabled( true );
    infoLabel->setText( "Press 'GO!' ." );
}

void ControlDialog :: start(){
    QDomDocument datagram;
    QDomElement command = datagram.createElement( "start" );
    datagram.appendChild( command );
    udpSocket->writeDatagram( datagram.toString().toUtf8(), hostAddress, arcanoidPort );

    infoLabel->setText( QString::number( BALLS_IN_RESERVE - ballsInReserve ) + " ball(s) out, 1 ball active, "
                        + QString::number( ballsInReserve - 1 ) + " ball(s) in reserve...");
}

void ControlDialog :: left(){
    QDomDocument datagram;
    QDomElement command = datagram.createElement( "move" );
    command.setAttribute( "direction" , -1);
    datagram.appendChild( command );
    udpSocket->writeDatagram( datagram.toString().toUtf8(), hostAddress, arcanoidPort );
}

void ControlDialog :: right(){
    QDomDocument datagram;
    QDomElement command = datagram.createElement( "move" );
    command.setAttribute( "direction", 1 );
    datagram.appendChild( command );
    udpSocket->writeDatagram( datagram.toString().toUtf8(), hostAddress, arcanoidPort );
}

void ControlDialog ::readDatagrams(){
    while ( udpSocket->hasPendingDatagrams() ) {
        QByteArray datagram;
        datagram.resize( udpSocket->pendingDatagramSize() );
        QHostAddress host;
        quint16 port;
        udpSocket->readDatagram( datagram.data(), datagram.size(), &host, &port );
        parseData( datagram );
    }
}

void ControlDialog :: parseData( const QByteArray& data ){
    ControlDialog :: XmlHandler* xmlHandler = new ControlDialog :: XmlHandler();

    QXmlInputSource buffer;
    buffer.setData(data);

    QXmlSimpleReader reader;
    reader.setContentHandler( xmlHandler );
    reader.parse( &buffer );

    if ( xmlHandler->gameBegins == 1 ) {
        goButton->setEnabled( false );
        leftButton->setEnabled( true );
        rightButton->setEnabled( true );
    }
    if ( xmlHandler->gameOver == 1) {
        leftButton->setEnabled( false );
        rightButton->setEnabled( false );

        --ballsInReserve;

        if ( ballsInReserve > 0) {
            infoLabel->setText( QString::number( BALLS_IN_RESERVE - ballsInReserve ) + " ball(s) out, 0 balls active, "
                        + QString::number( ballsInReserve ) + " ball(s) in reserve...");
            goButton->setEnabled( true );
        } else if ( ballsInReserve == 0 ){
            infoLabel->setText( "0 balls in reserve... Game is over!" );
            goButton->setEnabled( false );
        }
    }
}

bool ControlDialog :: XmlHandler :: startElement(const QString&, const QString&,
                                                const QString &name, const QXmlAttributes &attrs) {
        if ( name == "state" ) {
                gameBegins = attrs.value( "begins" ).toInt();
                gameOver = attrs.value( "gameover" ).toInt();
        }

        return true;
}
