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

#include "ControlDialog.h"

ControlDialog::ControlDialog(quint16 port, QWidget *parent) : QDialog(parent) {
    setupUI();
    setValidators();
    loadSettings();
    initSocket(port);
    createConnects();
}

ControlDialog::~ControlDialog() {
    saveSettings();
}

void ControlDialog::setupUI() {
    setWindowTitle( "Control Box" );
    setLayout( new QVBoxLayout() );


    //layouts
    QHBoxLayout* horLayout1 = new QHBoxLayout();
    QHBoxLayout* horLayout2 = new QHBoxLayout();
    layout()->addItem(horLayout1);
    layout()->addItem(horLayout2);

    //IP line edit
    myIPLineEdit = new QLineEdit("127.0.0.1",this);
    horLayout1->addWidget(myIPLineEdit);
    horLayout1->setSpacing(5);

    //port line edit
    myPortLineEdit = new QLineEdit("1025",this);
    horLayout1->addWidget(myPortLineEdit);

     //start button
    myStartButton = new QPushButton("start", this);
    horLayout1->setSpacing(10);
    horLayout1->addWidget(myStartButton);

    //left and right buttons
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

void ControlDialog::loadSettings() {
    mySettings = new QSettings("turkin","task5",this);
    if ( mySettings->contains("geometry") ) {
        setGeometry( mySettings->value("geometry").toRect() );
    }
}
void ControlDialog::saveSettings() {
    mySettings->setValue("geometry", geometry() );
}

void ControlDialog::createConnects() {
    connect( myLeftButton, SIGNAL(pressed()), this, SLOT(leftButtonPressed()) );
    connect( myRightButton, SIGNAL(pressed()), this, SLOT(rightButtonPressed()) );
    connect( myLeftButton, SIGNAL(released()), this, SLOT(directionButtonReleased()) );
    connect( myRightButton, SIGNAL(released()), this, SLOT(directionButtonReleased()) );

    connect( myStartButton, SIGNAL(clicked()), this, SLOT(startButtonPressed()) );
    connect( mySocket,SIGNAL(readyRead()),this,SLOT(receiveSlot()));

}

void ControlDialog::initSocket(quint16 port) {
    mySocket = new QUdpSocket(this);
    bool result = mySocket->bind(port);
    if (result == true) {
        
        setWindowTitle( windowTitle() + " at port " + QString::number(port) );
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


void ControlDialog::sendCommand(QString command) {

    QHostAddress address(myIPLineEdit->text());
    if ( address.toString() == "") {
        QMessageBox::critical(this, "Error", "IP address is wrong!");
        return;
    }
    quint16 port = myPortLineEdit->text().toInt();

    QDomDocument commandDocument;
    QDomElement commandElement = commandDocument.createElement("command");
    commandElement.setAttribute("name", command);
    commandDocument.appendChild(commandElement);

    qint64 result = mySocket->writeDatagram(commandDocument.toString().toUtf8(),address,port);
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
        mySocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);

        State state;
        QXmlSimpleReader parser;
        StateXmlHandler handler(&state);
        parser.setContentHandler(&handler);
        QXmlInputSource source;
        source.setData( QString::fromUtf8( datagram.data() )  );
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
        if (state.padX + state.padWidth < state.windowWidth) {
            myRightButton->setEnabled(  true );
        } else {
            myRightButton->setEnabled(  false );
        }
        if ( state.padX > 0 ) {
            myLeftButton->setEnabled( true );
        } else {
            myLeftButton->setEnabled( false );
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
    if (qName == "pad") {
        myState->padX = atts.value("x").toInt();
        myState->padWidth = atts.value("width").toInt();
    }
    if (qName == "ball") {
        myState->ballX = atts.value("x").toInt();
        myState->ballY = atts.value("y").toInt();
    }
    return true;
}