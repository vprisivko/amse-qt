#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>


class Calculator: public QMainWindow {
	Q_OBJECT;

public:
	Calculator( QWidget* parent = 0 );
	~Calculator();

	QWidget * inputForm;
	QLineEdit * le;
	QString fileName;
	QLabel * log;
	double lastValue;


public slots:
	void updateText();
	void open( bool rev );
	void save();
	void saveAs();
	void revert();
	void toogleForm();
	void reset();

};


#endif // CALCULATOR_H
