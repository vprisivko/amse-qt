#ifndef H_MAINWINDOW
#define H_MAINWINDOW

#include <QMainWindow>
#include <QTextCursor>
class QTextEdit;
class QLabel;
class Calculator;
class QMenu;
class QAction;


class MainWindow : public QMainWindow {
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
		void createMenus();
		void createActions();
		void setCurrentFile(const QString &fileName);
		
	



	private:
		int position;
		QString curFile;
		QTextCursor cursor;
		Calculator *calculator;
		QTextEdit *textEdit;
		QMenu *fileMenu;
		QAction *newFileAct;
		QAction *openAct;
		QAction *saveAct;
		QAction *showCalculatorAct;
		QAction *revertAct;

		
};

#endif
