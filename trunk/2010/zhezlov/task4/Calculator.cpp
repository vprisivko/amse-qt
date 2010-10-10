#include <Calculator.h>
#include <QLabel>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QMenuBar>
#include <QFileDialog>
#include <QStatusBar>
#include <QSettings>
#include <QScrollArea>
#include <QSizePolicy>


Calculator::Calculator( QWidget* parent ): QMainWindow(parent){

	setMinimumSize( 400, 300 );

	inputForm = new QDialog(this);
	inputForm->setLayout( new QVBoxLayout() );

	le = new QLineEdit( "0", inputForm );
	inputForm->layout()->addWidget( le );

	QLayout* lay = new QHBoxLayout( );
	inputForm->layout()->addItem( lay );

	QPushButton* buttonAdd = new QPushButton("+", inputForm);
	QPushButton* buttonSubstract = new QPushButton("-", inputForm);
	QPushButton* buttonMultiply = new QPushButton("*", inputForm);
	QPushButton* buttonDivide = new QPushButton("/", inputForm);
	lay->addWidget( buttonAdd );
	lay->addWidget( buttonSubstract );
	lay->addWidget( buttonMultiply );
	lay->addWidget( buttonDivide );

	connect( buttonAdd, SIGNAL(pressed()), this, SLOT(updateText()) );
	connect( buttonSubstract, SIGNAL(pressed()), this, SLOT(updateText()) );
	connect( buttonMultiply, SIGNAL(pressed()), this, SLOT(updateText()) );
	connect( buttonDivide, SIGNAL(pressed()), this, SLOT(updateText()) );

	QMenu* mFile = menuBar()->addMenu("File");
	mFile->addAction( "Open", this, SLOT(open(bool)) );
	mFile->addAction( "Save", this, SLOT(save()) )->
			setObjectName("SaveAction");
	mFile->actions()[1]->setEnabled( false );
	mFile->addAction( "Save As...", this, SLOT(saveAs()) );
	menuBar()->addAction( "Revert", this, SLOT(revert()) )->
			setObjectName("RevertAction");
	menuBar()->addAction( "Toggle input Form", this, SLOT(toogleForm()) );
	menuBar()->addAction( "Reset", this, SLOT(reset()) );
	menuBar()->actions()[1]->setEnabled( false );

	QLabel* tmp = new QLabel("0");
	tmp->setObjectName("lastValueLabel");
	statusBar()->addPermanentWidget( tmp );
	tmp = new QLabel("None");
	tmp->setObjectName("fileNameLabel");
	statusBar()->addWidget( tmp );

	log = new QLabel();
	QScrollArea* cw = new QScrollArea(this);
	setCentralWidget( cw );
	cw->setWidget( log );

	fileName = "";
	lastValue = 0;

}


Calculator::~Calculator(){

}


void Calculator::open( bool rev ){

	if ( !rev ){
		fileName = QFileDialog(this, "Select log").getOpenFileName();
	}

	QFile openedFile( fileName );
	openedFile.open( QIODevice::ReadOnly );

	statusBar()->findChild<QLabel*>("fileNameLabel")->
			setText( openedFile.fileName() );

	QString s(openedFile.readLine(40));
	statusBar()->findChild<QLabel*>("lastValueLabel")->setText(s);
	lastValue = s.toDouble();

	log->setText( QString( openedFile.readAll() ) );
	log->adjustSize();

	menuBar()->findChild<QAction *>("SaveAction")->setEnabled(true);
	menuBar()->findChild<QAction *>("RevertAction")->setEnabled(true);

	openedFile.close();

}


void Calculator::save(){

	QFile openedFile( fileName );
	openedFile.open( QIODevice::WriteOnly );

	openedFile.write( QString().number( lastValue ).toUtf8() );
	openedFile.write( "\n" );
	openedFile.write( log->text().toUtf8() );

	openedFile.close();

	menuBar()->findChild<QAction *>("RevertAction")->setEnabled(true);

}


void Calculator::saveAs(){

	fileName = QFileDialog( this, "Select file" ).getSaveFileName();
	QFile openedFile( fileName );
	openedFile.open( QIODevice::WriteOnly );

	openedFile.write( QString().number( lastValue ).toUtf8() );
	openedFile.write( "\n" );
	openedFile.write( log->text().toUtf8() );

	openedFile.close();

	statusBar()->findChild<QLabel*>("fileNameLabel")->
			setText( openedFile.fileName() );
	menuBar()->findChild<QAction *>("RevertAction")->setEnabled(true);

}


void Calculator::revert(){
	emit open(true);
}


void Calculator::toogleForm(){
	inputForm->setVisible( inputForm->isHidden() );
}


void Calculator::updateText(){

	if (sender() == 0) return;
	QPushButton* button = dynamic_cast<QPushButton*>(sender());

	QString sign = " " + button->text() + " ";

	bool parseOk = false;
	double value = le->text().toDouble( &parseOk );

	if ( !parseOk ){
		QMessageBox::warning( le->parentWidget(), "Parse error",
				"This is not a number",	QMessageBox::Close, QMessageBox::Close );
		return;
	}

	QString newLine;


	switch ( sign[1].toAscii() ){
	case '+':
		newLine = QString().number( lastValue ) + sign + le->text() + " = ";
		lastValue += value;
		newLine += QString().number( lastValue );
		break;
	case '-':
		newLine = QString().number( lastValue ) + sign + le->text() + " = ";
		lastValue -= value;
		newLine += QString().number( lastValue );
		break;
	case '*':
		newLine = QString().number( lastValue ) + sign + le->text() + " = ";
		lastValue *= value;
		newLine += QString().number( lastValue );
		break;
	case '/':
		if ( value == 0 ){
			QMessageBox::warning( le->parentWidget(), "Universe error",
					"Dividing by zero kills.", QMessageBox::Close,
					QMessageBox::Close );
			return;
		}
		newLine = QString().number( lastValue ) + sign + le->text() + " = ";
		lastValue /= value;
		newLine += QString().number( lastValue );
		break;
	}

	log->setText( log->text()+ newLine + "\n" );
	statusBar()->findChild<QLabel*>("lastValueLabel")->
			setText( QString().number( lastValue ) );
	log->adjustSize();

}


void Calculator::reset(){

	log->setText( "" );
	log->adjustSize();
	lastValue = 0;
	statusBar()->findChild<QLabel*>("lastValueLabel")->
			setText( QString().number( lastValue ) );

}
