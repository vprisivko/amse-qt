#include "Pult.h"
#include <QLabel>
#include <QErrorMessage>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>

Pult::Pult(qint16 port, QWidget *parent):QDialog(parent) {
    my_ip.setAddress("127.0.0.1");
    my_port = port;
    setView();
    connectButtons();
    setNetworkData();
}

void Pult::setNetworkData() {
    isSet = false;
    my_udpSocket = new QUdpSocket(this);
    my_udpSocket->bind(my_ip, my_port);
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
    layout1 = new QHBoxLayout();
    my_leftButton = new QPushButton("<", this);
    my_rightButton = new QPushButton(">", this);
    layout1->addWidget(my_leftButton);
    layout1->addWidget(my_rightButton);
    mainLayout->addItem(layout1);
    my_leftButton->setAutoRepeat(true);
    my_rightButton->setAutoRepeat(true);
    my_leftButton->setAutoRepeatDelay(0);
    my_rightButton->setAutoRepeatDelay(0);
    my_leftButton->setAutoRepeatInterval(BUTTON_INTERVAL);
    my_rightButton->setAutoRepeatInterval(BUTTON_INTERVAL);
}

void Pult::connectButtons() {
    connect(my_setButton, SIGNAL(clicked()),
            this, SLOT(setContact()));
    connect(my_leftButton, SIGNAL(clicked()),
            this, SLOT(sendLeft()));
    connect(my_rightButton, SIGNAL(clicked()),
            this, SLOT(sendRight()));
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
}

void Pult::sendRight() {
    if (!isSet) {
        QErrorMessage* ipError = new QErrorMessage(this);
        ipError->showMessage("Contact is not set");
        return;
    }
    my_udpSocket->writeDatagram("Right", my_ipTo, my_portTo);
}

void Pult::sendLeft() {
    if (!isSet) {
        QErrorMessage* ipError = new QErrorMessage(this);
        ipError->showMessage("Contact is not set");
        return;
    }
    my_udpSocket->writeDatagram("Left", my_ipTo, my_portTo);
}
