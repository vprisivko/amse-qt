#include <QApplication>

#include "Calculator.h"

int main(int c,char** v){
  QApplication app(c,v);
  Calculator d(NULL);
  d.show();
  return app.exec();
}
