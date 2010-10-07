#ifndef BALLOLO_H
#define BALLOLO_H


#include <QDialog>
#include <QEvent>
#include <QPaintEvent>

class Ballolo: public QDialog{

	Q_OBJECT;

public:
	Ballolo( QWidget* parent = 0 );
	int drawTimerId;

protected:
	virtual void timerEvent( QTimerEvent* e );
	virtual void paintEvent( QPaintEvent* e );

	struct ball {
		double x, y, vx, vy, r;
	} b;

	void moveBall();

};


#endif // BALLOLO_H
