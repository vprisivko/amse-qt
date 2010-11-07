#include "servermainwindow.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>
#include <QMessageBox>

#include "../command.hpp"
#include "../publicstate.hpp"

ServerMainWindow::ServerMainWindow(QWidget * parent):
        QMainWindow(parent) {
    client.connected = false;
    createObjects();
    connectObjects();
    loadSettings();
    //settingsDialog->reloadSettings();

    setFocusPolicy(Qt::StrongFocus);

    gameView->resize(640, 480);
    gameView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    setFocus();
}

bool ServerMainWindow::startUdpListener(quint16 port, quint16 endPort) {
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

void ServerMainWindow::createObjects() {

    //actions
    //settingsDialogAct = new QAction(tr("&Settings"), this);
    quitAct = new QAction(tr("&Quit"), this);

    //menus
    menuGame = menuBar()->addMenu(tr("&Game"));
    //menuHelp = menuBar()->addMenu(tr("&Help"));

    //menuGame->addAction(settingsDialogAct);
    //menuGame->addSeparator();
    menuGame->addAction(quitAct);

    //serverSettings = new ServerSettings();
    settings = new QSettings("ru.amse.qt2010.rassokhin", "arcanoid", this);
    //settingsDialog = new ServerSettingsDialog(serverSettings, this);
    connectionSocket = new QUdpSocket(this);
    gameEngine = new ArcanoidEngine(QRect(0, 0, 640, 480) ,this);
    gameView = new ArcanoidViewWidget(gameEngine, this);
    gameView->setScene(gameEngine);

    setCentralWidget(gameView);

    quitAct->setShortcuts(QKeySequence::Quit);
}

void ServerMainWindow::connectObjects() {
    //connect(settingsDialogAct, SIGNAL( triggered() ), SLOT( runSettingsDialog() ));
    connect(quitAct, SIGNAL( triggered() ), qApp, SLOT( closeAllWindows() ));

    connect(connectionSocket, SIGNAL(readyRead()), SLOT(readMessage()));
    
    connect(gameEngine, SIGNAL(stateChanged(ArcanoidEngine::State)), SLOT(gameStateChanged(ArcanoidEngine::State)));
}

void ServerMainWindow::loadSettings() {
    settings->beginGroup("Server");
    resize( settings->value("mainwindow.size",     QSize (640, 480) ).toSize());
    move(   settings->value("mainwindow.position", QPoint(120, 160) ).toPoint());
    //serverSettings->loadSettings(settings);
    settings->endGroup();

}

void ServerMainWindow::saveSettings() {
    settings->beginGroup("Server");
    settings->setValue("mainwindow.size",     size());
    settings->setValue("mainwindow.position", pos());
    //serverSettings->saveSettings(settings);
    settings->endGroup();
}

//void ServerMainWindow::runSettingsDialog() {
//    settingsDialog->reloadSettings();
//    settingsDialog->show();
//}

void ServerMainWindow::sendMessage(QByteArray message, bool force) {
    if (!client.connected && !force) return;
    qint64 sended = connectionSocket->writeDatagram(message, client.address, client.port);
    if (sended == -1) {
        statusBar()->showMessage("Cannot send message to server. Error occured");
        // TODO: something else...
        return;
    }
}

void ServerMainWindow::disconnect() {
    if (!client.connected) return;
    client.connected = false;
    static Command cmd(Command::DISCONNECT);
    QByteArray msg;
    msg.append(cmd.serialize());
    sendMessage(msg, true);
}

void ServerMainWindow::readMessage() {
    while (connectionSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(connectionSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        if( connectionSocket->readDatagram(datagram.data(), datagram.size(), &sender,
                                    &senderPort) == -1)
            continue;

        parseMessage(datagram, sender, senderPort);
    }
}

void ServerMainWindow::closeEvent(QCloseEvent *) {
    disconnect();
    saveSettings();
}

void ServerMainWindow::parseMessage(const QByteArray &message, const QHostAddress &senderAddress, quint16 senderPort) {
    Command * cmd = Command::deserialize(message);
    if (cmd == 0) return;

    switch(cmd->getType()) {
    case Command::DISCONNECT: {
            disconnect();
            statusBar()->showMessage("Client disconnected", 10000);
            gameEngine->closeGame();
        } break;
    case Command::CONNECT: {
            statusBar()->showMessage("Client connected", 10000);
            client.address = senderAddress;
            client.port = senderPort;
            client.connected = true;
            sendMessage(Command(Command::ACCEPTCONNECTION).serialize(), true);
            gameStateChanged(ArcanoidEngine::BeforeFirstGame);
        } break;
    case Command::MOVE_LEFT: {
            gameEngine->moveBoardLeft();
        } break;
    case Command::MOVE_RIGHT: {
            gameEngine->moveBoardRight();
        } break;
    case Command::PLAYPAUSE: {
            switch (gameEngine->state()) {
            case ArcanoidEngine::Paused: {
                    gameEngine->setPaused(false);
                } break;
            case ArcanoidEngine::BetweenLevels: {
                    gameEngine->nextLevel();
                } break;
            case ArcanoidEngine::Running: {
                    gameEngine->setPaused(true);
                } break;
            case ArcanoidEngine::BeforeFirstGame:
            case ArcanoidEngine::GameOver: {
                    gameEngine->newGame();
                } break;
            }
            statusBar()->showMessage("play|pause command", 3000);
        } break;
    default: break;
    }
    delete cmd;
}

void ServerMainWindow::gameStateChanged(ArcanoidEngine::State state) {
    PublicState ps;
    ps.leftAllowed = false;
    ps.rightAllowed = false;
    ps.playPauseAllowed = true;
    switch (state) {
    case ArcanoidEngine::Paused:
        break;
    case ArcanoidEngine::Running: {
        ps.leftAllowed = true;
        ps.rightAllowed = true;
        } break;
    case ArcanoidEngine::BetweenLevels:
        break;
    case ArcanoidEngine::GameOver:
        break;
    default:
        break;
    }
    sendMessage(ps.serialize());
}

