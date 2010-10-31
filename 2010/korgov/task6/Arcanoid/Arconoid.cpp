#include "Arconoid.h"

Arconoid::Arconoid(QWidget* parent)
    : QDialog(parent),
      myLives(0),myIsPlaying(0)
{
    mySocket = new QUdpSocket(this);
    createDialog();
    this->setWindowTitle("Arcanoid.");
}

Arconoid::~Arconoid()
{
}

void Arconoid::createDialog(){
    this->setLayout(new QVBoxLayout());

    myBallWgt = new BallWidget(QSize(400,300),this);
    myBindPortLE = new QLineEdit(this);
    myBindBtn = new QPushButton("Bind!",this);
    myControlAddressLE = new QLineEdit(this);
    myControlPortLE = new QLineEdit(this);
    myLivesLabel = new QLabel(this);

    QHBoxLayout *bindLayout = new QHBoxLayout();

    bindLayout->setSpacing(5);
    bindLayout->addWidget(myLivesLabel);
    bindLayout->addStretch(1);
    bindLayout->addWidget(new QLabel("My port:",this));
    myBindPortLE->setMaximumWidth(60);
    myBindPortLE->setValidator(new QIntValidator(0,65535,myBindPortLE));
    bindLayout->addWidget(myBindPortLE);
    bindLayout->addWidget(myBindBtn);
    this->layout()->addItem(bindLayout);

    QHBoxLayout *controlAddressLayout = new QHBoxLayout();
    controlAddressLayout->setSpacing(5);
    controlAddressLayout->addWidget(new QLabel("Control IP:",this));
    controlAddressLayout->addWidget(myControlAddressLE);
    controlAddressLayout->addWidget(new QLabel("port: ",this));
    myControlPortLE->setMaximumWidth(60);
    myControlPortLE->setValidator(new QIntValidator(0,65535,myControlPortLE));
    controlAddressLayout->addWidget(myControlPortLE);
    this->layout()->addItem(controlAddressLayout);
    this->layout()->addWidget(myBallWgt);

    QObject::connect(myBindBtn,SIGNAL(clicked()),this,SLOT(bindPort()));
    QObject::connect(myBallWgt,SIGNAL(gameOver()),this,SLOT(gameOver()));
    QObject::connect(mySocket,SIGNAL(readyRead()),this,SLOT(reciveCommand()));
}

void Arconoid::newGame(){
    myBallWgt->start();
    myIsPlaying = 1;
    if(myLives == 0){
        myLives = 3;
        myLivesLabel->setText("balls: " + QString::number(myLives));
    }
    myTimer = startTimer(20);
}

void Arconoid::gameOver(){
    myIsPlaying = 0;
    myLives--;
    myLivesLabel->setText("balls: " + QString::number(myLives));
    if(myLives == 0){
        QMessageBox::information(this,"GameOver","Game Over!.\nClick start for new game.");
    }
    killTimer(myTimer);
    sendStatus();
}


void Arconoid::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == myTimer){
        sendStatus();
    }
}

void Arconoid::sendStatus(){
    if(myControlAddressLE->text().isEmpty() || myControlPortLE->text().isEmpty()){
        return;
    }

    QDomDocument doc("Status");
    QDomElement root = doc.createElement("Status");
    doc.appendChild(root);

    QDomElement ballCoords = doc.createElement("ballCoords");
    root.appendChild(ballCoords);
    QDomElement ballX = doc.createElement("x");
    QDomElement ballY = doc.createElement("y");
    ballCoords.appendChild(ballX);
    ballCoords.appendChild(ballY);
    ballX.appendChild(doc.createTextNode(QString::number(myBallWgt->getBallCoords().x())));
    ballY.appendChild(doc.createTextNode(QString::number(myBallWgt->getBallCoords().y())));

    QDomElement windowSize = doc.createElement("windowSize");
    root.appendChild(windowSize);
    QDomElement WindowWidth = doc.createElement("width");
    QDomElement WindowHeight = doc.createElement("height");
    windowSize.appendChild(WindowWidth);
    windowSize.appendChild(WindowHeight);
    WindowWidth.appendChild(doc.createTextNode(QString::number(myBallWgt->size().width())));
    WindowHeight.appendChild(doc.createTextNode(QString::number(myBallWgt->size().height())));

    QDomElement platform = doc.createElement("platform");
    root.appendChild(platform);
    QDomElement platformX = doc.createElement("x");
    QDomElement platformWidth = doc.createElement("width");
    platform.appendChild(platformX);
    platform.appendChild(platformWidth);
    platformX.appendChild(doc.createTextNode(QString::number(myBallWgt->getPlatformX())));
    platformWidth.appendChild(doc.createTextNode(QString::number(myBallWgt->getPlatformWidth())));

    QDomElement game = doc.createElement("game");
    root.appendChild(game);
    QDomElement lives = doc.createElement("lives");
    QDomElement isPlaying = doc.createElement("isPlaying");
    game.appendChild(lives);
    game.appendChild(isPlaying);
    lives.appendChild(doc.createTextNode(QString::number(myLives)));
    isPlaying.appendChild(doc.createTextNode(QString::number(myIsPlaying)));

    //qDebug() << doc.toString();

    QString xml = doc.toString();
    mySocket->writeDatagram(xml.toUtf8(),QHostAddress(myControlAddressLE->text()),myControlPortLE->text().toInt());
}

void Arconoid::bindPort(){
    if(!myBindPortLE->text().isEmpty()){
        mySocket->bind(myBindPortLE->text().toInt());
        this->setWindowTitle("Arcanoid. My Port: " + myBindPortLE->text());
    }
}

void Arconoid::reciveCommand(){
    while (mySocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(mySocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        mySocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        if(QString(datagram) == "start"){
            newGame();
        } else if(QString(datagram) == "left"){
            myBallWgt->left();
        } else if(QString(datagram) == "right"){
            myBallWgt->right();
        }
    }
}
