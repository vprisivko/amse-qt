#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    myLastResult(0)
{
    ui->setupUi(this);
    myFileNameLbl = new QLabel("File Name: NewFile");
    myLastResultLbl = new QLabel("Last Operation Result: 0");
    statusBar()->addWidget(myFileNameLbl,1);
    statusBar()->addWidget(myLastResultLbl,1);
    ui->lineEdit->setValidator(new QDoubleValidator(ui->dockWidget_2));
    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calcPlus()
{
    if(!ui->lineEdit->text().isEmpty()){
        double firstOperand = myLastResult;
        myLastResult += ui->lineEdit->text().toDouble();
        writeLog(QString::number(firstOperand) + " + " + ui->lineEdit->text() + " = " + QString::number(myLastResult));
    }
}

void MainWindow::calcSub()
{
    if(!ui->lineEdit->text().isEmpty()){
        double firstOperand = myLastResult;
        myLastResult -= ui->lineEdit->text().toDouble();
        writeLog(QString::number(firstOperand) + " - " + ui->lineEdit->text() + " = " + QString::number(myLastResult));
    }
}

void MainWindow::calcPow()
{
    if(!ui->lineEdit->text().isEmpty()){
        double firstOperand = myLastResult;
        myLastResult *= ui->lineEdit->text().toDouble();
        writeLog(QString::number(firstOperand) + " * " + ui->lineEdit->text() + " = " + QString::number(myLastResult));
    }
}

void MainWindow::calcDiv()
{
    if(!ui->lineEdit->text().isEmpty()){
        double firstOperand = myLastResult;
        myLastResult /= ui->lineEdit->text().toDouble();
        writeLog(QString::number(firstOperand) + " / " + ui->lineEdit->text() + " = " + QString::number(myLastResult));
    }
}

void MainWindow::fileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open file",".","All files (*.kl)");
    if(QFile::exists(fileName)){
        myFileName = fileName;
        QFile file(myFileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            myLastResult = QString(file.readLine()).toDouble();
            ui->textEdit->setPlainText(QString(file.readAll()));
            myLastResultLbl->setText("Last Operation Result: " + QString::number(myLastResult));
            myFileNameLbl->setText("File Name: " + myFileName.section('/',-1));
            file.close();
        }
    }
}

void MainWindow::fileSave()
{
    if(myFileName.isEmpty()){
        myFileName = QFileDialog::getSaveFileName(this,"Save file",".","All files (*.kl)");
        if(!myFileName.isEmpty()){
            if(!myFileName.endsWith(".kl")){
                myFileName.append(".kl");
            }
        }
    }

    if(!myFileName.isEmpty()){
        QFile file(myFileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
            file.write((QString::number(myLastResult) + "\n").toUtf8());
            file.write(ui->textEdit->toPlainText().toUtf8());
            myFileNameLbl->setText("File Name: " + myFileName.section('/',-1));
            file.close();
        }
    }
}

void MainWindow::fileRevert()
{
    if(!myFileName.isEmpty()){
        if(QFile::exists(myFileName)){
            QFile file(myFileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
                myLastResult = QString(file.readLine()).toDouble();
                ui->textEdit->setPlainText(QString(file.readAll()));
                myLastResultLbl->setText("Last Operation Result: " + QString::number(myLastResult));
                file.close();
            }
        }
    }
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("MainWindow/Geometry", this->geometry());
    settings.setValue("myCalcDockWidget/Geometry", ui->dockWidget_2->geometry());
    settings.setValue("myCalcDockWidget/DockWidgetArea", dockWidgetArea(ui->dockWidget_2));
    settings.setValue("CheckableActions/myShowCalcAction", ui->actionShowCalc->isChecked());
}

void MainWindow::readSettings()
{
    QSettings settings;
    ui->actionShowCalc->setChecked(settings.value("CheckableActions/myShowCalcAction", true).toBool());
    removeDockWidget(ui->dockWidget_2);
    addDockWidget((Qt::DockWidgetArea)settings.value("myCalcDockWidget/DockWidgetArea", Qt::RightDockWidgetArea).toInt(), ui->dockWidget_2);
    ui->dockWidget_2->setVisible(settings.value("CheckableActions/myShowCalcAction", true).toBool());

    this->setGeometry(settings.value("MainWindow/Geometry",QRect(324,306,656,436)).toRect());
    ui->dockWidget_2->setGeometry(settings.value("myCalcDockWidget/Geometry",ui->dockWidget_2->geometry()).toRect());
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    writeSettings();
    e->accept();
}

void MainWindow::writeLog(const QString &str){
    ui->textEdit->append(str);
    myLastResultLbl->setText("Last Operation Result: " + QString::number(myLastResult));
}
