#include "ArconidControl.h"

ArconidControl::ArconidControl(QWidget *parent)
    : QDialog(parent)
{
    myIpLE = new QLineEdit(this);
    myPortLE = new QLineEdit(this);
    myBindPortLE = new QLineEdit(this);
    myLeftBtn = new QPushButton("Left",this);
    myRightBtn = new QPushButton("Right",this);
    myStartBtn = new QPushButton("New Game",this);
    myBindBtn = new QPushButton("Bind!",this);
    mySocket = new QUdpSocket(this);
///*
    this->resize(450,100);
    this->setLayout(new QVBoxLayout());

    QHBoxLayout *bindLayout = new QHBoxLayout();
    bindLayout->setSpacing(5);
    bindLayout->addWidget(new QLabel("You can use arrows.",this));
    bindLayout->addStretch(1);
    bindLayout->addWidget(new QLabel("My port:",this));
    myBindPortLE->setFixedWidth(60);
    myBindPortLE->setValidator(new QIntValidator(0,65535,myBindPortLE));
    bindLayout->addWidget(myBindPortLE);
    bindLayout->addWidget(myBindBtn);
    this->layout()->addItem(bindLayout);
//*/
    QHBoxLayout *addressLayout = new QHBoxLayout();
    addressLayout->setSpacing(5);
    addressLayout->addWidget(new QLabel("IP:",this));
    addressLayout->addWidget(myIpLE);
    addressLayout->addWidget(new QLabel("Port:",this));
    myPortLE->setValidator(new QIntValidator(0,65535,myPortLE));
    myPortLE->setFixedWidth(60);
    addressLayout->addWidget(myPortLE);
    this->layout()->addItem(addressLayout);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(myLeftBtn);
    buttonsLayout->addWidget(myRightBtn);
    buttonsLayout->addWidget(myStartBtn);
    this->layout()->addItem(buttonsLayout);

    this->setWindowTitle("ArcanoidControl.");

    QObject::connect(myBindBtn,SIGNAL(clicked()),this,SLOT(bindSocket()));
    QObject::connect(myLeftBtn,SIGNAL(clicked()),this,SLOT(left()));
    QObject::connect(myRightBtn,SIGNAL(clicked()),this,SLOT(right()));
    QObject::connect(myStartBtn,SIGNAL(clicked()),this,SLOT(start()));
    QObject::connect(mySocket,SIGNAL(readyRead()),this,SLOT(reciveStatus()));
}

ArconidControl::~ArconidControl()
{

}

void ArconidControl::start(){
    mySocket->writeDatagram(QString("start").toUtf8(),QHostAddress(myIpLE->text()),myPortLE->text().toInt());
    this->setFocus();
}

void ArconidControl::left(){
    mySocket->writeDatagram(QString("left").toUtf8(),QHostAddress(myIpLE->text()),myPortLE->text().toInt());
    this->setFocus();
}

void ArconidControl::right(){
    mySocket->writeDatagram(QString("right").toUtf8(),QHostAddress(myIpLE->text()),myPortLE->text().toInt());
    this->setFocus();
}

void ArconidControl::bindSocket(){
    if(!myBindPortLE->text().isEmpty()){
        mySocket->bind(myBindPortLE->text().toInt());
        this->setWindowTitle("ArcanoidControl. My Port: " + myBindPortLE->text());
    }
}

void ArconidControl::reciveStatus(){
    while (mySocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(mySocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        mySocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);

        QDomDocument doc("Status");
        doc.setContent(datagram);
        QDomElement docElem = doc.documentElement();
        QDomNode n = docElem.firstChild();

        QPoint ballCoords;
        QSize windowSize;
        int platformX = 0;
        int platformWidth = 0;
        int lives = 0;
        int isPlaying = 0;


        while(!n.isNull()){
            QDomElement e = n.toElement();
            if(!e.isNull()){
                if(e.tagName() == "ballCoords"){
                    QDomNode subNode = e.firstChild();
                    QDomElement x = subNode.toElement();
                    if(!x.isNull()){
                        ballCoords.setX(x.text().toInt());
                    }
                    QDomElement y = subNode.nextSibling().toElement();
                    if(!y.isNull()){
                        ballCoords.setY(y.text().toInt());
                    }
                } else if(e.tagName() == "windowSize"){
                    QDomNode subNode = e.firstChild();
                    QDomElement width = subNode.toElement();
                    if(!width.isNull()){
                        windowSize.setWidth(width.text().toInt());
                    }
                    QDomElement height = subNode.nextSibling().toElement();
                    if(!height.isNull()){
                        windowSize.setHeight(height.text().toInt());
                    }
                } else if(e.tagName() == "platform"){
                    QDomNode subNode = e.firstChild();
                    QDomElement platX = subNode.toElement();
                    if(!platX.isNull()){
                        platformX = platX.text().toInt();
                    }
                    QDomElement platWidth = subNode.nextSibling().toElement();
                    if(!platWidth.isNull()){
                        platformWidth = platWidth.text().toInt();
                    }
                } else if(e.tagName() == "game"){
                    QDomNode subNode = e.firstChild();
                    QDomElement ls = subNode.toElement();
                    if(!ls.isNull()){
                        lives = ls.text().toInt();
                    }
                    QDomElement isPl = subNode.nextSibling().toElement();
                    if(!isPl.isNull()){
                        isPlaying = isPl.text().toInt();
                    }
                }
            }
            n = n.nextSibling();
        }

        if(isPlaying == 1){
            myStartBtn->setEnabled(false);
        } else {
            myStartBtn->setEnabled(true);
        }

        if(platformX <= 0 || isPlaying == 0){
            myLeftBtn->setEnabled(false);
        } else {
            myLeftBtn->setEnabled(true);
        }

        if(platformX+platformWidth >= windowSize.width() || isPlaying == 0){
            myRightBtn->setEnabled(false);
        } else {
            myRightBtn->setEnabled(true);
        }

        if(lives == 0){
            myStartBtn->setText("New Game");
        } else {
            myStartBtn->setText("Next Ball("+QString::number(lives)+")");
        }

    }
}

void ArconidControl::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Left:{
            left();
        }break;
        case Qt::Key_Right:{
            right();
        }break;
    }
}
