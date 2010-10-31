#include <QApplication>
#include <QString>
#include "View.h"

int main(int c,char** v){
  QApplication app(c,v);
  QString s;
  if (c>2) {
    s = v[2];
    View d(NULL, v[1], s.toInt());
    d.show();
    return app.exec();
  } else {
    View d(NULL, "127.0.0.1", 20000);
    d.show();    
    return app.exec();
  }
}
