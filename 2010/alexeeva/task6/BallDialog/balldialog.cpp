#include "balldialog.h"

BallDialog::BallDialog(QHostAddress myAddress, qint16 myPort, QWidget *parent)
    : QDialog(parent)
{
	setWindowTitle("Arkanoid!");
	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_ballQuantity = 3;

	/* Network initialization */

	m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(myAddress, myPort);
    connect(m_udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));

    initializeAllTheStuff();
}

void BallDialog::initializeAllTheStuff(){
    if(m_ballQuantity-- == 0){
    	m_active = false;
    	sendState();
    	QMessageBox::warning(this, "Hi there!", "Game over!", "OK");
        m_udpSocket->writeDatagram("<gameOver/>", m_ipTo, m_portTo);
        close();
    }

    /* Initialisation of the ball */
    srand(time(NULL));
    m_ball.m_center = QPoint(width()/2, height()/2);
    m_ball.m_radius = m_ball.m_x_radius = m_ball.m_y_radius = BALL_RADIUS;
    m_ball.m_dx = m_ball.m_dy = 0;

	while((m_ball.m_dx == 0)&&(m_ball.m_dy == 0)){
		m_ball.m_dx = qrand() % 5;
		m_ball.m_dy = qrand() % 5;
	}

    /* Initialisation of the racket */
	m_racket.racket_rect = QRect((WINDOW_WIDTH - RACKET_WIDTH)/2, WINDOW_HEIGHT - RACKET_HEIGHT, RACKET_WIDTH, RACKET_HEIGHT);

}

void BallDialog::paintEvent(QPaintEvent* pe) {
	QPainter p(this);

    p.setBrush(QBrush(QColor(200, 200, 150)));
    p.drawRect(pe->rect());

    QRadialGradient gradient_ball(m_ball.m_center, m_ball.m_x_radius, m_ball.m_center);
    gradient_ball.setColorAt(1, Qt::transparent);
    gradient_ball.setColorAt(0.2, Qt::white);
	p.setBrush (gradient_ball);
	p.setPen(Qt::NoPen);
	p.drawEllipse(m_ball.m_center, m_ball.m_x_radius, m_ball.m_y_radius);

	QRadialGradient gradient_racket(m_racket.racket_rect.center(),
			m_racket.racket_rect.width(), m_racket.racket_rect.center());
	gradient_racket.setColorAt(1, Qt::transparent);
	gradient_racket.setColorAt(0.01, QColor(20, 10, 10));
	p.setBrush (gradient_racket);
	p.drawRect(m_racket.racket_rect);

	p.setPen(QPen(Qt::SolidLine));
	p.drawText(WINDOW_WIDTH - 50, 10, "Balls: " + QString::number(m_ballQuantity + 1));
}

void BallDialog::keyPressEvent(QKeyEvent * event){
	if(!m_active) return;

	if(event->key() == Qt::Key_Left){
		/* Check if there is any obstacle on the way of the racket*/
		if(m_racket.racket_rect.left() != 0){
			m_racket.racket_rect.moveLeft(m_racket.racket_rect.left() - 100/TIMER_INTERVAL);
		}
	}

	else if(event->key() == Qt::Key_Right){
		if(m_racket.racket_rect.right() != width() - 1){
			m_racket.racket_rect.moveRight(m_racket.racket_rect.right() + 100/TIMER_INTERVAL);
		}
	}
    update();
}

void BallDialog::Ball::move(Racket & m_racket, bool & m_active){
	int x = m_center.x() + m_dx;
	int y = m_center.y() + m_dy;

	if (x + m_radius >= WINDOW_WIDTH){
		m_x_radius = WINDOW_WIDTH - x;
	} else if (x - m_radius <= 0) {
		m_x_radius = x;
	}

	if (y + m_y_radius >= WINDOW_HEIGHT){
		m_active = false;
	} else if (y - m_radius <= 0) {
		m_y_radius = y;
	}

	if ((y + m_radius >= m_racket.racket_rect.top())&&
			(x < m_racket.racket_rect.right())&&
			(x > m_racket.racket_rect.left())){
		m_y_radius = m_racket.racket_rect.top() - y;
	}

	if (m_x_radius <= m_radius/2){
		m_dx = -m_dx;
	}

	if (m_y_radius <= m_radius/2){
		m_dy = -m_dy;
	}

	m_center = QPoint(x,y);
}

void BallDialog::timerEvent(QTimerEvent*){
	if(!m_active){
		m_active = true;
		initializeAllTheStuff();
	}
	m_ball.move(m_racket, m_active);
	update();
}

QDomDocument BallDialog::serialize() {
    QDomDocument doc;
    QDomElement state = doc.createElement("state");
    state.setAttribute("active", m_active);
    doc.appendChild(state);
    return doc;
}

void BallDialog::readPendingDatagrams() {
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress senderIp;
        quint16 senderPort;
        m_udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &senderIp, &senderPort);
        m_ipOfIncomeDatagram = senderIp;
        m_portOfIncomeDatagram = senderPort;
        processTheDatagram(datagram);
        if( !(m_active)&&
        	(m_ipOfIncomeDatagram == m_ipTo)&&
        	(m_portOfIncomeDatagram == m_portTo) ){
            m_udpSocket->writeDatagram("<set/>", m_ipTo, m_portTo);
        }
    }
}

void BallDialog::processTheDatagram(QByteArray datagram) {
    QXmlSimpleReader reader;
    BallDialog::BallDialogXmlHandler * xmlHandler = new BallDialog::BallDialogXmlHandler(this);
    reader.setContentHandler(xmlHandler);
    QXmlInputSource buf;
    buf.setData(datagram);
    reader.parse(&buf);
    delete xmlHandler;
}

void BallDialog::sendState(){
    QDomDocument state = serialize();
    m_udpSocket->writeDatagram(state.toString().toAscii(), m_ipTo, m_portTo);
}

bool BallDialog::BallDialogXmlHandler::startElement(const QString &, const QString &, const QString & qName, const QXmlAttributes & atts) {
	if (qName == "set") {
		m_ballDialog->m_ipTo =  m_ballDialog->m_ipOfIncomeDatagram;
		m_ballDialog->m_portTo =  m_ballDialog->m_portOfIncomeDatagram;
	}
    if (qName == "command") {
        if (atts.value("name") == "start") {
        	m_ballDialog->m_active = true;
        	m_ballDialog->m_timerId = m_ballDialog->startTimer(TIMER_INTERVAL);
            return true;
        }
        if (atts.value("name") == "right") {
        	m_ballDialog->getRacket().racket_rect.moveRight(m_ballDialog->getRacket().racket_rect.right() + 400/TIMER_INTERVAL);
            return true;
        }
        if (atts.value("name") == "left") {
        	m_ballDialog->getRacket().racket_rect.moveLeft(m_ballDialog->getRacket().racket_rect.left() - 400/TIMER_INTERVAL);
            return true;
        }
    }
    return true;
}
