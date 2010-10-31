#include "arkanoidclient.h"

ArkanoidClient::ArkanoidClient(QWidget *parent) :
    QWidget(parent)
{

    connected = false;
    action = "s";
    int port = 20000;
    socket = new QUdpSocket(this);
    while( !socket->bind(port) ) port++;

    left = new QPushButton("Left", this);
    right = new QPushButton("Right", this);
    go = new QPushButton("Go", this);
    connectBtn = new QPushButton("Connect", this);
    ipEdit = new QLineEdit("127.0.0.1", this);
    portEdit = new QLineEdit("10000", this);

    left->setEnabled( false );
    go->setEnabled( false );
    right->setEnabled( false );

    setLayout( new QVBoxLayout() );
    QFormLayout* l1 = new QFormLayout();
    QLayout* l2 = new QHBoxLayout();

    l1->addRow("Server IP", ipEdit);
    l1->addRow("Server port", portEdit);
    l2->addWidget( left );
    l2->addWidget( right );
    layout()->addWidget( connectBtn );
    layout()->addItem( l1 );
    layout()->addWidget( go );
    layout()->addItem( l2 );

    connect( left, SIGNAL(pressed()), this, SLOT(leftPressed()) );
    connect( right, SIGNAL(pressed()), this, SLOT(rightPressed()) );
    connect( go, SIGNAL(pressed()), this, SLOT(goPressed()) );
    connect( connectBtn, SIGNAL(pressed()), this, SLOT(connectPressed()) );
    connect( left, SIGNAL(released()), this, SLOT(buttonReleased()) );
    connect( right, SIGNAL(released()), this, SLOT(buttonReleased()) );
    connect( socket, SIGNAL(readyRead()), this, SLOT(processData()) );

}

#include <QMessageBox>
void ArkanoidClient::processData(){

    QByteArray datagramm;
    datagramm.resize( socket->pendingDatagramSize() );
    socket->readDatagram( datagramm.data(), socket->pendingDatagramSize() );
    QDomDocument doc;
    doc.setContent( datagramm );
    int restrMove = doc.documentElement().attribute("wallRestrictedMoveDir").toInt();
    int active = doc.documentElement().attribute("isActive").toInt();
    int lives = doc.documentElement().attribute("livesRemaining").toInt();
    setWindowTitle( QString::number(lives));
    if (!active && lives >= 0) go->setEnabled( true );
    if ( restrMove < 0 ) left->setEnabled(false);
    if ( restrMove > 0 ) right->setEnabled(false);
    if ( active && restrMove == 0 ){
        left->setEnabled( true );
        right->setEnabled( true );
        go->setEnabled( false );
    }
}


void ArkanoidClient::goPressed(){
    socket->writeDatagram("g", 2, serverIp, serverPort );
}


void ArkanoidClient::connectPressed(){

    bool ok = false;
    serverPort = portEdit->text().toUInt( &ok );

    if ( serverIp.setAddress(ipEdit->text()) && ok ){
        connectBtn->setEnabled( false );
    }

    socket->writeDatagram("c", 2, serverIp, serverPort );
    checkTimerId = startTimer(50);

}


void ArkanoidClient::leftPressed(){
    action = "l";
}


void ArkanoidClient::rightPressed(){
    action = "r";
}

void ArkanoidClient::buttonReleased(){
    action = "s";
}

void ArkanoidClient::timerEvent(QTimerEvent *e){
    if (e->timerId() != checkTimerId){
        return;
    }
    socket->writeDatagram(action.toAscii(), 2, serverIp, serverPort );
}
