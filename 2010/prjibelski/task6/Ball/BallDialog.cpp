#include <QFile>

#include "BallDialog.h"


BallDialog::BallDialog() {
    this->setWindowTitle( "Ball bouncer" );
    this->setFixedSize( 500, 300 );

    state = new State( this->geometry().width() );

    loadSettings();
    createSocket( myPort );
    connectAll();
    commandHandler = new CommandXmlHandler( this );

    ballPainter = new QPainter();
    ballTimer = new QTimer( this );
    connect( ballTimer, SIGNAL( timeout() ), this, SLOT( timeEvent()) );
    ballTimer->start( 20 );
}

void BallDialog::connectAll() {
    connect( socket, SIGNAL( readyRead() ), this, SLOT( commandRecieved()) );
}

void BallDialog::createSocket( int portNumber ) {
    socket = new QUdpSocket( this );
    if (!socket->bind( portNumber )) {
        throw std::exception();
    }
}

void BallDialog::loadSettings() {
    QFile inFile( "ipsettings.txt" );

    if ( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) ) return;

    QTextStream inStream(&inFile);
    inStream >> myPort;
    inStream >> toPort;
    inStream.readLine(1);
    inStream >> ip;
}

void BallDialog::sendState() {
    QDomDocument stateDoc;
    stateDoc.appendChild( State::serialize( state, &stateDoc ) );
    QHostAddress sendHost( ip );

    socket->writeDatagram( stateDoc.toString().toAscii(),
                               sendHost,
                               toPort );
}

void BallDialog::commandRecieved() {
    quint16 port;
    QHostAddress address;
    recievedData.resize( socket->pendingDatagramSize() );

    socket->readDatagram( recievedData.data(), recievedData.size(),
                              &address,
                              &port );

    QXmlSimpleReader simpleReader;
    simpleReader.setContentHandler( commandHandler );
    QXmlInputSource buffer;
    buffer.setData( recievedData );
    simpleReader.parse( &buffer );
}

void BallDialog::paintEvent( QPaintEvent * ) {
    static int liveR = 6;
    static int liveSpace = 16;

    ballPainter->begin( this );
    QBrush * ballBrush = new QBrush( Qt::yellow, Qt::SolidPattern );
    ballPainter->setBrush( *ballBrush );
    ballPainter->setPen( Qt::red );

    ballPainter->drawEllipse( (int) (state->ball->x - state->ball->rx),
                              (int) (state->ball->y - state->ball->ry),
                              (int) (2 * state->ball->rx),
                              (int) (2 * state->ball->ry) );

    QBrush * plateBrush = new QBrush( Qt::green, Qt::SolidPattern );
    ballPainter->setBrush( *plateBrush );
    ballPainter->setPen( Qt::green );
    ballPainter->drawRect( state->plate->x,
                           this->geometry().height() - state->plate->height,
                           state->plate->width,
                           state->plate->height );

    ballPainter->setPen( Qt::red );
    QBrush * fullBrush = new  QBrush( Qt::red, Qt::SolidPattern );
    ballPainter->setBrush( *fullBrush );
    for ( int i = 0; i < state->livesLeft; ++i ) {
         ballPainter->drawEllipse( (i + 1) * liveSpace - liveR, liveSpace - liveR,
                                   2 * liveR, 2 * liveR );
    }
    QBrush * emptyBrush = new QBrush( Qt::gray, Qt::SolidPattern );
    ballPainter->setBrush( *emptyBrush );
    for ( int i = state->livesLeft; i < state->startLives; ++i ) {
         ballPainter->drawEllipse( (i + 1) * liveSpace - liveR, liveSpace - liveR,
                                   2 * liveR, 2 * liveR );
    }

    ballPainter->end();
}

