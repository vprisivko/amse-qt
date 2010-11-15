#include <QDebug>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QRadialGradient>
#include <QLinearGradient>
#include <QUdpSocket>
#include <QMessageBox>
#include <QTime>

#include "Game.h"

static const int SEND_STATE_TIME = 100;
static const int MOVE_BALL_TIME = 10;
static const int RACKET_SPEED = 5;
static const int MAX_BALL_X_SPEED = 2;
static const int MAX_BALL_Y_SPEED = 2;

GameDialog::GameDialog(quint16 port, QWidget *parent): QDialog(parent), defRadius(16) {
    setFixedSize(460, 400);
    setWindowTitle("Flying ball and racket.");
    initSocket(port);
    setTimers();
    createConnects();
    toStartPosition();
    myLives = 3;
}

void GameDialog::initSocket(quint16 port) {
    mySocket = new QUdpSocket(this);
    bool result = mySocket->bind(port);
    if (result == true) {
        setWindowTitle(windowTitle() + " Your port is " + QString::number(port));
    } else {
        QMessageBox::critical(this, "Error", "Can't use this port!\nPlease, choose another one");
        throw std::exception();
    }
}

void GameDialog::setTimers() {
    mySendStateTimer = new QTimer(this);
    mySendStateTimer->start(SEND_STATE_TIME);
    myMovingBallTimer = new QTimer(this);
    myMovingBallTimer->start(MOVE_BALL_TIME);
}

void GameDialog::createConnects() {
    connect( mySocket,SIGNAL(readyRead()),this,SLOT(receiveSlot()));
    connect( mySendStateTimer, SIGNAL(timeout()), this, SLOT(sendStateSlot()));
    connect( myMovingBallTimer, SIGNAL(timeout()), this, SLOT(moveBallSlot()));
    connect( myMovingBallTimer, SIGNAL(timeout()), this, SLOT(moveRacketSlot()));
}

void GameDialog::toStartPosition() {
    myRacket.height = 12;
    myRacket.width = 80;
    myRacket.x = width() / 2 - myRacket.width / 2;
    myRacket.y = height() - myRacket.height ;
    myRacket.dx = 0;

    myBall.curRadius = QSize(defRadius,defRadius);
    myBall.coord = QPoint( myRacket.x + myRacket.width / 2 , myRacket.y - myBall.curRadius.height() );

    myBall.dx = myBall.dy = 0;
    myGameStarted = false;
}

void GameDialog::moveBallSlot() {
    int x = myBall.coord.x(), y = myBall.coord.y();
    int rx = myBall.curRadius.width();
    int ry = myBall.curRadius.height();
    int windowHeight = height();
    int windowWidth = width();

    x += myBall.dx;
    y += myBall.dy;

    if (x > windowWidth - defRadius/2) {
        x = windowWidth - defRadius/2;
    }
    if (y > windowHeight - defRadius/2) {
        y = windowHeight - defRadius/2;
    }

    if (x < defRadius) {
        rx = x;
    } else {
        if (x + defRadius > windowWidth) {
                rx = windowWidth - x;
        } else {
                rx = defRadius;
        }
    }
    if (rx <= defRadius/2) {
        myBall.dx = -myBall.dx;
    }

   if (y < defRadius) {
            ry = y;
    } else {

        if (y + defRadius > windowHeight) {
            lostBall();
            return;
        } else {
            ry = defRadius;
        }
        
    }
  
    if ( myRacket.x + rx <= x && x <= myRacket.x + myRacket.width -rx ) {
        if (y + defRadius > windowHeight - myRacket.height) {
            ry = windowHeight - y - myRacket.height;
        }
    }
    
    if (ry <= defRadius/2) {
        myBall.dy = -myBall.dy;
    }

    //if ball is near both of edges
    if (rx < defRadius && ry < defRadius) {
        rx = defRadius;
        ry = defRadius;
    }

    myBall.coord = QPoint(x,y);
    myBall.curRadius = QSize(rx,ry);

    update();
}

void GameDialog::lostBall() {
    --myLives;
    if (myLives == 0) {
        QMessageBox::critical(this, "Game over!", "You've lost all lives");
        myLives = 3;
        myGameStarted = false;
        myBall.dx = myBall.dy = 0;
        myRacket.dx = 0;
    } else {
        toStartPosition();
    }
    update();
}

void GameDialog::startMoveBall() {
    qsrand(QTime::currentTime().msec());
    myGameStarted = true;
    myBall.dy = - (qrand() % MAX_BALL_Y_SPEED + 1);
    while (myBall.dx == 0) {
        myBall.dx = qrand() % MAX_BALL_X_SPEED + 1;
        myBall.dx *= qrand() % 2 * (-1); //random direction
    }
}

