#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>

#include "RemoteControlDialog.h"

RemoteControlDialog::RemoteControlDialog(QHostAddress address, quint16 port,
                                         QHostAddress destinationAddress, quint16 destinationPort,
                                         QWidget *parent) : QDialog(parent) {
    setWindowTitle("Remote Control");
    myDestinationAddress = destinationAddress;
    myDestinationPort = destinationPort;
    createWidgets();
    fillLayout();
    mySocket = new QUdpSocket(this);
    mySocket->bind(address, port);
    connectSignalsAndSlots();
}

void RemoteControlDialog::createWidgets() {
    myStartButton = new QPushButton("Start", this);
    myLeftButton = new QPushButton("<", this);
    myLeftButton->setEnabled(false);
    myRightButton = new QPushButton(">", this);
    myRightButton->setEnabled(false);
}

void RemoteControlDialog::fillLayout() {
    setLayout(new QHBoxLayout());
    layout()->addWidget(myStartButton);
    layout()->addWidget(myLeftButton);
    layout()->addWidget(myRightButton);
}

void RemoteControlDialog::connectSignalsAndSlots() {
    connect(myStartButton, SIGNAL(pressed()), this, SLOT(startGame()));
    connect(myLeftButton, SIGNAL(pressed()), this, SLOT(moveBallToLeft()));
    connect(myRightButton, SIGNAL(pressed()), this, SLOT(moveBallToRight()));
    connect(mySocket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
}

void RemoteControlDialog::startGame() {
    sendDatagram("start");
}

void RemoteControlDialog::moveBallToLeft() {
    sendDatagram("moveLeft");
}

void RemoteControlDialog::moveBallToRight() {
    sendDatagram("moveRight");
}

void RemoteControlDialog::sendDatagram(const QString &command) {
    QDomDocument commandDocument;
    QDomElement element = commandDocument.createElement(command);
    commandDocument.appendChild(element);
    mySocket->writeDatagram(commandDocument.toString().toUtf8(), myDestinationAddress, myDestinationPort);
}

void RemoteControlDialog::readDatagrams() {
    while (mySocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(mySocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        mySocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        if (sender == myDestinationAddress && senderPort == myDestinationPort) {
            processTheDatagram(datagram);
        }
    }
}

void RemoteControlDialog::processTheDatagram(const QByteArray &datagram) {
    QXmlSimpleReader reader;
    StateHandler *stateHandler= new StateHandler();
    reader.setContentHandler(stateHandler);
    QXmlInputSource inputXml;
    inputXml.setData(datagram);
    reader.parse(&inputXml);
    myStartButton->setEnabled(!stateHandler->myStarted);
    myLeftButton->setEnabled(stateHandler->myRacketX > 0 && stateHandler->myStarted);
    myRightButton->setEnabled(stateHandler->myWidth - (stateHandler->myRacketX + stateHandler->myRacketWidth) > 0 && stateHandler->myStarted);
}

bool RemoteControlDialog::StateHandler::startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &attributes) {
    if (name == "state") {
        QString myStartedString = attributes.value("started");
        myStarted = myStartedString == "1";
        myWidth = attributes.value("tableWidth").toInt();
    } else if (name == "x") {
        myRacketX = attributes.value("value").toInt();
    } else if (name == "width") {
        myRacketWidth = attributes.value("value").toInt();
    }
    return true;
}
