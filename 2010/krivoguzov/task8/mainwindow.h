#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void revert();
    void documentWasModified();

    void plusPressed();
    void minusPressed();
    void multPressed();
    void dividePressed();

private:
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);

private:
    double myResult;
    QString curFile;
    Ui::MainWindow *ui;
    QLabel *logName;
    QLabel *lastResult;


};

#endif // MAINWINDOW_H
