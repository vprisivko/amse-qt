#ifndef calculator_h__
#define calculator_h__

#include <QtGui/QDialog>
#include <QtGui/QLineEdit>

class Calculator
  : public QDialog
{
  Q_OBJECT

public:

  Calculator(QWidget *parent = 0, Qt::WFlags flags = 0);
  ~Calculator();

public:

  void setResult(qreal);
  qreal result() const;

private slots:

  void add();
  void subtract();
  void multiply();
  void divide();

private slots:

  void setValue(const QString&);

signals:

  void resultChanged(qreal);
  void addText(QString);


private:

  qreal myValue;
  qreal myResult;

  QLineEdit* myLineEdit;

};

#endif // calculator_h__
