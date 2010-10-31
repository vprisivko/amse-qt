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

#include "ArkanoidDialog.h"

static const int WINDOW_WIDTH = 400;
static const int WINDOW_HEIGHT = 320;
static const int SEND_STATE_TIME = 100;
static const int MOVE_BALL_TIME = 10;
static const int LIVES = 3;
static const int PAD_HEIGHT = 30;
static const int PAD_WIDTH = 100;
static const int PAD_SPEED = 5;
static const int MAX_BALL_X_SPEED = 2;
static const int MAX_BALL_Y_SPEED = 2;

ArkanoidDialog::ArkanoidDialog(quint16 port, QWidget *parent): QDialog(parent),  DEFAULT_RADIUS(20) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    initSocket(port);
    setTimers();
    createConnects();
    makeStartPosition();

    myLives = LIVES;
}

void ArkanoidDialog::setTimers() {
    mySendStateTimer = new QTimer(this);
    mySendStateTimer->start(SEND_STATE_TIME);
    myMovingBallTimer = new QTimer(this);
    myMovingBallTimer->start(MOVE_BALL_TIME);
}

void ArkanoidDialog::initSocket(quint16 port) {
    mySocket = new QUdpSocket(this);
    bool result = mySocket->bind(port);
    if (result == false) {
        QMessageBox::critical(this, "Error", "Can't use this port!\nPlease, choose another one");
        throw std::exception();
    }
}

void ArkanoidDialog::createConnects() {
    connect( mySocket,SIGNAL(readyRead()),this,SLOT(receiveSlot()));
    connect( mySendStateTimer, SIGNAL(timeout()), this, SLOT(sendStateSlot()));
    connect( myMovingBallTimer, SIGNAL(timeout()), this, SLOT(moveBallSlot()));
    connect( myMovingBallTimer, SIGNAL(timeout()), this, SLOT(movePadSlot()));
}

void ArkanoidDialog::lostBall() {
    myLives -= 1;
     if (myLives == 0) {
        QMessageBox::critical(this, "you lose!", "you lost all lives");
        myLives = LIVES;
        myGameStarted = false;
        myBall.dx = myBall.dy = 0;
        myPad.dx = 0;
    } else {
        makeStartPosition();
    }
    update();
}
void ArkanoidDialog::makeStartPosition() {
    myPad.height = PAD_HEIGHT;
    myPad.width = PAD_WIDTH;
    myPad.x = width() / 2 - myPad.width / 2;
    myPad.y = height() - myPad.height ;
    myPad.dx = 0;

    myBall.curRadius = QSize(DEFAULT_RADIUS,DEFAULT_RADIUS);
    myBall.coord = QPoint( myPad.x + myPad.width / 2 , myPad.y - myBall.curRadius.height() );

    myBall.dx = myBall.dy = 0;
    myGameStarted = false;
}

void ArkanoidDialog::moveBallSlot() {

    int x = myBall.coord.x(), y = myBall.coord.y();
    int rx = myBall.curRadius.width();
    int ry = myBall.curRadius.height();
    int windowHeight = height();
    int windowWidth = width();

    x += myBall.dx;
    y += myBall.dy;

    // if ball is out of window, take it to the window back!
    if (x > windowWidth - DEFAULT_RADIUS/2) {
        x = windowWidth - DEFAULT_RADIUS/2;
    }
    if (y > windowHeight - DEFAULT_RADIUS/2) {
        y = windowHeight - DEFAULT_RADIUS/2;
    }

    // x coordinate processing
    if (x < DEFAULT_RADIUS) {
        rx = x;
    } else {
        if (x + DEFAULT_RADIUS > windowWidth) {
                rx = windowWidth - x;
        } else {
                rx = DEFAULT_RADIUS;
        }
    }
    if (rx <= DEFAULT_RADIUS/2) {
        myBall.dx = -myBall.dx;
    }



    

    // y coordinate processing

   
   if (y < DEFAULT_RADIUS) {
            ry = y;
    } else {

        if (y + DEFAULT_RADIUS > windowHeight) {
            lostBall();
            return;
        } else {
            ry = DEFAULT_RADIUS;
        }
        
    }
  
    if ( myPad.x + rx <= x && x <= myPad.x + myPad.width -rx ) {
        if (y + DEFAULT_RADIUS > windowHeight - myPad.height) {
            ry = windowHeight - y - myPad.height;
        }
    }
    
    if (ry <= DEFAULT_RADIUS/2) {
        myBall.dy = -myBall.dy;
    }

    //exception if ball is near both of edges
    if (rx < DEFAULT_RADIUS && ry < DEFAULT_RADIUS) {
        rx = DEFAULT_RADIUS;
        ry = DEFAULT_RADIUS;
    }


    myBall.coord = QPoint(x,y);
    myBall.curRadius = QSize(rx,ry);

    update();

}

