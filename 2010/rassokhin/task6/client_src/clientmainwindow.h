#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QUdpSocket>
#include <QSettings>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QHostAddress>

#include "clientsettings.h"
#include "settingsdialog.h"
#include "clientcontrolswidget.h"

class ClientMainWindow : public QMainWindow {
    Q_OBJECT;

public:
    ClientMainWindow(QWidget * parent = 0);

    bool startUdpListener(quint16 startPort, quint16 endPort = 0);

protected:
    virtual void closeEvent(QCloseEvent *);

signals:
    void newIncomingMessage(QByteArray message);

private slots:
    void runSettingsDialog();

    void sendMessage(QByteArray message, bool force = false);
    void readMessage();
    void connectToGame();
    void disconnectFromGame();


private:
    QUdpSocket * connectionSocket;

    struct {
        QHostAddress address;
        quint16 port;
        bool connected;
    } server;


    QAction * settingsDialogAct;
    QAction * connectAct;
    QAction * disconnectAct;
    QAction * quitAct;
    QMenu * menuGame;
    QMenu * menuHelp;
    ClientControlsWidget * controls;

    QSettings * settings;
    ClientSettingsPtr clientSettings;
    SettingsDialog * settingsDialog;


    void createObjects();
    void connectObjects();
    void loadSettings();
    void saveSettings();
};

#endif // CLIENTMAINWINDOW_H
