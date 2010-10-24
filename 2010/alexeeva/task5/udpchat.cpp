#include "udpchat.h"

UDPChat::UDPChat(quint16 port, QWidget *parent)
    : QDialog(parent), m_port(port)
{
	setMinimumSize(300, 300);
	setWindowTitle("UDPChat. You're on port " + QString::number(port));

	createItems();
	putItemsOnTheForm();
	connectAllTheStuff();
}

void UDPChat::createItems(){
    m_historyOfTheTalk = new QListWidget(this);
    m_portOfThePartner = new QLineEdit("8080", this);
    m_ipOfThePartner = new QLineEdit("127.0.0.1", this);
    m_messageToSend = new QTextEdit(this);
    m_send = new QPushButton("Send!", this);
    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(m_port);

    m_portOfThePartner->setValidator(new QIntValidator(0,65535,
    		m_portOfThePartner));
//    m_ipOfThePartner->setValidator(new QRegExValidator());
}
void UDPChat::putItemsOnTheForm(){
	QVBoxLayout * dialogLayout = new QVBoxLayout();
	QHBoxLayout * netInformatoinLayout = new QHBoxLayout();
	QHBoxLayout * messageLayout = new QHBoxLayout();

	netInformatoinLayout->addWidget(new QLabel("IP of the user: "));
	netInformatoinLayout->addWidget(m_ipOfThePartner);
	netInformatoinLayout->addWidget(new QLabel("Port of the user: "));
	netInformatoinLayout->addWidget(m_portOfThePartner);

	m_messageToSend->setMaximumHeight(MIN_HEIGHT);
	messageLayout->addWidget(m_messageToSend);
	messageLayout->addWidget(m_send);

	dialogLayout->addWidget(m_historyOfTheTalk);
	dialogLayout->addItem(netInformatoinLayout);
	dialogLayout->addItem(messageLayout);
	setLayout(dialogLayout);
}
void UDPChat::connectAllTheStuff(){
	connect(m_send, SIGNAL( clicked() ), SLOT (sendMessage()));
    connect(m_udpSocket,SIGNAL(readyRead()), SLOT(receiveMessage()));
}

void UDPChat::sendMessage(){
	if((!m_portOfThePartner->text().isEmpty()) &&
			(!m_ipOfThePartner->text().isEmpty())){
		QString message = m_messageToSend->toPlainText();
		QByteArray byteArrayMessage(message.toAscii());
		m_udpSocket->writeDatagram(message.toAscii(),
				QHostAddress(m_ipOfThePartner->text()),
				m_portOfThePartner->text().toInt());
		m_historyOfTheTalk->addItem(QString(MY_IP) + ":"
				+ QString::number(m_port) + ": "+ message);
//		m_historyOfTheTalk->currentItem()->setTextColor(Qt::red);
		m_messageToSend->clear();
	}
	else{
		QMessageBox::warning(this,"Whoops! Something went wrong.",
				"Are you sure that all the required info is provided and is right?");
	}
}

void UDPChat::receiveMessage(){
    QByteArray incomeMessage;
    incomeMessage.resize(m_udpSocket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
	m_udpSocket->readDatagram(incomeMessage.data(),
			incomeMessage.size(), &sender, &senderPort);
	m_historyOfTheTalk->addItem(sender.toString() + ":"
			+ QString::number(senderPort) + ": "+ QString(incomeMessage));
//	m_historyOfTheTalk->currentItem()->setTextColor(Qt::blue);
}
