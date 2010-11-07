#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QUdpSocket>
#include <QSettings>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QHostAddress>
#include <QByteArray>

#include "arcanoidengine.h"
#include "arcanoidviewwidget.h"

class ServerMainWindow : public QMainWindow {
    Q_OBJECT;

public:
    ServerMainWindow(QWidget * parent = 0);
    bool startUdpListener(quint16 startPort, quint16 endPort = 0);

protected:
    virtual void closeEvent(QCloseEvent *);

private slots:
    //void runSettingsDialog();

    void sendMessage(QByteArray message, bool force = false);
    void readMessage();
    void disconnect();

private:
    QUdpSocket * connectionSocket;

    struct ClientStruct {
        QHostAddress address;
        quint16 port;
        bool connected;
    } client;

    //QAction * settingsDialogAct;
    QAction * quitAct;
    QMenu * menuGame;
    //QMenu * menuHelp;

    ArcanoidViewWidget * gameView;
    ArcanoidEngine * gameEngine;

    QSettings * settings;
//    ServerSettingsPtr serverSettings;
//    ServerSettingsDialog * settingsDialog;


    void createObjects();
    void connectObjects();
    void loadSettings();
    void saveSettings();

    void parseMessage(const QByteArray & message, const QHostAddress & senderAddress, quint16 senderPort);

private slots:
    void gameStateChanged(ArcanoidEngine::State state );

};



#endif // SERVERMAINWINDOW_H
