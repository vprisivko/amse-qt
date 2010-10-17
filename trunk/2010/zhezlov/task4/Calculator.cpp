#include <Calculator.h>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMenuBar>
#include <QFileDialog>
#include <QStatusBar>
#include <QSettings>
#include <QScrollArea>
#include <QSizePolicy>


Calculator::Calculator( QWidget* parent ): QMainWindow(parent){

	setMinimumSize( 400, 300 );

        createWidgets();
        placeItemsOnLayouts();
        connectSigSlots();
        addMenuActions();

	fileName = "";
	lastValue = 0;

}


void Calculator::createWidgets(){

    inputForm = new QDialog(this);

    buttonAdd = new QPushButton("+", inputForm);
    buttonSubstract = new QPushButton("-", inputForm);
    buttonMultiply = new QPushButton("*", inputForm);
    buttonDivide = new QPushButton("/", inputForm);

    log = new QLabel();
    lastValueLabel = new QLabel("Last result: 0");
    fileNameLabel = new QLabel("None");

    le = new QLineEdit( "0", inputForm );

    menuBar();
    statusBar();

}


void Calculator::connectSigSlots(){

    connect( buttonAdd, SIGNAL(pressed()), this, SLOT(updateText()) );
    connect( buttonSubstract, SIGNAL(pressed()), this, SLOT(updateText()) );
    connect( buttonMultiply, SIGNAL(pressed()), this, SLOT(updateText()) );
    connect( buttonDivide, SIGNAL(pressed()), this, SLOT(updateText()) );

}


void Calculator::addMenuActions(){

    menuFile = menuBar()->addMenu("File");
    menuFile->addAction( "Open", this, SLOT(open(bool)) );
    saveAction = menuFile->addAction( "Save", this, SLOT(save()) );
    menuFile->addAction( "Save As...", this, SLOT(saveAs()) );
    revertAction = menuBar()->addAction( "Revert", this, SLOT(revert()) );
    menuBar()->addAction( "Toggle input Form", this, SLOT(toogleForm()) );
    menuBar()->addAction( "Reset", this, SLOT(reset()) );

    saveAction->setEnabled( false );
    revertAction->setEnabled( false );

}


void Calculator::placeItemsOnLayouts(){

    inputForm->setLayout( new QVBoxLayout() );
    QLayout* lay = new QHBoxLayout( );

    inputForm->layout()->addWidget( le );
    inputForm->layout()->addItem( lay );

    lay->addWidget( buttonAdd );
    lay->addWidget( buttonSubstract );
    lay->addWidget( buttonMultiply );
    lay->addWidget( buttonDivide );

    statusBar()->addPermanentWidget( lastValueLabel );
    statusBar()->addWidget( fileNameLabel );

    QScrollArea* cw = new QScrollArea(this);
    setCentralWidget( cw );
    cw->setWidget( log );

}


Calculator::~Calculator(){

}


void Calculator::open( bool rev ){

	if ( !rev ){
		fileName = QFileDialog(this, "Select log").getOpenFileName();
	}

	QFile openedFile( fileName );
	openedFile.open( QIODevice::ReadOnly );

        fileNameLabel->setText( openedFile.fileName() );

	QString s(openedFile.readLine(40));
        lastValueLabel->setText("Last result: " + s);
	lastValue = s.toDouble();

	log->setText( QString( openedFile.readAll() ) );
	log->adjustSize();

        saveAction->setEnabled(true);
        revertAction->setEnabled(true);

	openedFile.close();

}


void Calculator::save(){

	QFile openedFile( fileName );
	openedFile.open( QIODevice::WriteOnly );

	openedFile.write( QString().number( lastValue ).toUtf8() );
	openedFile.write( "\n" );
	openedFile.write( log->text().toUtf8() );

	openedFile.close();

        revertAction->setEnabled(true);

}


void Calculator::saveAs(){

	fileName = QFileDialog( this, "Select file" ).getSaveFileName();
	QFile openedFile( fileName );
	openedFile.open( QIODevice::WriteOnly );

	openedFile.write( QString().number( lastValue ).toUtf8() );
	openedFile.write( "\n" );
	openedFile.write( log->text().toUtf8() );

	openedFile.close();

        fileNameLabel->setText( openedFile.fileName() );
        revertAction->setEnabled(true);

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
        lastValueLabel->setText( "Last result: " + QString().number( lastValue ) );
	log->adjustSize();

}


void Calculator::reset(){

	log->setText( "" );
	log->adjustSize();
	lastValue = 0;
        lastValueLabel->setText( QString().number( lastValue ) );

}
