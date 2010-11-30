#ifndef H_TESTCOUNTER
#define H_TESTCOUNTER


#include "../src/Counter.h"

#include <QObject>

class TestCounter : public QObject {
	Q_OBJECT;

	public:
		TestCounter();

	private slots:
		void testComboBox();
		void testSetClicked();
		void testStopClicked();

	private:
		Counter *counter;

};

#endif

