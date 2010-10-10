#ifndef LOGGERWINDOW_H
#define LOGGERWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QStatusBar>
#include <QLabel>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QDockWidget>
#include <QIntValidator>
#include <QFileDialog>
#include <QToolButton>
#include <QCloseEvent>
#include <QSettings>
#include <QFlags>


class LoggerWindow : public QMainWindow
{
    Q_OBJECT

private:
    QAction *myOpenAction;
    QAction *mySaveAction;
    QAction *myRevertAction;
    QAction *myShowCalcAction;
    QLabel *myFileNameLbl;
    QLabel *myLastResultLbl;
    QTextEdit *myCentralTextEdit;
    QDockWidget *myCalcDockWidget;
    QLineEdit *myCalcInputLineEdit;
    double myLastResult;
    QString myFileName;

public:
    LoggerWindow(QWidget *parent = 0);
    ~LoggerWindow();

private:
    void writeLog(const QString &str);
    void writeSettings();

protected:
    void closeEvent(QCloseEvent *e);

public slots:
    void calcPlus();
    void calcSub();
    void calcPow();
    void calcDiv();
    void fileOpen();
    void fileSave();
    void fileRevert();
};

#endif // LOGGERWINDOW_H
