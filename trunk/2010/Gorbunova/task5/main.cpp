#include <QApplication>
#include "myDialog.h"

int main(int argc, char *argv[]){
  QApplication app(argc, argv);
  if(argc < 2){
    qDebug() << "need port";
    return 0;
  }
  myDialog d(atoi(argv[1]));
  d.show();
  return app.exec();
}
