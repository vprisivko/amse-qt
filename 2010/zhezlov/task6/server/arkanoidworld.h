#ifndef ARKANOIDWORLD_H
#define ARKANOIDWORLD_H


#include <QWidget>
#include <QMenuBar>
#include <QtXml>
#include <QDomDocument>
#include <QDomElement>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QTimerEvent>


class ArkanoidWorld : public QWidget
{
    Q_OBJECT
public:
    explicit ArkanoidWorld(QWidget *parent = 0);

    QDomDocument getState();

    void setWallMovement( int direction );


private:
    struct Ball{
        double x, y;
        double vx, vy;
        double radius;
    };

    struct Wall{
        double x;
        double width;
        double height;
        double speed;
    };

    Ball ball;
    Wall wall;
    int drawTimerId;
    int updateWorldTimerId;
    int sendStateTimerId;
    int wallMovementDirection;
    int livesRemaining;
    int wallRestrictedMoveDir;
    bool isActive;

protected:
    virtual void paintEvent(QPaintEvent * e);
    virtual void resizeEvent(QResizeEvent * e);
    virtual void timerEvent(QTimerEvent * e);
    void init();
    void updateWorld();

    void bottomHit();
signals:

public slots:
    void go();

};

#endif // ARKANOIDWORLD_H
