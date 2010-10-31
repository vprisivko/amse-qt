#ifndef ARCONIDCONTROL_H
#define ARCONIDCONTROL_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QLabel>
#include <QUdpSocket>
#include <QDomDocument>
#include <QDebug>
#include <QHostAddress>
#include <QKeyEvent>


class ArconidControl : public QDialog
{
    Q_OBJECT;

private:
    QPushButton *myLeftBtn;
    QPushButton *myRightBtn;
    QPushButton *myStartBtn;
    QPushButton *myBindBtn;
    QLineEdit *myIpLE;
    QLineEdit *myPortLE;
    QLineEdit *myBindPortLE;
    QUdpSocket *mySocket;

public:
    ArconidControl(QWidget *parent = 0);
    ~ArconidControl();

protected slots:
    void left();
    void right();
    void start();
    void bindSocket();
    void reciveStatus();
    void keyPressEvent(QKeyEvent*);
};

#endif // ARCONIDCONTROL_H
