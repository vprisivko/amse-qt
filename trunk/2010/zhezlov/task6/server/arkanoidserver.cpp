#include "arkanoidserver.h"
#include <QMessageBox>

ArkanoidServer::ArkanoidServer(QWidget *parent) :
    QMainWindow(parent)
{

    socket = new QUdpSocket(this);
    int port = 10000;
    while( !socket->bind(port) ) port++;
    QMessageBox( QMessageBox::Information, "Port", "Local port is " + QString::number(port), QMessageBox::Ok, this ).exec();

    world = new ArkanoidWorld(this);

    menuBar()->addAction("Go", world, SLOT(go()));

    setCentralWidget( world );

    connect( socket, SIGNAL(readyRead()), this, SLOT(processNewData()) );

}


void ArkanoidServer::sendState(){

    socket->writeDatagram( world->getState().toByteArray(), clientIp, clientPort );

}


void ArkanoidServer::processNewData(){

    QByteArray datagramm;

    datagramm.resize( socket->pendingDatagramSize() );
    socket->readDatagram( datagramm.data(), socket->pendingDatagramSize(), &clientIp, &clientPort );

    char what = datagramm.at(0);

    switch( what ){
    case 'l':
        world->setWallMovement( -1 );
        break;
    case 'r':
        world->setWallMovement( 1 );
        break;
    case 's':
        world->setWallMovement( 0 );
        break;
    case 'g':
        world->go();
        break;
    case 'c':
        sendTimerId = startTimer( 100 );
    }

}


void ArkanoidServer::timerEvent(QTimerEvent *e){
    if (e->timerId() == sendTimerId){
        sendState();
    }
}
