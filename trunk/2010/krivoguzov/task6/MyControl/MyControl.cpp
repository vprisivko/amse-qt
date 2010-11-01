#include <MyControl.h>
#include <QHBoxLayout>
#include <QDomDocument>
#include <QXmlInputSource>
#include <StateXmlHandler.h>

MyControl::MyControl(QString destIp, int destPort, int portNumberToListen){

    this->destIp = destIp;
    this->destPort = destPort;
    this->portToListen = portNumberToListen;

    createDialog();
    configureNetwork();

}

//Here we create all out widgets
void MyControl::createDialog(){

    leftButton = new QPushButton("<-");
    rightButton = new QPushButton("->");
    goButton = new QPushButton("GO!");
    pauseButton = new QPushButton("Pause!");
    ballsLeftLabel =  new QLabel("3");
    statusLabel = new QLabel("PAUSE");

    QHBoxLayout *statusAndBallsLay = new QHBoxLayout();
    statusAndBallsLay->addWidget(new QLabel("STATUS: "));
    statusAndBallsLay->addWidget(statusLabel);
    statusAndBallsLay->addWidget(new QLabel("Balls left: "));
    statusAndBallsLay->addWidget(ballsLeftLabel);

    QHBoxLayout *controlsLay = new QHBoxLayout();
    controlsLay->addWidget(leftButton);
    controlsLay->addWidget(rightButton);

    QHBoxLayout *lay = new QHBoxLayout();
    lay->addWidget(goButton);
    lay->addWidget(pauseButton);

    QVBoxLayout *mainLay = new QVBoxLayout();
    mainLay->addLayout(statusAndBallsLay);
    mainLay->addLayout(controlsLay);
    mainLay->addLayout(lay);

    pauseButton->setDisabled(true);
    leftButton->setDisabled(true);
    rightButton->setDisabled(true);

    leftButton->setShortcut(QKeySequence::MoveToPreviousChar);
    rightButton->setShortcut(QKeySequence::MoveToNextChar);

    setLayout(mainLay);
    setMinimumWidth(minimumSizeHint().width()+100);
    setWindowTitle(QString("We are listening on: ").append(QString::number(portToListen)));

    connect(leftButton,SIGNAL(pressed()),this,SLOT(leftButtonPressed()));
    connect(rightButton,SIGNAL(pressed()),this,SLOT(rightButtonPressed()));
    connect(goButton,SIGNAL(pressed()),this,SLOT(goButtonPressed()));
    connect(pauseButton,SIGNAL(pressed()),this,SLOT(pauseButtonPressed()));

}

//Bind the socket, start listening for incoming data
void MyControl::configureNetwork(){

    myUdpSocket = new QUdpSocket();
    if(!myUdpSocket->bind(portToListen)){
         qDebug()<<"Cannot bind socket to port: " <<  portToListen << " please try another port!";
         qDebug()<<"The application wouldn't work properly!\nRestart please!";
     }

    connect(myUdpSocket, SIGNAL(readyRead()), this, SLOT(newStateArrived()));

}

//Here we deserialize and process incoming states
void MyControl::newStateArrived(){

    while (myUdpSocket->hasPendingDatagrams()) {

        QByteArray datagram;
        datagram.resize(myUdpSocket->pendingDatagramSize());
        myUdpSocket->readDatagram(datagram.data(), datagram.size());

        QXmlSimpleReader reader;
        StateXmlHandler* myHandler = new StateXmlHandler();
        reader.setContentHandler(myHandler);
        QXmlInputSource recievedXml;
        recievedXml.setData(datagram);
        reader.parse(recievedXml);

        if(myHandler->isPaused){
            pauseButton->setDisabled(true);
            leftButton->setDisabled(true);
            rightButton->setDisabled(true);
            goButton->setEnabled(true);
            if(statusLabel->text() != "PAUSE")
                statusLabel->setText("PAUSE");
        }
        else{
            if(myHandler->deskPosition <= 0)
                leftButton->setDisabled(true);
            else
                leftButton->setEnabled(true);

            if(myHandler->deskPosition + myHandler->deskWidth >= myHandler->rightBorder)
                rightButton->setDisabled(true);
            else
               rightButton->setEnabled(true);

            goButton->setDisabled(true);
            pauseButton->setEnabled(true);
            if(statusLabel->text() != "PLAYING")
                statusLabel->setText("PLAYING");
        }

        if(myHandler->lifesLeft != ballsLeftLabel->text().toInt())
            ballsLeftLabel->setText(QString::number(myHandler->lifesLeft));

        if(myHandler->lifesLeft == 0 && goButton->text() == "GO!"){
            goButton->setText("Play Again!");
        } else if(myHandler->lifesLeft != 0 && goButton->text() == "Play Again!"){
            goButton->setText("GO!");
        }


    }
}

//Send control data
void MyControl::sendControlData(QByteArray dataToSend){

        QByteArray datagram = dataToSend;
        myUdpSocket->writeDatagram(datagram, QHostAddress(destIp), destPort);
}

//Here we serialize our control data using DOM XML
QByteArray MyControl::createDomByteArray(int whatButtonWasPressed){

    QDomDocument doc("Control");
    QDomElement root = doc.createElement("Control");
    doc.appendChild(root);

    QDomElement tag[4];
    tag[0] = doc.createElement("Left");
    tag[1] = doc.createElement("Right");
    tag[2] = doc.createElement("GoButton");
    tag[3] = doc.createElement("Pause");

    for(int i = 0; i < 4; i++){
        root.appendChild(tag[i]);
    }

    QDomAttr atr[4];
    for(int i = 0; i < 4; i++){
        atr[i] = doc.createAttribute("isPressed");
        atr[i].setValue("0");
        tag[i].setAttributeNode(atr[i]);
    }
    atr[whatButtonWasPressed].setValue("1");

    return doc.toByteArray();
}

void MyControl::leftButtonPressed(){

    sendControlData( createDomByteArray(0) );

}

void MyControl::rightButtonPressed(){

    sendControlData( createDomByteArray(1) );

}

void MyControl::goButtonPressed(){

    sendControlData( createDomByteArray(2) );

}

void MyControl::pauseButtonPressed(){

    sendControlData( createDomByteArray(3) );

}
