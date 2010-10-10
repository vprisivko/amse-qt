#include "LoggerWindow.h"

LoggerWindow::LoggerWindow(QWidget *parent)
    : QMainWindow(parent), myLastResult(0)
{
    QSettings settings;

    myOpenAction = new QAction(QIcon("img/open.png"),"&Open",this);
    mySaveAction = new QAction(QIcon("img/save.png"),"&Save",this);
    myRevertAction = new QAction(QIcon("img/revert.png"),"&Revert",this);
    myShowCalcAction = new QAction(QIcon("img/calc.png"),"&Calculator",this);
    myShowCalcAction->setCheckable(true);
    myShowCalcAction->setChecked(settings.value("CheckableActions/myShowCalcAction", true).toBool());

    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(myOpenAction);
    fileMenu->addAction(mySaveAction);
    fileMenu->addAction(myRevertAction);

    QToolBar *fileToolbar = addToolBar("File ToolBar");
    fileToolbar->addAction(myOpenAction);
    fileToolbar->addAction(mySaveAction);
    fileToolbar->addAction(myRevertAction);
    fileToolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    QToolBar *dockWidgetsToolBar = addToolBar("Dock Widgets ToolBar");
    dockWidgetsToolBar->addAction(myShowCalcAction);
    dockWidgetsToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    myCalcDockWidget = new QDockWidget("Calculator", this);
    myCalcDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea |
                                Qt::TopDockWidgetArea |
                                Qt::BottomDockWidgetArea);

    myCalcDockWidget->setWidget(new QWidget(myCalcDockWidget));
    myCalcDockWidget->widget()->setLayout(new QVBoxLayout());

    myCalcInputLineEdit = new QLineEdit(myCalcDockWidget->widget());
    myCalcInputLineEdit->setAlignment(Qt::AlignRight);
    myCalcInputLineEdit->setValidator(new QDoubleValidator(myCalcDockWidget));

    myCalcDockWidget->widget()->layout()->addWidget(myCalcInputLineEdit);
    QHBoxLayout *calcBtnsLayout = new QHBoxLayout();

    calcBtnsLayout->addStretch();

    QPushButton *btnPlus = new QPushButton("+",myCalcDockWidget->widget());
    QObject::connect(btnPlus, SIGNAL(clicked()), this, SLOT(calcPlus()));
    calcBtnsLayout->addWidget(btnPlus);
    btnPlus->setFixedSize(40,25);

    QPushButton *btnSub = new QPushButton("-",myCalcDockWidget->widget());
    QObject::connect(btnSub, SIGNAL(clicked()), this, SLOT(calcSub()));
    calcBtnsLayout->addWidget(btnSub);
    btnSub->setFixedSize(40,25);


    QPushButton *btnPow = new QPushButton("*",myCalcDockWidget->widget());
    QObject::connect(btnPow, SIGNAL(clicked()), this, SLOT(calcPow()));
    calcBtnsLayout->addWidget(btnPow);
    btnPow->setFixedSize(40,25);

    QPushButton *btnDiv = new QPushButton("/",myCalcDockWidget->widget());
    QObject::connect(btnDiv, SIGNAL(clicked()), this, SLOT(calcDiv()));
    calcBtnsLayout->addWidget(btnDiv);
    btnDiv->setFixedSize(40,25);

    myCalcDockWidget->widget()->layout()->addItem(calcBtnsLayout);
    myCalcDockWidget->setFixedHeight(myCalcDockWidget->sizeHint().height());
    addDockWidget((Qt::DockWidgetArea)settings.value("myCalcDockWidget/DockWidgetArea", Qt::RightDockWidgetArea).toInt(), myCalcDockWidget);
    if(!settings.value("CheckableActions/myShowCalcAction", true).toBool()){
        myCalcDockWidget->hide();
    }


    myFileNameLbl = new QLabel("File Name: NewFile");
    myLastResultLbl = new QLabel("Last Operation Result: 0");
    statusBar()->addWidget(myFileNameLbl,1);
    statusBar()->addWidget(myLastResultLbl,1);

    myCentralTextEdit = new QTextEdit();
    myCentralTextEdit->setReadOnly(true);
    setCentralWidget(myCentralTextEdit);

    setContextMenuPolicy(Qt::NoContextMenu);

    QObject::connect(myShowCalcAction, SIGNAL(triggered( bool )), myCalcDockWidget, SLOT(setVisible( bool )));
    QObject::connect(myCalcDockWidget, SIGNAL(visibilityChanged( bool )), myShowCalcAction, SLOT(setChecked( bool )));

    QObject::connect(myOpenAction, SIGNAL(triggered( bool )), this, SLOT(fileOpen()));
    QObject::connect(mySaveAction, SIGNAL(triggered( bool )), this, SLOT(fileSave()));
    QObject::connect(myRevertAction, SIGNAL(triggered( bool )), this, SLOT(fileRevert()));

    this->setGeometry(settings.value("MainWindow/Geometry",QRect(324,306,656,436)).toRect());
    myCalcDockWidget->setGeometry(settings.value("myCalcDockWidget/Geometry",myCalcDockWidget->geometry()).toRect());

}

