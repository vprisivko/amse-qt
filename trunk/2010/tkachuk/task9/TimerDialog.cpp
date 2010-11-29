#include <QVBoxLayout>
#include <QString>
#include <QIntValidator>
#include <QTimerEvent>
#include <QCloseEvent>
#include "TimerDialog.h"

TimerDialog::TimerDialog(QWidget *parent) : QDialog(parent), myTimer1(this), myTimer2(this) {
	valueTimer1 = valueTimer2 = 0;
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QHBoxLayout *lay = NULL;
	setLayout(mainLayout);

	label1 = new QLabel("<b>Timer 1:</b> 0");
    label2 = new QLabel("<b>Timer 2:</b> 0");
    
    mainLayout->addWidget(label1);
    mainLayout->addWidget(label2);

	myComboBox = new QComboBox();
	myComboBox->addItem("Timer 1");
	myComboBox->addItem("Timer 2");
	mainLayout->addWidget(myComboBox);

	intervalEdit = new QLineEdit();
	intervalEdit->setValidator(new QIntValidator());
	setButton = new QPushButton("SET");
	lay = new QHBoxLayout();
    lay->addWidget(intervalEdit);
	lay->addWidget(setButton);
	mainLayout->addLayout(lay);
	
	stopButton = new QPushButton("STOP");
	mainLayout->addWidget(stopButton);

    connect(setButton, SIGNAL(clicked()), this, SLOT(setPressed()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopPressed()));

	startTimer(10);
}

void TimerDialog::setPressed() {
	if (intervalEdit->text() != "") {
		switch (myComboBox->currentIndex()) {
			case 0:
				if (myTimer1.isRunning()) {
					myTimer1.stop();
					myTimer1.wait();
				}
				myTimer1.setParams(&valueTimer1, intervalEdit->text().toInt(), &myMutex1);
				myTimer1.start();
			break;
			case 1:
				if (myTimer2.isRunning()) {
					myTimer2.stop();
					myTimer2.wait();
				}
				myTimer2.setParams(&valueTimer2, intervalEdit->text().toInt(), &myMutex2);
				myTimer2.start();
			break;
		}
	}
}

void TimerDialog::stopPressed() {
	switch (myComboBox->currentIndex()) {
		case 0:
			if (myTimer1.isRunning()) {
				myTimer1.stop();
			}
		break;
		case 1:
			if (myTimer2.isRunning()) {
				myTimer2.stop();
			}
		break;
	}
}

void TimerDialog::timerEvent(QTimerEvent *) {
	myMutex1.lock();
	QString str = QString("<b>Timer 1:</b> %1").arg(valueTimer1);
	myMutex1.unlock();
	label1->setText(str);

	myMutex2.lock();
	str = QString("<b>Timer 2:</b> %1").arg(valueTimer2);
	myMutex2.unlock();
	label2->setText(str);
}

void TimerDialog::closeEvent(QCloseEvent *e) {
	myTimer1.stop();
	myTimer2.stop();
	myTimer1.wait();
	myTimer2.wait();
	e->accept();
}