void GameDialog::processCommand(const ControlCommand& cmd) {
    if (myGameStarted == true) {
        if (cmd.cmd == "left") {
            myRacket.dx = -RACKET_SPEED;
        }
        if (cmd.cmd == "right") {
            myRacket.dx = RACKET_SPEED;
        }
    }
    if (cmd.cmd == "stop") {
        myRacket.dx = 0;
    }
    if (cmd.cmd == "start") {
        myGameStarted = true;
        toStartPosition();
        startMoveBall();
    }
}

void GameDialog::paintEvent(QPaintEvent*) {
    QPainter p(this);

    p.fillRect(rect(), QBrush(Qt::white));

    QRadialGradient gradient(myBall.coord,defRadius, myBall.coord-QPoint(5,5));
    gradient.setColorAt(0.2, Qt::white);
    gradient.setColorAt(1, Qt::blue);
    p.setBrush (gradient);
    p.setPen (Qt::NoPen);
    p.drawEllipse(myBall.coord, myBall.curRadius.width(), myBall.curRadius.height());

    p.setPen(Qt::black);
    p.drawText(360,30, QString("Lives left: %1").arg(myLives));

    QLinearGradient linearGradient(myRacket.x,myRacket.y, myRacket.x, myRacket.y + myRacket.height);
    linearGradient.setColorAt(0, Qt::green);
    linearGradient.setColorAt(1, Qt::black);
    p.setPen(Qt::black);
    p.setBrush(linearGradient);
    p.drawRect(myRacket.x, myRacket.y, myRacket.width, myRacket.height);
}


void GameDialog::receiveSlot() {
    while(mySocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(mySocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        mySocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
    
        myControlHostAddress = sender;
        myControlHostPort = senderPort;
        
        ControlCommand cmd;
        QXmlSimpleReader parser;
        CommandXmlHandler handler(&cmd);
        parser.setContentHandler(&handler);
        QXmlInputSource source;
        source.setData(QString::fromUtf8(datagram.data()));
        parser.parse(source);

        processCommand(cmd);
    }
}

void GameDialog::moveRacketSlot() {
    myRacket.x += myRacket.dx;
    if (myRacket.x + myRacket.width > width()) {
        myRacket.x = width() - myRacket.width;
    } else if ( myRacket.x < 0 ) {
        myRacket.x = 0;
    }
}

void GameDialog::sendStateSlot() {
    if (myControlHostAddress.isNull() == true) {
        return;
    }

    QDomDocument stateDomDocument = serialize();
    int result = mySocket->writeDatagram(stateDomDocument.toString().toUtf8(), myControlHostAddress, myControlHostPort);
    if (result == -1) {
        QMessageBox::critical(this, "Error with sending", mySocket->errorString());
    }
}

QDomDocument GameDialog::serialize() const {
    QDomDocument stateDomDocument;
    QDomElement game = stateDomDocument.createElement("game");
    game.setAttribute("started", myGameStarted == true ? 1 : 0);
    game.setAttribute("height", height());
    game.setAttribute("width", width());

    game.appendChild(myBall.serialize(stateDomDocument));
    game.appendChild(myRacket.serialize(stateDomDocument));

    stateDomDocument.appendChild(game);

    return stateDomDocument;
}

QDomElement GameDialog::Ball::serialize(QDomDocument &domDocument) const {
    QDomElement element = domDocument.createElement("ball");
    element.setAttribute("x", coord.x());
    element.setAttribute("y", coord.y());
    QDomElement radius = domDocument.createElement("radius");
    radius.setAttribute("x", curRadius.width());
    radius.setAttribute("y", curRadius.height());
    element.appendChild(radius);
    return element;
}

QDomElement GameDialog::Racket::serialize(QDomDocument &domDocument) const {
    QDomElement element = domDocument.createElement("racket");
    element.setAttribute("x", x);
    element.setAttribute("y", y);
    element.setAttribute("width", width);
    element.setAttribute("height",height);
    return element;
}

GameDialog::CommandXmlHandler::CommandXmlHandler(ControlCommand* cmd) {
    myCommand = cmd;
}

bool GameDialog::CommandXmlHandler::startElement(const QString &, const QString &, const QString &qName, const QXmlAttributes &atts) {
    if (qName == "command") {
        myCommand->cmd = atts.value("name");
    }
    return true;
}
