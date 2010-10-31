#include <QFile>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtNetwork/QHostAddress>
#include <iostream>

#include "reotecontrol.h"

RecievedState RecievedState::createInstance(QDomDocument *dom) {
    RecievedState recState;

    QDomElement stateEl = dom->namedItem("state").toElement();

    recState.livesLeft = stateEl.attribute("lives").toInt();

    recState.windowWidth = stateEl.attribute("window_width").toInt();
    QDomElement plateEl = stateEl.namedItem("plate").toElement();
    recState.plateX = plateEl.attribute("x").toInt();
    recState.plateW = plateEl.attribute("width").toInt();

    return recState;
}

RemoteControl::RemoteControl(QWidget *parent)
    : QDialog( parent )
{
    loadSettings();
    createDialog();
    createSocket( myPort );
    connectAll();
}

RemoteControl::~RemoteControl()
{

}

void RemoteControl::createDialog() {
    this->setLayout( new QVBoxLayout() );

    livesLeftLabel = new QLabel( this );
    restartButton = new QPushButton( "Restart", this);
    QHBoxLayout * rsLayout = new QHBoxLayout();
    rsLayout->addWidget( livesLeftLabel );
    rsLayout->addWidget( restartButton );

    moveLeftButton = new QPushButton( "Left", this );
    moveRightButton = new QPushButton( "Right", this );
    QHBoxLayout * rlLayout = new QHBoxLayout();
    rlLayout->addWidget( moveLeftButton );
    rlLayout->addWidget( moveRightButton );

    this->layout()->addItem( rsLayout );
    this->layout()->addItem( rlLayout );

    focusKeyboard();
}


void RemoteControl::connectAll() {
    connect( socket, SIGNAL( readyRead() ), this, SLOT( stateRecieved()) );
    connect( restartButton, SIGNAL( pressed() ), this, SLOT( sendRestartCommand()) );
    connect( moveRightButton, SIGNAL( clicked()), this, SLOT( sendRightCommand()) );
    connect( moveLeftButton, SIGNAL( pressed()), this, SLOT( sendLeftCommand()) );
}

void RemoteControl::keyPressEvent( QKeyEvent * e ) {
    if ( ( e->key() == Qt::Key_Left ) && ( state.canMoveLeft() ) ) {
        sendLeftCommand();
    }
    if ( ( e->key() == Qt::Key_Right ) && ( state.canMoveRight() ) ) {
        sendRightCommand();
    }
    if ( ( e->key() == Qt::Key_Space ) && ( state.livesLeft == 0 ) ) {
        sendRestartCommand();
    }

}

void RemoteControl::createSocket( int portNumber ) {
    socket = new QUdpSocket( this );
    if (!socket->bind( portNumber )) {
        throw std::exception();
    }
}

void RemoteControl::loadSettings() {
    QFile inFile( "ipsettings.txt" );

    if ( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) ) return;

    QTextStream inStream(&inFile);
    inStream >> myPort;
    inStream >> toPort;
    inStream.readLine(1);
    inStream >> ip;
}

void RemoteControl::sendMoveCommand( QString direction ) {
    QHostAddress sendHost( ip );
    QString sendText = "<command value=\"" + direction + "\" />";

    socket->writeDatagram( sendText.toAscii(),
                               sendHost,
                               toPort );
}

void RemoteControl::sendRightCommand() {
    sendMoveCommand( "right" );
    focusKeyboard();
}

void RemoteControl::sendLeftCommand()  {
    sendMoveCommand( "left" );
    focusKeyboard();
}

void RemoteControl::sendRestartCommand() {
    QHostAddress sendHost( ip );
    QString sendText = "<restart />";

    socket->writeDatagram( sendText.toAscii(),
                               sendHost,
                               toPort );
    focusKeyboard();
}

void RemoteControl::stateRecieved() {
    quint16 port;
    QHostAddress address;
    recievedData.resize( socket->pendingDatagramSize() );

    socket->readDatagram( recievedData.data(), recievedData.size(),
                              &address,
                              &port );

    QDomDocument stateDom;
    stateDom.setContent( recievedData );

    state = RecievedState::createInstance( &stateDom );
    stateUpdated();
}

void RemoteControl::stateUpdated() {
    livesLeftLabel->setText( "Lives left: " + QString::number( state.livesLeft ) );

    if ( state.livesLeft == 0 ) {
        restartButton->setEnabled( true );
    } else {
        restartButton->setEnabled( false );
    }

    if ( state.canMoveLeft() ) {
        moveLeftButton->setEnabled( true );
    } else {
        moveLeftButton->setEnabled( false );
    }


    if ( state.canMoveRight() ) {
        moveRightButton->setEnabled( true );
    } else {
        moveRightButton->setEnabled( false );
    }
}
