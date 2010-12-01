#include <QtGui>
#include "Counter.h"
#include "ThreadCounter.h"

Counter::Counter() {
	
	//count1 = 0;
	//count2 = 0;
	timer1 = new ThreadCounter(1000, 0);
	timer2 = new ThreadCounter(1000, 0);
	startTimer(10);
	timer1->start();
	timer2->start();

	
	comboBox = new QComboBox;
	comboBox->addItem(tr("Timer1"));
	comboBox->addItem(tr("Timer2"));
	textLine = new QLineEdit;
	textLine->setReadOnly(true);
	lineEdit = new QLineEdit;
	setButton = new QPushButton(tr("Set"));
	setButton->setDefault(true);
	setButton->setEnabled(false);

	stopButton = new QPushButton(tr("Stop"));

	closeButton = new QPushButton(tr("Close"));

	QHBoxLayout *topLayout = new QHBoxLayout;
	topLayout->addWidget(lineEdit);
	topLayout->addWidget(setButton);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(textLine);
	mainLayout->addWidget(comboBox);
	mainLayout->addItem(topLayout);
	mainLayout->addWidget(stopButton);
	mainLayout->addWidget(closeButton);
	mainLayout->addStretch();
	setLayout(mainLayout);

	connect(comboBox, SIGNAL(currentIndexChanged (int)),
		this, SLOT(updateComboBox(int)));
	
	connect(lineEdit, SIGNAL(textChanged(const QString &)),
		this, SLOT(enableFindButton(const QString &)));
	connect(setButton, SIGNAL(clicked()),
		this, SLOT(setClicked()));
	connect(stopButton, SIGNAL(clicked()),
		this, SLOT(stopClicked()));
	connect(closeButton, SIGNAL(clicked()),
		this, SLOT(close()));

	setWindowTitle(tr("Counter"));
	setFixedHeight(sizeHint().height());
}
void Counter::timerEvent(QTimerEvent *) {
	int i = comboBox->currentIndex();
	if (i == 0) {
		textLine->clear();
		QString s = QString::number(timer1->getTime());
		textLine->insert(s);
	}
	if (i == 1) {
		textLine->clear();
		QString s = QString::number(timer2->getTime());
		textLine->insert(s);
	}
}
void Counter :: setClicked() {
	QString text = lineEdit->text();
	int number = text.toInt();
	int i = comboBox->currentIndex();
	if (i == 0) {
		timer1->terminate();
		timer1->wait();
		timer1->setStep(number);
		timer1->start();
	}
	if (i == 1) {
		timer2->terminate();
		timer1->wait();
		timer2->setStep(number);
		timer2->start();
	}
}
void Counter :: stopClicked() {
	int i = comboBox->currentIndex();
	if (i == 0) {
		timer1->terminate();
		timer1->wait();
	}
	if (i == 1) {
		timer2->terminate();
		timer1->wait();
	}
}
void Counter :: updateComboBox(int index) {
	if (index == 0) {
		textLine->clear();
		QString s = QString::number(timer1->getTime());
		textLine->insert(s);
	} else if (index == 1) {
		textLine->clear();
		QString s = QString::number(timer2->getTime());
		textLine->insert(s);
	}	
}
void Counter::enableFindButton(const QString &text) {
	setButton->setEnabled(!text.isEmpty());
}
void Counter :: closeEvent(QCloseEvent *event) {
	timer1->terminate();
	timer2->terminate();
	timer1->wait();
	timer2->wait();
	event->accept();
}















