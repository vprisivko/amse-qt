#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <QTextEdit>

#include "CalcDialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT;
    
    public:
        MainWindow(QWidget *parent = NULL);
        ~MainWindow();
        
    public:
        
    private: // UI elements
        CalcDialog* calcDialog;
		QTextEdit* teLog;
		QLabel *lblFilename;
		QLabel *lblResult;
		QString logHistory;
		QString resultHistory;
    private:
    
    signals:
    
    public slots:
		void slotOpenFile();
		void slotSaveFile();
		void slotRevertFile();
		void slotShowCalc(bool checked);
		void exprCalculated(QString str, int result);	
};


#endif
