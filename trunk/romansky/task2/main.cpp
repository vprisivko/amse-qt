#include <QApplication>

#include "TimeDialog.h"

int main(int c,char** v){
  QApplication app(c,v);
  TimeDialog d(NULL);
  d.show();
  return app.exec();
}
