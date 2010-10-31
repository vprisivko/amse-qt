#ifndef TASK6_H
#define TASK6_H

#include <QDialog>
#include <QTimerEvent>
#include <QPainter>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QIntValidator>
#include <QUdpSocket>
#include <QXmlDefaultHandler>

#include "BallWidget.h"

class Arconoid : public QDialog
{
    Q_OBJECT;
private:
    BallWidget *myBallWgt;
    QLineEdit *myBindPortLE;
    QPushButton *myBindBtn;
    QLineEdit *myControlAddressLE;
    QLineEdit *myControlPortLE;
    QLabel *myLivesLabel;

    int myLives;
    int myIsPlaying;
    int myTimer;
    QUdpSocket *mySocket;

public:
    Arconoid(QWidget * parent = 0);
    virtual ~Arconoid();

protected:
    void timerEvent(QTimerEvent *e);
    void sendStatus();
    void createDialog();
protected slots:
    void newGame();
    void gameOver();
    void bindPort();
    void reciveCommand();
};

#endif // TASK6_H
