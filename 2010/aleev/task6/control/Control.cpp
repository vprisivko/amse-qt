#include <QApplication>
#include <QHBoxLayout>
#include <QSettings>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QRegExp>
#include <QMessageBox>
#include <QByteArray>
#include <QDebug>
#include <qt4/QtCore/qdatetime.h>

#include "Control.h"

ControlDialog::ControlDialog(quint16 port, QWidget *parent) : QDialog(parent) {
    setWidgets();
    setValidators();
    initSocket(port);
    createConnects();
}

void ControlDialog::setWidgets() {
    setWindowTitle("Controller.");
    setLayout(new QVBoxLayout());

    QHBoxLayout* horLayout1 = new QHBoxLayout();
    QHBoxLayout* horLayout2 = new QHBoxLayout();
    layout()->addItem(horLayout1);
    layout()->addItem(horLayout2);

    myIPLineEdit = new QLineEdit("192.168.44.11",this);
    horLayout1->addWidget(myIPLineEdit);
    horLayout1->setSpacing(5);

    myPortLineEdit = new QLineEdit("10000",this);
    horLayout1->addWidget(myPortLineEdit);

    myStartButton = new QPushButton("Start game", this);
    horLayout1->setSpacing(10);
    horLayout1->addWidget(myStartButton);

    myLeftButton = new QPushButton("Left",this);
    myLeftButton->setEnabled(false);
    myRightButton = new QPushButton("Right",this);
    myRightButton->setEnabled(false);
    horLayout2->addWidget(myLeftButton);
    horLayout2->addWidget(myRightButton);
}

void ControlDialog::setValidators() {
    myPortLineEdit->setValidator( new QIntValidator(0,65535,this) );
}

void ControlDialog::createConnects() {
    connect(myLeftButton, SIGNAL(pressed()), this, SLOT(leftButtonPressed()));
    connect(myRightButton, SIGNAL(pressed()), this, SLOT(rightButtonPressed()));
    connect(myLeftButton, SIGNAL(released()), this, SLOT(directionButtonReleased()));
    connect(myRightButton, SIGNAL(released()), this, SLOT(directionButtonReleased()));

    connect(myStartButton, SIGNAL(clicked()), this, SLOT(startButtonPressed()));
    connect(mySocket, SIGNAL(readyRead()), this, SLOT(receiveSlot()));

}

void ControlDialog::initSocket(quint16 port) {
    mySocket = new QUdpSocket(this);
    bool result = mySocket->bind(port);
    if (result == true) {
        setWindowTitle(windowTitle() + " Your port is " + QString::number(port));
    } else {
        QMessageBox::critical(this, "Error", "Can't use this port!\nPlease, choose another one");
        throw std::exception();
    }
}

void ControlDialog::leftButtonPressed() {
    sendCommand("left");
}

void ControlDialog::rightButtonPressed() {
    sendCommand("right");
}

void ControlDialog::startButtonPressed() {
   sendCommand("start");
}

void ControlDialog::directionButtonReleased() {
    sendCommand("stop");
}


void ControlDialog::sendCommand(QString cmd) {
    QHostAddress address(myIPLineEdit->text());
    if (address.toString() == "") {
        QMessageBox::critical(this, "Error", "IP address is wrong!");
        return;
    }
    quint16 port = myPortLineEdit->text().toInt();

    QDomDocument commandDocument;
    QDomElement commandElement = commandDocument.createElement("command");
    commandElement.setAttribute("name", cmd);
    commandDocument.appendChild(commandElement);

    qint64 result = mySocket->writeDatagram(commandDocument.toString().toUtf8(), address, port);
    if (result == -1) {
        QMessageBox::critical(this, "Error", mySocket->errorString());
    }
}

void ControlDialog::receiveSlot() {
    while(mySocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(mySocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        mySocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        State state;
        QXmlSimpleReader parser;
        StateXmlHandler handler(&state);
        parser.setContentHandler(&handler);
        QXmlInputSource source;
        source.setData(QString::fromUtf8(datagram.data()));
        parser.parse(source);

        processState(state);
    }
}

void ControlDialog::processState(const ControlDialog::State& state) {
    if (state.started == false) {
       myStartButton->setEnabled(true);
       myLeftButton->setEnabled(false);
       myRightButton->setEnabled(false);
    } else {
        myStartButton->setEnabled(false);
        if (state.racketX + state.racketWidth < state.windowWidth) {
            myRightButton->setEnabled(true);
        } else {
            myRightButton->setEnabled(false);
        }
        if (state.racketX > 0) {
            myLeftButton->setEnabled(true);
        } else {
            myLeftButton->setEnabled(false);
        }
    }
}

ControlDialog::StateXmlHandler::StateXmlHandler(State* state) {
    myState = state;
}

bool ControlDialog::StateXmlHandler::startElement(const QString &, const QString &, const QString &qName, const QXmlAttributes &atts) {
    if (qName == "game") {
        myState->started = atts.value("started").toInt();
        myState->windowHeight = atts.value("height").toInt();
        myState->windowWidth = atts.value("width").toInt();
    }
    if (qName == "racket") {
        myState->racketX = atts.value("x").toInt();
        myState->racketWidth = atts.value("width").toInt();
    }
    if (qName == "ball") {
        myState->ballX = atts.value("x").toInt();
        myState->ballY = atts.value("y").toInt();
    }

    return true;
}
