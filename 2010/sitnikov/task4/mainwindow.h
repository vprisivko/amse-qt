#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QAction>
#include <QString>

class CalcDialog;


class MainWindow : public QMainWindow
{
	Q_OBJECT;

public:
	MainWindow(QWidget *parent = 0);

private:
	void configureUI();
	void updateStatusBar();

private slots:
	void file_open();
	void file_save();
	void file_revert();
	void main_calculate();
	void evaluated(QString expr, double result);

private:
	QListWidget *list_;
	QLabel *fileName_;
	QLabel *result_;

	QAction *open_;
	QAction *save_;
	QAction *revert_;
	QAction *calculate_;
	QAction *exit_;

	CalcDialog *calculator_;

	QString openedFile_;
	double lastResult_;

	int revertState_;
	QString exprState_;
	double resultState_;
};

#endif
