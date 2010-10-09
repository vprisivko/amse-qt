#ifndef BALLDIALOG_H
#define BALLDIALOG_H

#include <QtGui/QWidget>
#include <QPainter>
#include <QDialog>

class BallDialog : public QDialog
{
    Q_OBJECT

    QPoint m_center;
    int m_x_radius;
    int m_y_radius;
    int m_radius;

    int m_dx;
    int m_dy;

public:
    BallDialog(QWidget *parent = 0);

protected:
	virtual void timerEvent(QTimerEvent *);
	virtual void paintEvent(QPaintEvent *);
};

#endif // BALLDIALOG_H
