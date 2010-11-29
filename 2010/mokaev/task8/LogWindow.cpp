#include "LogWindow.h"
#include <QtGui>

LogWindow :: LogWindow( QWidget* parent ) : QMainWindow( parent ){

        logWindowUi.setupUi( this );
        myCalcDialog = new Calculator( this );

        createLabels();
  	createStatusBar();
  	setConnection();
  
}

void LogWindow :: createLabels(){
        fileName = "";
        nameLabel = new QLabel( "File Name: " + fileName, this );
        resultLabel = new QLabel( "Last Result : " + QString::number( 0 ) );
}
   
void LogWindow :: createStatusBar(){
  	statusBar()->addWidget( nameLabel, 1 );
  	statusBar()->addWidget( resultLabel, 1 );
}

void LogWindow :: setConnection(){
        connect( logWindowUi.actionCalculator, SIGNAL( triggered() ), this, SLOT( showCalc() ) );
        connect( logWindowUi.actionOpen, SIGNAL( triggered() ), this, SLOT( fileOpen() ) );
        connect( logWindowUi.actionSave, SIGNAL( triggered() ), this, SLOT( fileSave() ) );
        connect( logWindowUi.actionRevert, SIGNAL( triggered() ), this, SLOT( fileRevert() ) );
	connect( myCalcDialog, SIGNAL( newExpr( QString, double ) ),this, SLOT( outputCalculation( QString, double ) ) );  	
}
void LogWindow :: outputCalculation( QString expression, double result ){
        logWindowUi.log->setText( logWindowUi.log->toPlainText() + expression + "\n" );
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
                        logWindowUi.log->setText( QString( file.readAll() ) );
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
                        stream << QString::number( myCalcDialog->curResult ) << "\n" << logWindowUi.log->toPlainText();
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
                                logWindowUi.log->setText( QString( file.readAll() ) );
        			resultLabel->setText( "Last Result: " + QString::number( myCalcDialog->curResult ) );
        			file.close();
      			}
    		}
  	}
}

