#ifndef MYATOMICINT_H
#define MYATOMICINT_H

#include <QObject>
#include <QMutex>

class MyAtomicInt : public QObject {
Q_OBJECT;
/*Q_DISABLE_COPY(MyAtomicInt);
*/
public:
    MyAtomicInt();

    int get();
    void set(int newValue);
    void inc();

signals:
    void changed(int);


private:
    QMutex mutex;
    int value;
};

#endif // MYATOMICINT_H
