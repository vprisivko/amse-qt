#ifndef COUNTER_H
#define COUNTER_H

#include <QDialog>

class QComboBox;
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
		void updateComboBox(int index);
	protected:
		void timerEvent(QTimerEvent *event);
	private:
		int timer1;
		int timer2;
		int count1;
		int count2;
		QComboBox *comboBox;
		QLineEdit *textLine;
		QLineEdit *lineEdit;
		QPushButton *setButton;
		QPushButton *stopButton;
		QPushButton *closeButton;
		QVBoxLayout *mainLayout;

	friend class TestCounter;
};

#endif
