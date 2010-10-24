#include "LogWindow.h"
#include <QtGui>

LogWindow :: LogWindow( QWidget* parent ) : QMainWindow( parent ){
	setWindowTitle( "Log Journal" );  	
	fileName = "";
  	nameLabel = new QLabel( "File Name: " + fileName, this );
  	resultLabel = new QLabel( "Last Result : " + QString::number( 0 ) );  	 
  	myCalcDialog = new Calculator( this );
  	
	createActions(); 
  	createMenu();
  	createCentralText();
  	createStatusBar();
  	setConnection();
  
}

void LogWindow :: createActions(){
  	openAction = new QAction( "&Open", this );
  	saveAction = new QAction( "&Save", this );
  	revertAction = new QAction( "&Revert", this );
  	calculateAction = new QAction( "&Calculator", this );
}

void LogWindow :: createMenu(){
  	QMenu* menu = menuBar()->addMenu( "Menu" );
  	menu->addAction( openAction );
  	menu->addAction( saveAction );
  	menu->addAction( revertAction );
  	menu->addAction( calculateAction );
}

void LogWindow :: createCentralText(){
  	centralText = new QTextEdit();
  	centralText->setReadOnly( true );
  	setCentralWidget( centralText );
}
   
void LogWindow :: createStatusBar(){
  	statusBar()->addWidget( nameLabel, 1 );
  	statusBar()->addWidget( resultLabel, 1 );
}

void LogWindow :: setConnection(){
  	connect( calculateAction, SIGNAL( triggered() ), this, SLOT( showCalc() ) );
	connect( openAction, SIGNAL( triggered() ), this, SLOT( fileOpen() ) );
  	connect( saveAction, SIGNAL( triggered() ), this, SLOT( fileSave() ) );
  	connect( revertAction, SIGNAL( triggered() ), this, SLOT( fileRevert() ) );
	connect( myCalcDialog, SIGNAL( newExpr( QString, double ) ),this, SLOT( outputCalculation( QString, double ) ) );  	
}
void LogWindow :: outputCalculation( QString expression, double result ){
	centralText->setText( centralText->toPlainText() + expression + "\n" );
   	resultLabel->setText( "Last Result: " + QString::number( result ) );
}

void LogWindow :: showCalc(){
  	myCalcDialog->setVisible( !myCalcDialog->isVisible() );
}

void LogWindow :: fileOpen(){
  	QString name = QFileDialog::getOpenFileName( this, "Open File","Choose File To Open" );
  	if ( QFile::exists( name ) ){
    		QFile file( name );
    		if ( file.open( QIODevice::ReadOnly ) ){
       			myCalcDialog->curResult = QString( file.readLine() ).toDouble();
       			resultLabel->setText( "Last Result: " + QString::number( myCalcDialog->curResult ) );
       			centralText->setText( QString( file.readAll() ) );
       			fileName = name;
       			nameLabel->setText( "File Name: " + fileName.section( '/',-1 ) ); 
      			file.close();
    		}
  	}
}
   
void LogWindow :: fileSave(){
  	if( fileName.isEmpty() ){
     		fileName = QFileDialog::getSaveFileName( this, "Save File" );
  	}

  	if( !fileName.isEmpty() ){
    		QFile file( fileName );
    		if ( file.open( QIODevice::WriteOnly ) ){
      			QTextStream stream( &file );
      			stream << QString::number( myCalcDialog->curResult ) << "\n" << centralText->toPlainText();
       			nameLabel->setText( "File Name: " + fileName.section( '/',-1 ) );
       			file.close();
        	}
    	}
}

void LogWindow :: fileRevert(){
  	if( !fileName.isEmpty() ){
    		if( QFile::exists( fileName ) ){
      			QFile file( fileName );
      			if ( file.open( QIODevice::ReadOnly ) ){
        			myCalcDialog->curResult = QString( file.readLine() ).toDouble();
        			resultLabel->setText( QString::number( myCalcDialog->curResult ) );
        			centralText->setText( QString( file.readAll() ) );
        			resultLabel->setText( "Last Result: " + QString::number( myCalcDialog->curResult ) );
        			file.close();
      			}
    		}
  	}
}

