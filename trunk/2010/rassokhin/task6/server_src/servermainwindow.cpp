#include "servermainwindow.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>
#include <QMessageBox>

#include "../command.hpp"

ServerMainWindow::ServerMainWindow(QWidget * parent):
        QMainWindow(parent) {
    client.connected = false;
    createObjects();
    connectObjects();
    loadSettings();
    settingsDialog->reloadSettings();

    // Game
//    m_newAction = KStandardGameAction::gameNew(this, SLOT(newGame()), actionCollection());
//    KStandardGameAction::end(this, SLOT(closeGame()), actionCollection());
//    m_pauseAction = KStandardGameAction::pause(this, SLOT(pauseGame()), actionCollection());
//    KStandardGameAction::highscores(this, SLOT(showHighscore()), actionCollection());
//    KStandardGameAction::quit(this, SLOT(close()), actionCollection());

    setFocusPolicy(Qt::StrongFocus);

    setFocus();
    resize(660,500);
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
    settingsDialogAct = new QAction(tr("&Settings"), this);
    quitAct = new QAction(tr("&Quit"), this);

    //menus
    menuGame = menuBar()->addMenu(tr("&Game"));
    //menuHelp = menuBar()->addMenu(tr("&Help"));

    menuGame->addAction(settingsDialogAct);
    menuGame->addSeparator();
    menuGame->addAction(quitAct);

    serverSettings = new ServerSettings();
    settings = new QSettings("ru.amse.qt2010.rassokhin", "arcanoid", this);
    settingsDialog = new ServerSettingsDialog(serverSettings, this);
    connectionSocket = new QUdpSocket(this);
    gameEngine = new ArcanoidEngine(QRect(0,0,640,480) ,this);
    gameView = new ArcanoidViewWidget(gameEngine, this);
    gameView->setScene(gameEngine);

    setCentralWidget(gameView);

    quitAct->setShortcuts(QKeySequence::Quit);
}

void ServerMainWindow::connectObjects() {
    connect(settingsDialogAct, SIGNAL( triggered() ), SLOT( runSettingsDialog() ));
    connect(quitAct, SIGNAL( triggered() ), qApp, SLOT( closeAllWindows() ));

    connect(connectionSocket, SIGNAL(readyRead()), SLOT(readMessage()));
    
//    connect(gameView, SIGNAL( levelChanged( unsigned int ) ), this, SLOT( displayLevel( unsigned int ) ));
//    connect(gameView, SIGNAL( scoreChanged( unsigned int ) ), this, SLOT( displayScore( unsigned int ) ));
//    connect(gameView, SIGNAL( livesChanged( unsigned int ) ), this, SLOT( displayLives( unsigned int ) ));
    connect(gameView, SIGNAL(stateChanged(ArcanoidViewWidget::State)), this, SLOT(gameStateChanged(ArcanoidViewWidget::State) ));
}

void ServerMainWindow::loadSettings() {
    settings->beginGroup("Server");
    resize( settings->value("mainwindow.size",     QSize (640, 480) ).toSize());
    move(   settings->value("mainwindow.position", QPoint(120, 160) ).toPoint());
    serverSettings->loadSettings(settings);
    settings->endGroup();

}

void ServerMainWindow::saveSettings() {
    settings->beginGroup("Server");
    settings->setValue("mainwindow.size",     size());
    settings->setValue("mainwindow.position", pos());
    serverSettings->saveSettings(settings);
    settings->endGroup();
}

void ServerMainWindow::runSettingsDialog() {
    settingsDialog->reloadSettings();
    settingsDialog->show();
}

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

        statusBar()->showMessage(datagram, 1000);
        Command * cmd = Command::deserialize(datagram);
        if (cmd!=0) {
            switch(cmd->getType()) {
            case Command::DISCONNECT: {
                    disconnect();
                    statusBar()->showMessage("Client disconnected", 10000);
                } break;
            case Command::CONNECT: {
                    gameView->newGame();
                    statusBar()->showMessage("Client connected", 10000);
                    client.address = sender;
                    client.port = senderPort;
                    sendMessage(Command(Command::ACCEPTCONNECTION).serialize(), true);
                } break;
            case Command::MOVE_LEFT: {
                } break;
            case Command::MOVE_RIGHT: {
                } break;
            case Command::PLAYPAUSE: {
                    static bool paused = false;
                    gameView->setPaused(!paused);
                    paused = !paused;
                    statusBar()->showMessage("play|pause command", 10000);
                } break;
            default: break;
            }
            delete cmd;
        }


        emit newIncomingMessage(datagram);
    }
}

void ServerMainWindow::closeEvent(QCloseEvent *) {
    disconnect();
    saveSettings();
}
/*
 * Copyright (C) 2007-2008 John-Paul Stanford <jp@stanwood.org.uk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * create the action events create the gui.
 */


void ServerMainWindow::newGame() {
    // Check for running game
    closeGame();
    if (gameView->state() == ArcanoidViewWidget::BeforeFirstGame
            || gameView->state() == ArcanoidViewWidget::GameOver) {
        gameView->newGame();
    }
}

void ServerMainWindow::pauseGame() {
    if (gameView->state() == ArcanoidViewWidget::Paused) {
        gameView->setPaused(false);
    }
    else {
        gameView->setPaused(true);
    }
}

void ServerMainWindow::closeGame() {
    if (gameView->state() == ArcanoidViewWidget::BeforeFirstGame
            || gameView->state() == ArcanoidViewWidget::GameOver) {
        return;
    }
    gameView->closeGame();
}

void ServerMainWindow::gameStateChanged(ArcanoidViewWidget::State state)
{
    switch (state)
    {
    case ArcanoidViewWidget::Paused:
        break;
    case ArcanoidViewWidget::Running:
        break;
    case ArcanoidViewWidget::GameOver:
        break;
    default:
        break;
    }
}

