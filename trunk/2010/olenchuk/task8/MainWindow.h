#ifndef H_MAINWINDOW
#define H_MAINWINDOW

#include <QMainWindow>
#include <QTextCursor>

#include "ui_MainWindow.h"

class Calculator;



class MainWindow : public QMainWindow, public Ui :: MainWindow {
	Q_OBJECT

	public:
		MainWindow(QWidget *perent = 0);
	
	private slots:
		void slotNewFile();
		void slotOpenFile();
		void slotSaveFile();
		void slotRevertFile();
		void slotShowCalculator();
		void answerWrite(const QString &str);




	private:
		void closeEvent(QCloseEvent *event);
		void readSettings();
		void writeSettings();
		void createActions();
		void setCurrentFile(const QString &fileName);
		
	



	private:
		int position;
		QString curFile;
		QTextCursor cursor;
		Calculator *calculator;
};

#endif
