#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QEvent>
#include <QComboBox>

class Dialog: public QDialog {
Q_OBJECT;

public:
  Dialog(QWidget *w = 0);

private:
  struct Timer {
    int time;
    int id;
  };
  Timer timer1, timer2;
  int activetimer;
  QLabel *lb1, *lb2;
  QLineEdit *ed;
  QComboBox* cb;

protected:
  virtual void timerEvent(QTimerEvent*);

public slots:
    void cboxchanged(int);
    void btnstop();
    void btnset();

};

#endif
