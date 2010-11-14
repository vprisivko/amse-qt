#ifndef _MY_DIALOG_H_
#define _MY_DIALOG_H_

#include <QDialog>
#include <QLCDNumber>
#include <QLabel>
#include <QLineEdit>
#include <QEvent>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>


class MyDialog : public QDialog{
	Q_OBJECT;

	public:
		MyDialog( QWidget* parent = NULL );
		virtual void timerEvent( QTimerEvent* );

	private slots:
		void setClick();
		void stopClick();

        signals:
                void setSignal();

	private:
		int timer1Id, timer2Id;
		int count1, count2;
		bool isT1Exist, isT2Exist;

	private:	
		QLCDNumber* t1Value;
		QLCDNumber* t2Value;
		QComboBox* timerComboBox;
		QLineEdit* timerEditBox;
		QPushButton* setButton;
		QPushButton* stopButton;

        friend class MyTest;
};

#endif