LoggerWindow::~LoggerWindow()
{
}

void LoggerWindow::writeLog(const QString &str){
    myCentralTextEdit->append(str);
    myLastResultLbl->setText("Last Operation Result: " + QString::number(myLastResult));
}

void LoggerWindow::calcPlus()
{
    if(!myCalcInputLineEdit->text().isEmpty()){
        double firstOperand = myLastResult;
        myLastResult += myCalcInputLineEdit->text().toDouble();
        writeLog(QString::number(firstOperand) + " + " + myCalcInputLineEdit->text() + " = " + QString::number(myLastResult));
    }
}

void LoggerWindow::calcSub()
{
    if(!myCalcInputLineEdit->text().isEmpty()){
        double firstOperand = myLastResult;
        myLastResult -= myCalcInputLineEdit->text().toDouble();
        writeLog(QString::number(firstOperand) + " - " + myCalcInputLineEdit->text() + " = " + QString::number(myLastResult));
    }
}

void LoggerWindow::calcPow()
{
    if(!myCalcInputLineEdit->text().isEmpty()){
        double firstOperand = myLastResult;
        myLastResult *= myCalcInputLineEdit->text().toDouble();
        writeLog(QString::number(firstOperand) + " * " + myCalcInputLineEdit->text() + " = " + QString::number(myLastResult));
    }
}

void LoggerWindow::calcDiv()
{
    if(!myCalcInputLineEdit->text().isEmpty()){
        double firstOperand = myLastResult;
        myLastResult /= myCalcInputLineEdit->text().toDouble();
        writeLog(QString::number(firstOperand) + " / " + myCalcInputLineEdit->text() + " = " + QString::number(myLastResult));
    }
}

void LoggerWindow::fileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open file",".","All files (*.kl)");
    if(QFile::exists(fileName)){
        myFileName = fileName;
        QFile file(myFileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            myLastResult = QString(file.readLine()).toDouble();
            myCentralTextEdit->setPlainText(QString(file.readAll()));
            myLastResultLbl->setText("Last Operation Result: " + QString::number(myLastResult));
            myFileNameLbl->setText("File Name: " + myFileName.section('/',-1));
            file.close();
        }
    }
}

void LoggerWindow::fileSave()
{
    if(myFileName.isEmpty()){
        myFileName = QFileDialog::getSaveFileName(this,"Save file",".","All files (*.kl)");
        if(!myFileName.endsWith(".kl")){
            myFileName.append(".kl");
        }
    }

    if(!myFileName.isEmpty()){
        QFile file(myFileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
            file.write((QString::number(myLastResult) + "\n").toUtf8());
            file.write(myCentralTextEdit->toPlainText().toUtf8());
            myFileNameLbl->setText("File Name: " + myFileName.section('/',-1));
            file.close();
        }
    }
}

void LoggerWindow::fileRevert()
{
    if(!myFileName.isEmpty()){
        if(QFile::exists(myFileName)){
            QFile file(myFileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
                myLastResult = QString(file.readLine()).toDouble();
                myCentralTextEdit->setPlainText(QString(file.readAll()));
                myLastResultLbl->setText("Last Operation Result: " + QString::number(myLastResult));
                file.close();
            }
        }
    }
}

void LoggerWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("MainWindow/Geometry", this->geometry());
    settings.setValue("myCalcDockWidget/Geometry", myCalcDockWidget->geometry());
    settings.setValue("myCalcDockWidget/DockWidgetArea", dockWidgetArea(myCalcDockWidget));
    settings.setValue("CheckableActions/myShowCalcAction", myShowCalcAction->isChecked());


}

void LoggerWindow::closeEvent(QCloseEvent *e)
{
    writeSettings();
    e->accept();
}
