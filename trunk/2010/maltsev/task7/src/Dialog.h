#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QEvent>
#include <QComboBox>
#include <QPushButton>

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
  QLabel *my_label1, *my_label2;
  QLineEdit *my_edit;
  QComboBox* my_cbox;
  QPushButton *my_setbtn, *my_stopbtn;

protected:
  virtual void timerEvent(QTimerEvent*);

public slots:
    void cboxchanged(int);
    void btnstop();
    void btnset();

signals:
    void setSignal();

friend class Test;

};

#endif
