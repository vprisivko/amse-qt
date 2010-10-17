#ifndef calculator_h__
#define calculator_h__

#include <QtGui/QDialog>
#include <QTGui/QLineEdit>

class Calculator 
  : public QDialog
{
  Q_OBJECT

public:

  Calculator(QWidget *parent = 0, Qt::WFlags flags = 0);
  ~Calculator();

public:

  void setResult(int);
  const int result() const;

private slots:

  void add();
  void subtract();
  void multiply();
  void divide();

private slots:

  void setValue(const QString&);

signals:

  void resultChanged(int);
  void addText(QString);


private:

  int myValue;
  int myResult;

  QLineEdit* myLineEdit;

};

#endif // calculator_h__