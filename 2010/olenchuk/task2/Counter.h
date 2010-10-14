#ifndef COUNTER_H
#define COUNTER_H

#include <QDialog>

class QComboBox;
class QTimer;
class QLabel;
class QLineEdit;
class QPushBatton;
class QVBoxLayout;


class Counter : public QDialog {
	Q_OBJECT

	public:
		Counter(QWidget *parent = 0);
	private slots:
		void setClicked();
		void stopClicked();
		void enableFindButton(const QString &text);
	protected:
		void timerEvent(QTimerEvent *event);
	private:
		int timer1;
		int timer2;
		int count1;
		int count2;
		QComboBox *comboBox;
		QLabel *label;
		QLineEdit *textLine;
		QLineEdit *lineEdit;
		QPushButton *setButton;
		QPushButton *stopButton;
		QPushButton *closeButton;
		QVBoxLayout *mainLayout;
};

#endif
