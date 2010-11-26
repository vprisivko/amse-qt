#include "calculator.h"


Calculator::Calculator(QWidget *parent) : QMainWindow(parent), ui(new Ui::Calculator){

    lastValue = 0;

    ui->setupUi(this);    

    fileNameLabel = new QLabel(this);
    lastValueLabel = new QLabel(this);
    ui->statusBar->addWidget(fileNameLabel);
    ui->statusBar->addPermanentWidget(lastValueLabel);

    inputForm = new InputForm(this);
    connect(inputForm->ui->buttonAdd, SIGNAL(clicked()),this, SLOT(updateText()));
    connect(inputForm->ui->buttonSubstract, SIGNAL(clicked()),this, SLOT(updateText()));
    connect(inputForm->ui->buttonMultiply, SIGNAL(clicked()),this, SLOT(updateText()));
    connect(inputForm->ui->buttonDivide, SIGNAL(clicked()),this, SLOT(updateText()));

}


Calculator::~Calculator(){
    delete ui;
}


void Calculator::open(){

        if ( sender() == ui->actionOpen){
                fileName = QFileDialog(this, "Select log").getOpenFileName();
        }
        if ( fileName == "" ){
            return;
        }

        QFile openedFile( fileName );
        openedFile.open( QIODevice::ReadOnly );

        fileNameLabel->setText( openedFile.fileName() );

        QString s(openedFile.readLine(40));
        lastValueLabel->setText("Last result: " + s);
        lastValue = s.toDouble();

        ui->label->setText( QString( openedFile.readAll() ) );
        ui->label->adjustSize();

        ui->actionSave->setEnabled(true);
        ui->actionRevert->setEnabled(true);

        openedFile.close();

}


void Calculator::save(){

        QFile openedFile( fileName );
        openedFile.open( QIODevice::WriteOnly );

        openedFile.write( QString().number( lastValue ).toUtf8() );
        openedFile.write( "\n" );
        openedFile.write( ui->label->text().toUtf8() );

        openedFile.close();

        ui->actionRevert->setEnabled(true);

}


void Calculator::saveAs(){

        fileName = QFileDialog( this, "Select file" ).getSaveFileName();
        if (fileName == ""){
            return;
        }

        QFile openedFile( fileName );
        openedFile.open( QIODevice::WriteOnly );

        openedFile.write( QString().number( lastValue ).toUtf8() );
        openedFile.write( "\n" );
        openedFile.write( ui->label->text().toUtf8() );

        openedFile.close();

        fileNameLabel->setText( openedFile.fileName() );
        ui->actionRevert->setEnabled(true);

}


void Calculator::revert(){
    open();
}


void Calculator::toggleForm(){
        inputForm->setVisible( inputForm->isHidden() );
}


void Calculator::updateText(){

        if (sender() == 0) return;
        QPushButton* button = dynamic_cast<QPushButton*>(sender());

        QString sign = " " + button->text() + " ";

        bool parseOk = false;
        double value = inputForm->ui->lineEdit->text().toDouble( &parseOk );

        if ( !parseOk ){
                QMessageBox::warning( inputForm->ui->lineEdit->parentWidget(), "Parse error",
                                "This is not a number",	QMessageBox::Close, QMessageBox::Close );
                return;
        }

        QString newLine;


        switch ( sign[1].toAscii() ){
        case '+':
                newLine = QString().number( lastValue ) + sign + inputForm->ui->lineEdit->text() + " = ";
                lastValue += value;
                newLine += QString().number( lastValue );
                break;
        case '-':
                newLine = QString().number( lastValue ) + sign + inputForm->ui->lineEdit->text() + " = ";
                lastValue -= value;
                newLine += QString().number( lastValue );
                break;
        case '*':
                newLine = QString().number( lastValue ) + sign + inputForm->ui->lineEdit->text() + " = ";
                lastValue *= value;
                newLine += QString().number( lastValue );
                break;
        case '/':
                if ( value == 0 ){
                        QMessageBox::warning( inputForm->ui->lineEdit->parentWidget(), "Universe error",
                                        "Dividing by zero kills.", QMessageBox::Close,
                                        QMessageBox::Close );
                        return;
                }
                newLine = QString().number( lastValue ) + sign + inputForm->ui->lineEdit->text() + " = ";
                lastValue /= value;
                newLine += QString().number( lastValue );
                break;
        }

        ui->label->setText( ui->label->text()+ newLine + "\n" );
        lastValueLabel->setText( "Last result: " + QString().number( lastValue ) );
        ui->label->adjustSize();

}


void Calculator::reset(){

        ui->label->setText( "" );
        ui->label->adjustSize();
        lastValue = 0;
        lastValueLabel->setText( QString().number( lastValue ) );

}
