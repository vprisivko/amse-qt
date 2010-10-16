#ifndef CALCULATEMAINWINDOW_H
#define CALCULATEMAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QPlainTextEdit>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QSettings>

#include "calculatordialog.h"

class CalculateMainWindow : public QMainWindow {
    Q_OBJECT;

public:
    CalculateMainWindow(QWidget *parent = 0);

private:
    QPlainTextEdit * logText;
    QAction * actionOpen;
    QAction * actionSave;
    QAction * actionRevert;
    QAction * actionQuit;
    QAction * actionToggleCalcDialog;
    QMenu * menuFile;
    QLabel * sbFileName;
    QLabel * sbLastOpResult;
    CalculatorDialog * calcDialog;

    QSettings * settings;

    QString logName;
    QString lastState;
    qreal lastStateLastOpResult;
    qreal lastOpResult;

signals:


protected:
    virtual void closeEvent(QCloseEvent *);

public slots:
    void fileOpen();
    void fileSave();
    void fileRevert();
    void toggleCalc();
    void calculate(QString str, qreal result);
    void updateStatusBar();

private:
    void loadSettings();
    void saveSettings();
    void constructObjects();
    void connectSignals();
    void initCalculatorDialog();
    void loadLog(QString fileName);
    void saveLog(QString fileName);
};

#endif // CALCULATEMAINWINDOW_H
