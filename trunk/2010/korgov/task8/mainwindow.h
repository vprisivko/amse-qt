#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSettings>
#include <QFileDialog>
#include <QCloseEvent>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *myFileNameLbl;
    QLabel *myLastResultLbl;
    double myLastResult;
    QString myFileName;

private:
    void writeLog(const QString &str);
    void writeSettings();
    void readSettings();

private slots:
    void calcDiv();
    void calcPlus();
    void calcPow();
    void calcSub();
    void fileOpen();
    void fileSave();
    void fileRevert();

protected:
    void closeEvent(QCloseEvent *e);
};

#endif // MAINWINDOW_H
