#ifndef BALLWIDGET_H
#define BALLWIDGET_H

#include <QWidget>
#include <QTimerEvent>
#include <QPainter>

class BallWidget : public QWidget
{
    Q_OBJECT;
private:
    QPoint myBallCoords;
    int myBallAbsRadius;
    int myBallStep;
    QSize myBallDxDy;
    QSize myBallRadius;
    int myTimerId;
    int myXSqueezeTimer;
    int myYSqueezeTimer;
    int myXSqueezeTimerStatus;
    int myYSqueezeTimerStatus;
    int myPlatformX;
    int myPlatformWidth;

public:
    BallWidget(const QSize &size, QWidget *parent = 0);
    ~BallWidget();
    void start();
    void stop();
    int getPlatformX() const { return myPlatformX; }
    int getPlatformWidth() const { return myPlatformWidth; }
    const QPoint& getBallCoords() const { return myBallCoords; }
    void left();
    void right();
protected:
    void timerEvent(QTimerEvent *e);
    void paintEvent(QPaintEvent *e);
    void squeezeX();
    void squeezeY();

signals:
    void gameOver();
};

#endif // BALLWIDGET_H
