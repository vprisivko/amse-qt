#include "Pult.h"
#include <QLabel>
#include <QErrorMessage>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>

Pult::Pult(QHostAddress& ip, qint16 port, QWidget *parent):QDialog(parent) {
    my_ip = ip;
    my_port = port;
    setView();
    connectButtons();
    setNetworkData();
}

void Pult::setNetworkData() {
    isSet = false;
    my_udpSocket = new QUdpSocket(this);
    my_udpSocket->bind(my_ip, my_port);
    connect(my_udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void Pult::setView() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* layout1 = new QHBoxLayout();
    QLabel * ipLabel = new QLabel("IP:", this);
    QLabel * portLabel = new QLabel("port:", this);
    my_ipEdit = new QLineEdit("127.0.0.1", this);
    my_portEdit = new QLineEdit(this);
    my_portEdit->setValidator(new QIntValidator(0, 65535, this));
    my_setButton = new QPushButton("Set", this);
    layout1->addWidget(ipLabel);
    layout1->addWidget(my_ipEdit);
    layout1->addWidget(portLabel);
    layout1->addWidget(my_portEdit);
    layout1->addWidget(my_setButton);
    mainLayout->addItem(layout1);
    my_startButton = new QPushButton("Start", this);
    mainLayout->addWidget(my_startButton);
    layout1 = new QHBoxLayout();
    my_leftButton = new QPushButton("<", this);
    my_rightButton = new QPushButton(">", this);
    my_leftButton->setEnabled(false);
    my_rightButton->setEnabled(false);
    my_startButton->setEnabled(false);
    layout1->addWidget(my_leftButton);
    layout1->addWidget(my_rightButton);
    mainLayout->addItem(layout1);
}

void Pult::connectButtons() {
    connect(my_setButton, SIGNAL(clicked()),
            this, SLOT(setContact()));
    connect(my_leftButton, SIGNAL(pressed()),
            this, SLOT(sendLeft()));
    connect(my_startButton, SIGNAL(clicked()),
            this, SLOT(sendStart()));
    connect(my_leftButton, SIGNAL(released()),
            this, SLOT(sendStop()));
    connect(my_rightButton, SIGNAL(pressed()),
            this, SLOT(sendRight()));
    connect(my_rightButton, SIGNAL(released()),
            this, SLOT(sendStop()));
}

void Pult::setContact() {
    QHostAddress temp_my_ipTo = my_ipTo;
    if (!my_ipTo.setAddress(my_ipEdit->text())) {
        my_ipTo = temp_my_ipTo;
        if (isSet) {
            my_ipEdit->setText(my_ipTo.toString());
            my_portEdit->setText(QString::number(my_portTo));
        }
        QErrorMessage* ipError = new QErrorMessage(this);
        ipError->showMessage("Invalid IP");
        return;
    }
    my_portTo = my_portEdit->text().toInt();
    isSet = true;
    my_udpSocket->writeDatagram("<set/>", my_ipTo, my_portTo);
}

void Pult::sendRight() {
    if (!isSet) {
        QErrorMessage* ipError = new QErrorMessage(this);
        ipError->showMessage("Contact is not set");
        return;
    }
    my_udpSocket->writeDatagram("<command name = \"right\"/>", my_ipTo, my_portTo);
}

void Pult::sendLeft() {
    if (!isSet) {
        QErrorMessage* ipError = new QErrorMessage(this);
        ipError->showMessage("Contact is not set");
        return;
    }
    my_udpSocket->writeDatagram("<command name = \"left\"/>", my_ipTo, my_portTo);
}

void Pult::sendStart() {
    if (!isSet) {
        QErrorMessage* ipError = new QErrorMessage(this);
        ipError->showMessage("Contact is not set");
        return;
    }
    my_udpSocket->writeDatagram("<command name = \"start\"/>", my_ipTo, my_portTo);
}

void Pult::sendStop() {
    if (!isSet) {
        QErrorMessage* ipError = new QErrorMessage(this);
        ipError->showMessage("Contact is not set");
        return;
    }
    my_udpSocket->writeDatagram("<command name = \"stop\"/>", my_ipTo, my_portTo);
}

void Pult::readPendingDatagrams() {
    while (my_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(my_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        my_udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        processTheDatagram(datagram);

    }
}

bool Pult::PultXmlHandler::startElement(const QString &, const QString &, const QString & qName, const QXmlAttributes & atts) {
    if (qName == "state") {
        my_ts->gameOver = atts.value("gameover").toInt();
        my_ts->started = atts.value("started").toInt();
        my_ts->height = atts.value("height").toInt();
        my_ts->width = atts.value("width").toInt();
    }
    if (qName == "racket") {
        my_ts->tableHW = atts.value("halfwidth").toInt();
        my_ts->tableX = atts.value("x").toInt();
    }
    if (qName == "ball") {
        my_ts->ballX = atts.value("x").toInt();
        my_ts->ballY = atts.value("y").toInt();
    }
    return true;
}

void Pult::processTheDatagram(QByteArray datagram) {
    Pult::TableState* TS = Pult::TableState::createInstance(datagram);
    if (TS->gameOver) {
        my_startButton->setEnabled(false);
        my_rightButton->setEnabled(false);
        my_leftButton->setEnabled(false);
        my_setButton->setEnabled(true);
    } else {
       my_setButton->setEnabled(false);
        if (TS->started) {
            my_startButton->setEnabled(false);
        } else {
            my_startButton->setEnabled(true);
        }
        if (TS->tableX > TS->tableHW) {
            my_leftButton->setEnabled(true);
        } else {
            my_leftButton->setEnabled(false);
        }
        if (TS->tableX < TS->width - TS->tableHW) {
            my_rightButton->setEnabled(true);
        } else {
            my_rightButton->setEnabled(false);
        }
    }
}

Pult::TableState* Pult::TableState::createInstance(const QByteArray& s) {
    Pult::TableState* TS = new Pult::TableState();
    QXmlSimpleReader reader;
    reader.setContentHandler(new Pult::PultXmlHandler(TS));
    QXmlInputSource buf;
    buf.setData(s);
    reader.parse(&buf);
    return TS;
}
