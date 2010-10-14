#ifndef MAGICBALL_H
#define MAGICBALL_H

#include <QDialog>

class QPainter;

class MagicBall : public QDialog {

	Q_OBJECT

	public: 
		MagicBall(QWidget *parent = 0);
	protected:
		void timerEvent(QTimerEvent *event);
		void paintEvent(QPaintEvent *);

	private:
		int x;
		int y;
		struct MyBall {
			int timer;
			int defRad;
			QPoint center;
			QPoint radius;
		};

	MyBall ball;
		

};

#endif 

