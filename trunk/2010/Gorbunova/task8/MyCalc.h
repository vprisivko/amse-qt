#ifndef MYCALC_H
#define MYCALC_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
class myCalc: public QDialog{
  Q_OBJECT;

  public:
    myCalc(QWidget* parent = 0);
    double temp1;
    double temp2;
    int znak;
    void What();

  private:
    QLineEdit* l;
    QPushButton* a;
    QPushButton* s;
    QPushButton* m;
    QPushButton* d;



  public slots:
    void Add();
    void Sub();
    void Mul();
    void Div();

  signals:
    void signalAdd();
    void signalSub();
    void signalMul();
    void signalDiv();
};
#endif // MYCALC_H
