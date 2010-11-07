#include "clientmainwindow.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>
#include <QMessageBox>

#include "../command.hpp"

ClientMainWindow::ClientMainWindow(QWidget * parent):
        QMainWindow(parent) {
    server.connected = false;
    createObjects();
    connectObjects();
    loadSettings();
    settingsDialog->reloadSettings();
}

bool ClientMainWindow::startUdpListener(quint16 port, quint16 endPort) {
    if (connectionSocket->isValid()) return false;
    while(port <= endPort) {
        if (!connectionSocket->bind(port)) {
            ++port;
            continue;
        }
        statusBar()->showMessage("Started at port " + QString::number(port), 50);
        return true;
    }
    return false;
}

void ClientMainWindow::createObjects() {

    //actions
    settingsDialogAct = new QAction(tr("&Settings"), this);
    connectAct = new QAction(tr("&Connect"), this);
    disconnectAct = new QAction(tr("&Disconnect"), this);
    quitAct = new QAction(tr("&Quit"), this);

    //menus
    menuGame = menuBar()->addMenu(tr("&Game"));
    menuHelp = menuBar()->addMenu(tr("&Help"));

    menuGame->addAction(connectAct);
    menuGame->addAction(disconnectAct);
    menuGame->addSeparator();
    menuGame->addAction(settingsDialogAct);
    menuGame->addSeparator();
    menuGame->addAction(quitAct);

    clientSettings = new ClientSettings();
    settings = new QSettings("ru.amse.qt2010.rassokhin","arcanoid",this);
    settingsDialog = new SettingsDialog(clientSettings,this);
    connectionSocket = new QUdpSocket(this);
    controls = new ClientControlsWidget(this);
    setCentralWidget(controls);

    quitAct->setShortcuts(QKeySequence::Quit);
}

void ClientMainWindow::connectObjects() {
    connect(settingsDialogAct, SIGNAL(triggered()), SLOT(runSettingsDialog()));
    connect(connectAct, SIGNAL(triggered()), SLOT(connectToGame()));
    connect(disconnectAct, SIGNAL(triggered()), SLOT(disconnectFromGame()));
    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    connect(connectionSocket, SIGNAL(readyRead()), SLOT(readMessage()));

    connect(controls, SIGNAL(sendingDataToServer(QByteArray)), SLOT(sendMessage(QByteArray)));

    connect(this, SIGNAL(newIncomingMessage(QByteArray)), controls, SLOT(tryToResolveMessage(QByteArray)));
}

void ClientMainWindow::loadSettings() {
    settings->beginGroup("Client");
    resize( settings->value("mainwindow.size",     QSize (640, 480) ).toSize());
    move(   settings->value("mainwindow.position", QPoint(120, 160) ).toPoint());
    clientSettings->loadSettings(settings);
    settings->endGroup();

}

void ClientMainWindow::saveSettings() {
    settings->beginGroup("Client");
    settings->setValue("mainwindow.size",     size());
    settings->setValue("mainwindow.position", pos());
    clientSettings->saveSettings(settings);
    settings->endGroup();
}

void ClientMainWindow::runSettingsDialog() {
    settingsDialog->reloadSettings();
    settingsDialog->show();
}

void ClientMainWindow::connectToGame() {
    if(server.connected) return;
    if (!server.address.setAddress(clientSettings->getAddress())) {
        QMessageBox::warning(0, windowTitle(), "Cannot connect to server. May be address is invalid");
        return;
    }
    server.port = clientSettings->getPort();

    static Command cmd(Command::CONNECT);
    QByteArray msg;
    cmd.serialize();
    msg.append(cmd.serialize());
    sendMessage(msg, true);
}

void ClientMainWindow::sendMessage(QByteArray message, bool force) {
    if (!(server.connected || force)) return;
    qint64 sended = connectionSocket->writeDatagram(message, server.address, server.port);
    if (sended == -1) {
        statusBar()->showMessage("Cannot send message to server. Error occured");
        return;
    }
}

void ClientMainWindow::disconnectFromGame() {
    if (!server.connected) return;
    server.connected = false;
    static Command cmd(Command::DISCONNECT);
    QByteArray msg;
    msg.append(cmd.serialize());
    sendMessage(msg, true);
}

void ClientMainWindow::readMessage() {
    while (connectionSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(connectionSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        if( connectionSocket->readDatagram(datagram.data(), datagram.size(), &sender,
                                    &senderPort) == -1)
            continue;
        if ((sender != server.address) && (senderPort != server.port)) continue;
        if(!server.connected) {
            Command * cmd = Command::deserialize(datagram);
            if (cmd!=0 && (cmd->getType() & Command::ACCEPTCONNECTION)) {
                server.connected = true;
                statusBar()->showMessage("Connected to server", 10000);
            }
        }

        emit newIncomingMessage(datagram);
    }
}

void ClientMainWindow::closeEvent(QCloseEvent *) {
    disconnectFromGame();
    saveSettings();
}
