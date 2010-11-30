#include <QtGui>
#include "Counter.h"

Counter::Counter(QWidget *parent)
	:QDialog(parent) {
	count1 = 0;
	count2 = 0;
	timer1 = startTimer(1000);
	timer2 = startTimer(1000);

	
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
void Counter::timerEvent(QTimerEvent *event) {
	
	if (event->timerId() == timer1) {
		++count1;
	}
	if (event->timerId() == timer2) {
		++count2;
	}
	int i = comboBox->currentIndex();
	if (i == 0) {
		textLine->clear();
		QString s = QString::number(count1);
		textLine->insert(s);
	}
	if (i == 1) {
		textLine->clear();
		QString s = QString::number(count2);
		textLine->insert(s);
	}
}
void Counter :: setClicked() {
	QString text = lineEdit->text();
	int number = text.toInt();
	int i = comboBox->currentIndex();
	if (i == 0) {
		killTimer(timer1);
		timer1 = startTimer(number);
	}
	if (i == 1) {
		killTimer(timer2);
		timer2 = startTimer(number);
	}
}
void Counter :: stopClicked() {
	int i = comboBox->currentIndex();
	if (i == 0) {
		killTimer(timer1);
	}
	if (i == 1) {
		killTimer(timer2);
	}
}
void Counter :: updateComboBox(int index) {
	if (index == 0) {
		textLine->clear();
		QString s = QString::number(count1);
		textLine->insert(s);	
	} else if (index == 1) {
		textLine->clear();
		QString s = QString::number(count2);
		textLine->insert(s);
	}	
}
void Counter::enableFindButton(const QString &text) {
	setButton->setEnabled(!text.isEmpty());
}
















