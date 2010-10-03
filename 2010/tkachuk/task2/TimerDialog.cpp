#include <QVBoxLayout>
#include <QString>
#include <QIntValidator>
#include <QTimerEvent>
#include "TimerDialog.h"

TimerDialog::TimerDialog(QWidget *parent) : QDialog(parent) {
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
}

void TimerDialog::setPressed() {
	if (intervalEdit->text() != "") {
		switch (myComboBox->currentIndex()) {
			case 0:
				if (myTimer1) {
					killTimer(myTimer1);					
				} 
				myTimer1 = startTimer(intervalEdit->text().toInt());
			break;
			case 1:
				if (myTimer2) {
					killTimer(myTimer2);
				} 
				myTimer2 = startTimer(intervalEdit->text().toInt());
			break;
		}
	}
}

void TimerDialog::stopPressed() {
	switch (myComboBox->currentIndex()) {
		case 0:
			if (myTimer1) {
				killTimer(myTimer1);					
				myTimer1 = 0;
			}
		break;
		case 1:
			if (myTimer2) {
				killTimer(myTimer2);
				myTimer2 = 0;
			}
		break;
	}
}

void TimerDialog::timerEvent(QTimerEvent *event) {
    if (event->timerId() == myTimer1) {
		QString str = QString("<b>Timer 1:</b> %1").arg(++valueTimer1);
    	label1->setText(str);
	} else {
		if (event->timerId() == myTimer2) {
        	QString str = QString("<b>Timer 2:</b> %1").arg(++valueTimer2);
    		label2->setText(str);
		}
	}
}
