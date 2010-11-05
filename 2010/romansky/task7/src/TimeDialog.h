#ifndef TIMEDIALOG_H
#define TIMEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTimerEvent>
class TimeDialog:public QDialog{
  Q_OBJECT;
  private:
  QLabel* myfirsttimelabel;
  QLabel* mysecondtimelabel;
  QComboBox* mybox;
  QLineEdit* myset;
  QPushButton* mysetbutton;
  QPushButton* mystopbutton;

  int myfirsttimerid;
  int mysecondtimerid;
  int myfirsttime;
  int mysecondtime;

  public:
  TimeDialog(QWidget* parent=0);

  int getfirsttimerid();
  int getsecondtimerid();
  int getfirsttime();
  int getsecondtime();
  
  QPushButton* getsetbutton();
  QPushButton* getstopbutton();
  QComboBox* getbox();
  QLineEdit* getsetlineedit();
  
  private:
  void timerEvent(QTimerEvent* e);
  
  public slots:
  void Set();
  void Stop();
  signals:
  void setSignal();
  void stopSignal();
};

#endif
