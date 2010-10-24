#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLineEdit>


class MainWindow : public QMainWindow {
    Q_OBJECT;

public:
    MainWindow();

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
     void createActions();
     void createMenu();
     void createMainArea();
     void createToolBar();
     void createStatusBar();
     void createDockCalculator();

     //void readSettings();
     //void writeSettings();

     void loadFile(const QString &fileName);
     bool saveFile(const QString &fileName);

     double myResult;
     QString curFile;

     QMenu *myMenu;
     QMenu *myViewMenu;
     QStatusBar *myStatusBar;
     QAction *newAction;
     QAction *openAction;
     QAction *saveAction;
     QAction *saveAsAction;
     QAction *revertAction;
     QAction *exitAction;
     QLabel *logNameLabel;
     QLabel *logName;
     QLabel *lastResultLabel;
     QLabel *lastResult;
     QPlainTextEdit *myTextEdit;
     QDialog *myCalculator;
     QPushButton *plusButton;
     QPushButton *minusButton;
     QPushButton *multButton;
     QPushButton *divideButton;
     QLineEdit *myInput;

};

#endif // MAINWINDOW_H