void BallDialog::timeEvent() {
    state->ball->vx += state->ball->ax;
    state->ball->vy += state->ball->ay;


    if ( !state->fail && ( state->ball->vy > 0) &&
         ( state->ball->y + state->ball->ry + state->ball->vy + state->plate->height >=
           this->geometry().height() ) &&
           ( ( state->ball->x + state->ball->rx / 2  < state->plate->x ) ||
           ( state->ball->x - state->ball->rx / 2 > state->plate->x + state->plate->width ) ) ) {

        --state->livesLeft;
        state->fail = true;
    }

    if ( state->fail ) {
        if ( state->ball->y > this->geometry().height() + 2 * state->ball->radius ) {
            if ( state->livesLeft == 0 ) {
                ballTimer->stop();
            } else {
                state->restart();
            }
        }
        else {
            state->ball->vx += state->ball->ax;
            state->ball->vy += state->ball->ay;
            state->ball->x += state->ball->vx;
            state->ball->y += state->ball->vy;
        }
        repaint();
        sendState();
        return;
    }

    //Horizonatal case
    if ( state->ball->compDirectionX == 0 ) {
         moveBall(state->ball->x, state->ball->rx,
                  state->ball->vx > 0 ? (double) this->geometry().width() : 0.0,
                  state->ball->vx, state->ball->compDirectionX );
    }
    else {
         if ( ( state->ball->compDirectionX == 1 ) &&
              ( (state->ball->vx - state->ball->ax) * state->ball->vx < 0 ) ) {
               state->ball->compDirectionX = -1;
         }
         int compDirectionXT = state->ball->compDirectionX;

         compressBall( state->ball->x, state->ball->rx,
                       state->ball->compDirectionX > 0 ? state->ball->radius/2.0 : state->ball->radius,
                       state->ball->vx, state->ball->compDirectionX);
         state->ball->vx = (state->ball->compDirectionX == -compDirectionXT) ?
                           -state->ball->vx : state->ball->vx;
    }

    //Vertical case
    if ( state->ball->compDirectionY == 0 ) {
         moveBall( state->ball->y, state->ball->ry,
                   state->ball->vy > 0 ? this->geometry().height() - state->plate->height : 0,
                   state->ball->vy, state->ball->compDirectionY );
    }
    else {
         if ( ( state->ball->compDirectionY == 1 ) &&
              ( (state->ball->vy - state->ball->ay) * state->ball->vy < 0 ) ) {
              state->ball->compDirectionY = -1;
         }
         int compDirectionYT = state->ball->compDirectionY;

         compressBall( state->ball->y, state->ball->ry,
                       state->ball->compDirectionY > 0 ? state->ball->radius/2.0 : state->ball->radius,
                       state->ball->vy, state->ball->compDirectionY);
         state->ball->vy = (state->ball->compDirectionY == -compDirectionYT) ?
                           -state->ball->vy : state->ball->vy;
    }
    repaint();
    sendState();
}


void BallDialog::moveBall( double & coord, double & rad, double limit, double & speed, int & compDirection ) {
    int direction = speed > 0 ? 1 : -1;
    double newCoord = coord + direction * rad + speed;

    if ( direction * newCoord > direction * limit ) {
         coord = limit - direction *  state->ball->radius;
         compDirection = 1;
         compressBall( coord, rad, state->ball->radius/2.0, speed - (newCoord - limit), compDirection );
         speed = compDirection > 0 ? speed : -speed;
    }
    else {
        coord += speed;
    }
}


void BallDialog::compressBall( double & coord, double & rad, double radLimit, double speed, int & compDirection ) {
    int direction = speed > 0 ? 1 : -1;
    double newRad = rad - compDirection * direction * speed/2.0;

    if ( compDirection * newRad < compDirection * radLimit ) {
         rad = radLimit;
         if ( compDirection == 1 ) {
              coord += speed/2.0 - 2.0 * direction * (radLimit - newRad);
              rad += (radLimit - newRad);
              compDirection = -1;
         } 
         else {
              compDirection = 0;
              coord += speed/2.0;
         }
    }
    else {
        rad = newRad;
        coord += speed/2.0;
    }
}


bool CommandXmlHandler::startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &attrs) {
    if ( name == "restart" ) {
        ballDial->newGame();
    }
    if ( name == "command" ) {
        if ( attrs.value("value") == "right" ) {
            ballDial->state->plate->x += ballDial->state->plate->getDx();
        }
        if ( attrs.value("value") == "left" ) {
            ballDial->state->plate->x -= ballDial->state->plate->getDx();
        }
    }
    return true;
}
