#include "balldialog.h"

BallDialog::BallDialog(QWidget *parent)
    : QDialog(parent)
{
    qsrand(time(0));

    m_center = QPoint(width()/2, height()/2);
    m_radius = m_x_radius = m_y_radius = 16;
    m_dx = m_dy = 0;

	while((m_dx == 0)&&(m_dy == 0)){
		m_dx = qrand() % 3;
		m_dy = qrand() % 3;
	}
	startTimer(10);
}

void BallDialog::paintEvent(QPaintEvent*) {
	QPainter p(this);
	p.setBrush(QBrush(Qt::white));
	p.setPen(Qt::NoPen);
	p.drawEllipse(m_center, m_x_radius, m_y_radius);
}

void BallDialog::timerEvent(QTimerEvent*){
	int x = m_center.x() + m_dx;
	int y = m_center.y() + m_dy;

	if (x + m_radius > width()){
		m_x_radius = width() - x;
	} else if (x - m_radius < 0) {
		m_x_radius = x;
	}

	if (y + m_radius > height()){
		m_y_radius = height() - y;
	} else if (y - m_radius < 0) {
		m_y_radius = y;
	}

	if (m_x_radius < m_radius/2){
		m_dx = -m_dx;
	}

	if (m_y_radius < m_radius/2){
		m_dy = -m_dy;
	}

	m_center = QPoint(x,y);
    update();
}
