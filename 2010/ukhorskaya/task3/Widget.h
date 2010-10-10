#ifndef WIDGET_H
#define WIDGET_H

#include <QDialog>
#include <QTimerEvent>
#include <QPaintEvent>

class Widget: public QDialog{

        Q_OBJECT;

public:
        Widget( QWidget* parent = 0 );
private:
        int timer_id;

        struct ball {
        double x, y, dx, dy, r, rx, ry;
        } b;

public slots:
        void timerEvent(QTimerEvent* e);
        void paintEvent(QPaintEvent* e);

private:
        void moveElipse();

};


#endif // WIDGET_H
