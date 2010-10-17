#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <QMainWindow>
//#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QAction>
#include <QPushButton>


class Calculator: public QMainWindow {
	Q_OBJECT;

public:
	Calculator( QWidget* parent = 0 );
	~Calculator();


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

private:
        //Widgets and other stuff
        QWidget* inputForm;
        QPushButton* buttonAdd;
        QPushButton* buttonSubstract;
        QPushButton* buttonMultiply;
        QPushButton* buttonDivide;
        QLabel* lastValueLabel;
        QLabel* fileNameLabel;
        QMenu* menuFile;
        QAction* saveAction;
        QAction* revertAction;

        //Constructor subroutines
        void createWidgets();
        void placeItemsOnLayouts();
        void connectSigSlots();
        void addMenuActions();



};


#endif // CALCULATOR_H
