#include <QApplication>
#include <QFile>
#include "Game.h"

int main(int argc, char *argv[]){
  QApplication app(argc, argv);
  QFile file("ip");
  if (!file.open(QIODevice::ReadOnly)) 
    return 1;
  QHostAddress ip;
  int port;
  ip = QString(file.readLine());
  port = QString(file.readLine()).toInt();
  file.close();
  Game p(ip,port);
  p.show();
  return app.exec();
}
