#include "Chat.h"
#include <QLabel>
#include <QErrorMessage>
#include <QIntValidator>
#include <QMessageBox>

Chat::Chat(qint16 port, QWidget *parent):QDialog(parent) {
    my_ip.setAddress("127.0.0.1");
    my_port = port;
    setWindowTitle(QString::number(port));
    setView();
    connectButtons();
    setNetworkData();
}

void Chat::setNetworkData() {
    isSet = false;
    my_udpSocket = new QUdpSocket(this);
    my_udpSocket->bind(my_ip, my_port);
    connect(my_udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void Chat::setView() {
    my_model = new QStringListModel(this);
    my_list = new QListView(this);
    my_list->setModel(my_model);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(my_list);
    QHBoxLayout* layout1 = new QHBoxLayout();
    my_ipEdit = new QLineEdit(this);
    my_portEdit = new QLineEdit(this);
    my_portEdit->setValidator(new QIntValidator(0, 65535, this));
    QLabel * ipLabel = new QLabel("IP:", this);
    QLabel * portLabel = new QLabel("port:", this);
    my_setButton = new QPushButton("Set", this);
    layout1->addWidget(ipLabel);
    layout1->addWidget(my_ipEdit);
    layout1->addWidget(portLabel);
    layout1->addWidget(my_portEdit);
    layout1->addWidget(my_setButton);
    mainLayout->addItem(layout1);
    layout1 = new QHBoxLayout();
    my_inputEdit = new QLineEdit(this);
    my_sendButton = new QPushButton("Send", this);
    layout1->addWidget(my_inputEdit);
    layout1->addWidget(my_sendButton);
    mainLayout->addItem(layout1);
}

void Chat::connectButtons() {
    connect(my_setButton, SIGNAL(clicked()),
            this, SLOT(setContact()));
    connect(my_sendButton, SIGNAL(clicked()),
            this, SLOT(sendData()));
}

void Chat::readPendingDatagrams() {
    while (my_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(my_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        my_udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        if (sender == my_ipTo && senderPort == my_portTo) {
            processTheDatagram(datagram);
        } else {
            QMessageBox* intruder = new QMessageBox(this);
            intruder->setText("\"" + sender.toString() + ':' + QString::number(senderPort) + "\" is trying to communicate with you.\n Set him as your contact?");
            intruder->addButton("Yes", QMessageBox::AcceptRole);
            intruder->addButton("No", QMessageBox::RejectRole);
            if (intruder->exec() == 0) {
                my_ipTo = sender;
                my_portTo = senderPort;
                my_ipEdit->setText(my_ipTo.toString());
                my_portEdit->setText(QString::number(my_portTo));
                isSet = true;
                processTheDatagram(datagram);
            }
        }
    }
}

void Chat::setContact() {
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

void Chat::sendData() {
    if (!isSet) {
        QErrorMessage* ipError = new QErrorMessage(this);
        ipError->showMessage("Contact is not set");
        return;
    }
    my_udpSocket->writeDatagram(my_inputEdit->text().toAscii(), my_ipTo, my_portTo);
    my_model->insertRows(my_model->rowCount(), 1);
    my_model->setData(my_model->index(my_model->rowCount() - 1, 0, QModelIndex()), "me: " + QString(my_inputEdit->text()));
    my_list->scrollToBottom();
}

void Chat::processTheDatagram(QByteArray datagram) {
    my_model->insertRows(my_model->rowCount(), 1);
    my_model->setData(my_model->index(my_model->rowCount() - 1, 0, QModelIndex()), my_ipTo.toString() + ':' + QString::number(my_portTo) + "/: " + QString(datagram));
    my_list->scrollToBottom();
}