void ArkanoidDialog::paintEvent(QPaintEvent*) {

    QPainter p(this);
    
    p.fillRect( rect(), QBrush( Qt::yellow ) );
    
    QRadialGradient gradient(myBall.coord,DEFAULT_RADIUS, myBall.coord-QPoint(5,5) );
    gradient.setColorAt(0.2, Qt::white);
    gradient.setColorAt(0.8, Qt::red);
    gradient.setColorAt(1, Qt::black);
    p.setBrush ( gradient  );
    p.setPen ( Qt::NoPen );
    p.drawEllipse( myBall.coord, myBall.curRadius.width(), myBall.curRadius.height() );

    p.setPen(Qt::red);
    p.drawText(10,40, QString("Lives: %1").arg(myLives) );

    QLinearGradient linearGradient(myPad.x,myPad.y, myPad.x, myPad.y + myPad.height );
    linearGradient.setColorAt(0, Qt::gray);
    linearGradient.setColorAt(1, Qt::black);
    p.setPen(Qt::black);
    p.setBrush( linearGradient );
    p.drawRect(myPad.x, myPad.y, myPad.width, myPad.height);

}


void ArkanoidDialog::receiveSlot() {
    while(mySocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(mySocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        mySocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
    
        myControlHostAddress = sender;
        myControlHostPort = senderPort;
        
        ControlCommand command;
        QXmlSimpleReader parser;
        CommandXmlHandler handler(&command);
        parser.setContentHandler(&handler);
        QXmlInputSource source;
        source.setData( QString::fromUtf8( datagram.data() )  );
        parser.parse(source);

        processCommand(command);

       
    }

}

void ArkanoidDialog::processCommand(const ControlCommand& command) {
    if (myGameStarted == true) {
        if (command.command == "left") {
            myPad.dx = -PAD_SPEED;
        }
        if (command.command == "right") {
            myPad.dx = PAD_SPEED;
        }
        
    }
    if (command.command == "stop") {
        myPad.dx = 0;
    }
    if (command.command == "start") {
        myGameStarted = true;
        makeStartPosition();
        startMoveBall();
    }

}

void ArkanoidDialog::startMoveBall() {
    qsrand(QTime::currentTime().msec());
    myGameStarted = true;
    myBall.dy = - (qrand() % MAX_BALL_Y_SPEED + 1);
    while (myBall.dx == 0) {
        myBall.dx = qrand() % MAX_BALL_X_SPEED + 1;
        myBall.dx *= qrand() % 2 * (-1); // random direction
    }
}
void ArkanoidDialog::movePadSlot() {
    myPad.x += myPad.dx;
    if ( myPad.x + myPad.width > width() ) {
        myPad.x = width() - myPad.width;
    } else if ( myPad.x < 0 ) {
        myPad.x = 0;
    }
}

void ArkanoidDialog::sendStateSlot() {
    if (myControlHostAddress.isNull() == true) {
        return;
    }

   
    QDomDocument stateDomDocument = serialize();
    int result = mySocket->writeDatagram(stateDomDocument.toString().toUtf8(), myControlHostAddress, myControlHostPort);
    if (result == -1) {
        QMessageBox::critical(this, "Error with sending", mySocket->errorString());
    }
}

QDomDocument ArkanoidDialog::serialize() const {
    QDomDocument stateDomDocument;
    QDomElement game = stateDomDocument.createElement("game");  
    game.setAttribute("started", myGameStarted == true ? 1 : 0  );
    game.setAttribute("height", height());
    game.setAttribute("width", width());

    game.appendChild( myBall.serialize( stateDomDocument ));
    game.appendChild( myPad.serialize( stateDomDocument ));

    stateDomDocument.appendChild(game);

    return stateDomDocument;
}

QDomElement ArkanoidDialog::Ball::serialize( QDomDocument &domDocument ) const {
    QDomElement element = domDocument.createElement("ball");
    element.setAttribute("x", coord.x());
    element.setAttribute("y", coord.y());
    QDomElement radius = domDocument.createElement("radius");
    radius.setAttribute("x", curRadius.width());
    radius.setAttribute("y", curRadius.height());
    element.appendChild(radius);
    return element;
}

QDomElement ArkanoidDialog::Pad::serialize( QDomDocument &domDocument ) const {
    QDomElement element = domDocument.createElement("pad");
    element.setAttribute("x", x);
    element.setAttribute("y", y);
    element.setAttribute("width", width);
    element.setAttribute("height",height);
    return element;
}



ArkanoidDialog::CommandXmlHandler::CommandXmlHandler(ControlCommand* command) {
    myCommand = command;
}

bool ArkanoidDialog::CommandXmlHandler::startElement(const QString &, const QString &, const QString &qName, const QXmlAttributes &atts) {
    if (qName == "command") {
        myCommand->command = atts.value("name");
    }
    return true;
}