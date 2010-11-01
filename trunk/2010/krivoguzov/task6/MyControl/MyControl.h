#ifndef MYCONTROL_H
#define MYCONTROL_H

#include <QDialog>
#include <QPushButton>
#include <QUdpSocket>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QXmlDefaultHandler>

class MyControl : public QDialog {
    Q_OBJECT;

public:
    MyControl(QString,int,int);

private slots:
    void newStateArrived();
    void sendControlData(QByteArray);
    void leftButtonPressed();
    void rightButtonPressed();
    void goButtonPressed();
    void pauseButtonPressed();

private:
    void createDialog();
    void configureNetwork();
    QByteArray createDomByteArray(int);

private:
    QString destIp;
    int destPort;
    int portToListen;

    QPushButton* leftButton;
    QPushButton* rightButton;
    QPushButton* goButton;
    QPushButton* pauseButton;
    QLabel* ballsLeftLabel;
    QLabel* statusLabel;
    QUdpSocket* myUdpSocket;

};

#endif // MYCONTROL_H
