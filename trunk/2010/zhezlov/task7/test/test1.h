#ifndef TEST1_H
#define TEST1_H

#include <QObject>
#include <QTest>
#include <timers.h>

class Test1 : public QObject
{
    Q_OBJECT
public:
    explicit Test1(QObject *parent = 0);

private:
    Timers* m_timers;

signals:

private slots:
    void testSignals();
    void testGUI();
    void testSem();

};

#endif // TEST1_H
