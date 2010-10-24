#include "Chat.h"

#include <QApplication>

int main(int c,char** v){
  QApplication app(c,v);
  QString s;
  int i;
  Chat** d = new Chat*[c];
  if (c>1){
    for (i = 1; i<c; ++i){
      s=v[i];
      d[i-1] = new Chat(NULL,s.toInt());
      d[i-1]->show();
    }
  } 
  return app.exec();
}
