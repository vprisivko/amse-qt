#ifndef _BALL_DIALOG_H_
#define _BALL_DIALOG_H_

#include <QDialog>

class BallDialog : public QDialog {

	Q_OBJECT

public:
	BallDialog(QWidget *parent, int x, int y, int dx, int dy, int rx, int ry, int time);

	void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent *event);
	
private:
	int myXCoord, myYCoord;
	int myXRadius, myYRadius;
	int myDx, myDy;
	int myInitialXRadius, myInitialYRadius;

};

#endif // _BALL_DIALOG_H_
