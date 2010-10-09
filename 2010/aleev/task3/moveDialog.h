#ifndef _MOVEDIALOG_H_
#define _MOVEDIALOG_H_

#include <QWidget>
#include <QDialog>
#include <QPoint>
#include <QSize>
#include <QTimerEvent>
#include <QPaintEvent>

class moveDialog : public QDialog{
    Q_OBJECT;

public:
    moveDialog(QWidget *parent = NULL);

public:
    virtual void timerEvent(QTimerEvent* e);
    virtual void paintEvent(QPaintEvent* e);

private:
    int defRadius;
    int dx,dy;

    struct Ball{
        QPoint center;
        QSize radius;
    } ball;
};


#endif
