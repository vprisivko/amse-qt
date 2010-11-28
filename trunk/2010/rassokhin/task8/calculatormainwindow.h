#ifndef CALCULATORMAINWINDOW_H
#define CALCULATORMAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QPlainTextEdit>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QSettings>

#include "calculatordialog.h"

namespace Ui {
    class CalculatorMainWindow;
}

class CalculatorMainWindow : public QMainWindow {
    Q_OBJECT;

public:
    CalculatorMainWindow(QWidget * parent = 0);
    ~CalculatorMainWindow();

private:

    Ui::CalculatorMainWindow *ui;

    CalculatorDialog * calcDialog;

    QSettings * settings;

    QString logName;
    QString lastState;
    qreal lastStateLastOpResult;
    qreal lastOpResult;

signals:


protected:
    virtual void closeEvent(QCloseEvent *);
    void changeEvent(QEvent *e);

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
    void fixUi();
    void connectSignals();
    void initCalculatorDialog();
    void loadLog(QString fileName);
    void saveLog(QString fileName);
};

#endif // CALCULATORMAINWINDOW_H
