#include "calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), m_fileName("Untitled")
{
	setWindowTitle("Calculator");
	createActions();
	initMainWindow();
	createMenuBar();
	createToolBars();
	createStatusBar();
	createDockWidget();
	connectEvents();
}

void Calculator::createActions(){
    m_save = new QAction("Save", this);
    m_open = new QAction("Open", this);
    m_revert = new QAction("Revert", this);

    m_openCalcWidget = new QAction("&Open calculator panel", this);
    m_openCalcWidget->setCheckable(true);


    m_open->setShortcut(QKeySequence("Ctrl+O"));
    m_save->setShortcut(QKeySequence("Ctrl+S"));
    m_revert->setShortcut(QKeySequence("Ctrl+R"));
}

void Calculator::initMainWindow(){
	setGeometry(324,306,656,436);
	m_edit = new QTextEdit(this);
	m_edit->setReadOnly(true);
	setCentralWidget(m_edit);
}
void Calculator::createMenuBar(){
    m_fileMenu = new QMenu("File", this);

    m_fileMenu->addAction(m_open);
    m_fileMenu->addAction(m_save);
    m_fileMenu->addAction(m_revert);

    menuBar()->addMenu(m_fileMenu);
    menuBar()->addAction(m_openCalcWidget);
}
void Calculator::createToolBars(){
	m_toolbar = new QToolBar(this);

	m_toolbar->addAction(m_open);
	m_toolbar->addAction(m_save);
	m_toolbar->addAction(m_revert);

	m_toolbarCalc = new QToolBar(this);

	m_toolbarCalc->addAction(m_openCalcWidget);

	addToolBar(m_toolbar);
	addToolBar(m_toolbarCalc);
}
void Calculator::createStatusBar(){

    m_logName = new QLabel(m_fileName, this);
    m_lastResult = new QLabel("Undefined", this);

    statusBar()->addWidget(new QLabel("Filename: ", this), 1);
    statusBar()->addWidget(m_logName);
    statusBar()->addWidget(new QLabel("Last result: ", this), 1);
    statusBar()->addWidget(m_lastResult);
}
void Calculator::createDockWidget(){
	m_calculator = new CalcDockWgt();
	m_dockWgt = new QDockWidget(this);
	m_dockWgt->setWindowTitle("Calculator tool");
	m_dockWgt->setWidget(m_calculator);
	m_dockWgt->setAllowedAreas(Qt::AllDockWidgetAreas);

	addDockWidget(Qt::RightDockWidgetArea, m_dockWgt);
	QObject::connect(m_calculator, SIGNAL(plus_signal(int, int, int, char)), this, SLOT(writeLog(int, int, int, char)));
	QObject::connect(m_calculator, SIGNAL(minus_signal(int, int, int, char)), this, SLOT(writeLog(int, int, int, char)));
	QObject::connect(m_calculator, SIGNAL(multiply_signal(int, int, int, char)), this, SLOT(writeLog(int, int, int, char)));
	QObject::connect(m_calculator, SIGNAL(divide_signal(int, int, int, char)), this, SLOT(writeLog(int, int, int, char)));
}

void Calculator::connectEvents(){
	QObject::connect(m_save, SIGNAL(triggered(bool)), this, SLOT(save()));
	QObject::connect(m_open, SIGNAL(triggered(bool)), this, SLOT(open()));
	QObject::connect(m_revert, SIGNAL(triggered(bool)), this, SLOT(revert()));

	QObject::connect(m_openCalcWidget, SIGNAL(triggered(bool)), m_dockWgt, SLOT(setVisible(bool)));
    QObject::connect(m_dockWgt, SIGNAL(visibilityChanged(bool)), m_openCalcWidget, SLOT(setChecked(bool)));
}
void Calculator::save(){
	if(m_fileName == "Untitled"){
		QString fileName = QFileDialog::getSaveFileName(this, "Save file");
		if(fileName != "") m_fileName = fileName;
		m_logName->setText(m_fileName);
	}

	if(m_fileName != "Untitled"){
		QFile file(m_fileName);
		file.open(QIODevice::ReadWrite);
        file.write((m_lastResult->text() + "\n").toUtf8());
		file.write(m_edit->toPlainText().toUtf8());
		file.close();
	}
}
void Calculator::open(){
	QString fileName = QFileDialog::getOpenFileName(this, "Open file");
	if(fileName != "") m_fileName = fileName;
	m_logName->setText(m_fileName);

	if(m_fileName != "Untitled"){
		QFile file(m_fileName);
		if(file.open(QIODevice::ReadWrite)){
			QString lastResult = QString(file.readLine());
			m_calculator->setLastResult(lastResult.toInt());
			m_lastResult->setText(lastResult);
			m_edit->setText(QString(file.readAll()));
			file.close();
		}
	}
}

void Calculator::revert(){
	if(m_fileName == "Untitled"){
		m_edit->clear();
		m_calculator->setLastResult(NULL);
		m_lastResult->setText("NULL");
		return;
	}
	QFile file(m_fileName);

	if(file.open(QIODevice::ReadWrite)){
		QString lastResult = QString(file.readLine());
		m_calculator->setLastResult(lastResult.toInt());
		m_lastResult->setText(lastResult);
		m_edit->setText(QString(file.readAll()));
		file.close();
	}
}

void Calculator::writeLog(int result, int secondOperand, int firstOperand, char sign){
	m_edit->append(QString::number(firstOperand)+QString(sign)+QString::number(secondOperand)+"="+QString::number(result));
	m_lastResult->setText(QString::number(result));
}
