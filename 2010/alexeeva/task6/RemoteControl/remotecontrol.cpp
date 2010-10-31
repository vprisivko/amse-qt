#include "remotecontrol.h"

RemoteControl::RemoteControl(QHostAddress myAddress, qint16 myPort, QWidget *parent)
    : QDialog(parent)
{
    m_ipInput = new QLineEdit("192.168.0.102");
    m_portInput = new QLineEdit("8085");
    m_setSocket = new QPushButton("Set");

    m_portInput->setValidator(new QIntValidator(0,65535, m_portInput));

    m_pushRight = new QPushButton(">");
    m_pushLeft = new QPushButton("<");
    m_start = new QPushButton("Start");

    m_pushRight->setEnabled(false);
    m_pushLeft->setEnabled(false);
    m_start->setEnabled(false);

    QHBoxLayout * netLayout = new QHBoxLayout();
    netLayout->addWidget(m_ipInput);
    netLayout->addWidget(m_portInput);
    netLayout->addWidget(m_setSocket);

    QHBoxLayout * gameLayout = new QHBoxLayout();
    gameLayout->addWidget(m_pushLeft);
    gameLayout->addWidget(m_pushRight);
    gameLayout->addWidget(m_start);

    QVBoxLayout * appLayout = new QVBoxLayout();
    appLayout->addItem(netLayout);
    appLayout->addItem(gameLayout);

    setLayout(appLayout);

    connect(m_pushRight, SIGNAL(pressed()), this, SLOT(moveRight()));
    connect(m_pushLeft, SIGNAL(pressed()), this, SLOT(moveLeft()));
    connect(m_start, SIGNAL(pressed()), this, SLOT(start()));
    connect(m_setSocket, SIGNAL(pressed()), this, SLOT(setSocket()));
    connect(m_start, SIGNAL(pressed()), this, SLOT(enableMove()));

    /* Network initialization */

	m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(myAddress, myPort);
    connect(m_udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void RemoteControl::enableStart(){
	m_start->setEnabled(true);
}

void RemoteControl::enableMove(){
	m_pushRight->setEnabled(true);
	m_pushLeft->setEnabled(true);
	m_start->setEnabled(false);
}

void RemoteControl::setSocket() {
	m_portTo = m_portInput->text().toInt();
	m_ipTo = QHostAddress(m_ipInput->text());

    m_udpSocket->writeDatagram("<set/>", m_ipTo, m_portTo);
}

void RemoteControl::moveRight() {
    m_udpSocket->writeDatagram("<command name = \"right\"/>", m_ipTo, m_portTo);
}

void RemoteControl::moveLeft() {
    m_udpSocket->writeDatagram("<command name = \"left\"/>", m_ipTo, m_portTo);
}

void RemoteControl::start() {
    m_udpSocket->writeDatagram("<command name = \"start\"/>", m_ipTo, m_portTo);
}

void RemoteControl::readPendingDatagrams() {
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        m_udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        processTheDatagram(datagram);

    }
}

void RemoteControl::processTheDatagram(QByteArray datagram) {
	RemoteControl::State * state = RemoteControl::State::createInstance(datagram, this);
       m_setSocket->setEnabled(false);
        if (state->active) {
            m_start->setEnabled(false);
        } else {
        	m_start->setEnabled(true);
            m_pushRight->setEnabled(false);
            m_pushLeft->setEnabled(false);
        }
    delete state;
}

RemoteControl::State * RemoteControl::State::createInstance(const QByteArray& stream, RemoteControl * rc) {
	RemoteControl::State * state = new RemoteControl::State();
    QXmlSimpleReader reader;
    RemoteControl::RCXmlHandler * xmlHandler = new RemoteControl::RCXmlHandler(state, rc);
    reader.setContentHandler(xmlHandler);
    QXmlInputSource buf;
    buf.setData(stream);
    reader.parse(&buf);
    delete xmlHandler;
    return state;
}

bool RemoteControl::RCXmlHandler::startElement(const QString &, const QString &, const QString & qName, const QXmlAttributes & atts) {
	if (qName == "set") {
		m_remoteControl->enableStart();
	}
	if (qName == "gameOver") {
		m_remoteControl->close();
	}
	if (qName == "state") {
        m_state->active = atts.value("active").toInt();
    }
    return true;
}

