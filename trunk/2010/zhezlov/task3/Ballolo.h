#ifndef BALLOLO_H
#define BALLOLO_H


#include <QDialog>
#include <QEvent>
#include <QPaintEvent>
#include <QResizeEvent>

class Ballolo: public QDialog{

	Q_OBJECT;

public:
	Ballolo( QWidget* parent = 0 );
	int drawTimerId;

protected:
	virtual void timerEvent( QTimerEvent* e );
	virtual void paintEvent( QPaintEvent* e );
        virtual void resizeEvent( QResizeEvent* e );

        struct Ball {
		double x, y, vx, vy, r;
        } ball;

	void moveBall();

};


#endif // BALLOLO_H
